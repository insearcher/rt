#include "rt_cl.h"

static float	sdf(float3 origin, float3 direction, __global t_object *obj, float3 *lp, int scene_params)
{
	float3	gright = (float3){1, 0, 0};
	float3	gup = (float3){0, 1, 0};
	float	distance = 0.0f;
	float3	local_pos;

	if (scene_params & RT_REPETITION)
		local_pos = repeatSDF(origin, obj->transform.pos, 0, 0, 0);
	else
		local_pos = origin - obj->transform.pos;

	float3 cr = cross(gup, obj->transform.up);
	float cos = dot(gup, obj->transform.up);
	float sin = length(cr);
	float3 a = normalize(cr);
	if (fabs(a.x) < RM_FLT_EPSILON && fabs(a.y) < RM_FLT_EPSILON && fabs(a.z)< RM_FLT_EPSILON)
	{
		cr = cross(gright, obj->transform.right);
		cos = dot(gright, obj->transform.right);
		sin = length(cr);
		a = normalize(cr);
		if (fabs(a.x) < RM_FLT_EPSILON && fabs(a.y) < RM_FLT_EPSILON && fabs(a.z)< RM_FLT_EPSILON)
		{
			a = gup;
		}
	}
	float3 x = (float3)
	{
		cos + (1 - cos) * a.x * a.x, (1 - cos) * a.x * a.y - sin * a.z, (1 - cos) * a.x * a.z + sin * a.y
	};
	float3 y = (float3)
	{
		(1 - cos) * a.x * a.y + sin * a.z, cos + (1 - cos) * a.y * a.y, (1 - cos) * a.y * a.z - sin * a.x
	};
	float3 z = (float3)
	{
		(1 - cos) * a.x * a.z - sin * a.y, (1 - cos) * a.y * a.z + sin * a.x, cos + (1 - cos) * a.z * a.z
	};
	float3 new_local_pos = (float3)
	{
		dot(x, local_pos),
		dot(y, local_pos),
		dot(z, local_pos)
	};
	local_pos = new_local_pos;
	switch (obj->type)
	{
		case o_sphere:
			distance = sdf_octahedron(local_pos, obj->params.sphere.radius);
			break;
		case o_box:
			distance = sdf_box(local_pos, obj->params.box.bounds);
			break;
		case o_round_box:
			distance = sdf_round_box(local_pos, obj->params.round_box.bounds, obj->params.round_box.r);
			break;
		case o_torus:
			distance = sdf_torus(local_pos, obj->params.torus.radius, obj->params.torus.inner_radius);
			break;
		case o_capped_torus:
			distance = sdf_capped_torus(local_pos, obj->params.capped_torus.sc, obj->params.capped_torus.ra, obj->params.capped_torus.rb);
			break;
		case o_link:
			distance = sdf_link(local_pos, obj->params.link.le, obj->params.link.r1, obj->params.link.r2);
			break;
		case o_cylinder:
			distance = sdf_cylinder(local_pos, obj->params.cylinder.params);
			break;
		case o_cone:
			distance = sdf_cone(local_pos, obj->params.cone.c);
			break;
		case o_plane:
			distance = sdf_plane(local_pos, obj->transform.up, obj->params.plane.distance);
			break;
		case o_mandelbulb:
			distance = sdf_mandelbulb(local_pos, obj->params.mandelbulb.power,
					obj->params.mandelbulb.iteration, obj->params.mandelbulb.breakout);
			break;
		case o_mandelbox:
			distance = sdf_mandelbox(local_pos, obj->params.mandelbox.scale, obj->params.mandelbox.fixedradius,
									 obj->params.mandelbox.minradius, obj->params.mandelbox.cube_size,
									 obj->params.mandelbox.iteration);
			break;
	    case o_menger_sponge:
	        distance = sdf_menger_sponge(local_pos, obj->params.menger_sponge.offset,
	                obj->params.menger_sponge.scale, obj->params.menger_sponge.iteration);
	        break;
		case o_octahedron:
			distance = sdf_octahedron(local_pos, obj->params.octahedron.bounds);
			break;
	}
	if (lp)
	{
		float3 new_direction = (float3){
				dot(x, direction),
				dot(y, direction),
				dot(z, direction)};
		*lp = new_local_pos + new_direction * distance;
	}
	return (distance);
}

static float	sceneSDF(float3 origin, float3 direction, __global t_scene *scene, t_raycast_hit *rh)
{
	float		dist_to_obj = 1000000.f;
	float		tmp_dist_to_obj;
	bool		cond;
	float3		lp;

	for (uint i = 0; i < scene->objects_count; i++)
	{
		tmp_dist_to_obj = sdf(origin, direction, &scene->objects[i], &lp, scene->params);
		cond = tmp_dist_to_obj < dist_to_obj && tmp_dist_to_obj > -F_EPS;
		if (cond)
		{
			dist_to_obj = tmp_dist_to_obj;
			rh->hit = &scene->objects[i];
			rh->local_point = lp;
		}
	}
	return (dist_to_obj);
}

static void	get_normal(float3 pos, float3 direction, float basic_dist,
		t_raycast_hit *rh, int params)
{
	rh->normal = normalize((float3){sdf((float3){pos.x + F_EPS, pos.y, pos
			.z}, direction, rh->hit, 0, params),
									sdf((float3){pos.x, pos.y + F_EPS, pos.z},
										direction, rh->hit, 0, params),
									sdf((float3){pos.x, pos.y, pos.z + F_EPS},
										direction, rh->hit, 0, params)} -
						   (float3){basic_dist, basic_dist, basic_dist});
}

int			raymarch(float3 origin, float3 direction, float distance, __global t_scene *scene, t_raycast_hit *rh)
{
	float	intersect_dist = F_EPS;
	float	dist_to_obj;
	int		max_steps = 500;
	float3	cur_ray_point;
	bool	cond;

	distance = select(distance, MAXFLOAT, distance < F_EPS);

	#pragma unroll 16
	for (int i = 0; i < max_steps; i++)
	{
		cur_ray_point = mad(direction, intersect_dist, origin);
		dist_to_obj = sceneSDF(cur_ray_point, direction, scene, rh);
		if (dist_to_obj < -F_EPS)
		{
			rh->point = cur_ray_point;
			rh->distance = intersect_dist;
			return (1);
		}
		if (dist_to_obj < F_EPS)
		{
			rh->point = cur_ray_point;
			rh->distance = intersect_dist;
			get_normal(cur_ray_point, direction, dist_to_obj, rh, scene->params);
			return (1);
		}
		intersect_dist += dist_to_obj;
		cond = intersect_dist > scene->camera.clipping_planes.far || intersect_dist > distance;
		if (cond)
			return (0);
	}
	return (0);
}

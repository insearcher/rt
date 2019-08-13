#include "rt_cl.h"

static float	sdf(float3 origin, __global t_object *obj)
{
	float	distance = 0;
	float3	local_pos;

	local_pos = origin - obj->transform.pos;
//	if (1) // if obj->isRepeating or anything like this
//		local_pos = repeatSDF(local_pos, obj->transform.pos, 0, 0, 0);
	switch (obj->type)
	{
		case sphere:
			distance = sdf_sphere(local_pos, obj->params.sphere.radius);
			break;
		case box:
			distance = sdf_box(local_pos, obj->params.box.bounds);
			break;
		case round_box:
			distance = sdf_round_box(local_pos, obj->params.round_box.bounds);
			break;
		case torus:
			distance = sdf_torus(local_pos, obj->params.torus.params);
			break;
		case cylinder:
			distance = sdf_cylinder(local_pos, obj->params.cylinder.params);
			break;
		case plane:
			distance = sdf_plane(local_pos, obj->transform.up, obj->params.plane.distance);
			break;
	}
	return (distance);
}

static float	sceneSDF(float3 O, __global t_scene *scene, t_raycast_hit *rh)
{
	float		dist_to_obj = 1000000.f;
	float		tmp_dist_to_obj;
	bool		cond;

	for (size_t i = 0; i < scene->objects_count; i++)
	{
		tmp_dist_to_obj = sdf(O, &scene->objects[i]);
		cond = tmp_dist_to_obj < dist_to_obj && tmp_dist_to_obj > -F_EPS;
		if (cond)
		{
			dist_to_obj = tmp_dist_to_obj;
			rh->hit = &scene->objects[i];
		}
	}
	return (dist_to_obj);
}

static void	get_normal(float3 pos, float basic_dist, t_raycast_hit *rh)
{
	rh->normal = normalize((float3){sdf((float3){pos.x + F_EPS, pos.y, pos.z}, rh->hit),
							sdf((float3){pos.x, pos.y + F_EPS, pos.z}, rh->hit),
							sdf((float3){pos.x, pos.y, pos.z + F_EPS}, rh->hit)} -
									(float3){basic_dist, basic_dist, basic_dist});
}

char	raymarch(float3 origin, float3 direction, float distance, __global t_scene *scene, t_raycast_hit *rh)
{
	float	intersect_dist = 0;
	float	dist_to_obj;
	int		max_steps = 1000;
	float3	cur_ray_point;
	bool	cond;

	distance = select(distance, MAXFLOAT, distance < F_EPS);

	#pragma unroll 4
	for (int i = 0; i < max_steps; i++)
	{
		cur_ray_point = mad(direction, intersect_dist, origin);
		dist_to_obj = sceneSDF(cur_ray_point, scene, rh);
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
			get_normal(cur_ray_point, dist_to_obj, rh);
			return (1);
		}
		intersect_dist += dist_to_obj;
		cond = intersect_dist > scene->camera.clipping_planes.far || intersect_dist > distance;
		if (cond)
			return (0);
	}
	return (0);
}

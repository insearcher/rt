/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 17:50:06 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/23 17:50:07 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_raycast.h"
#include "rt_input_system.h"

# define  F_EPS		0.001f

static cl_float3	screen_to_world(cl_int2 coord, cl_int2 screen, float fov)
{
	cl_float3	k;

	coord.x -= screen.x / 2;
	coord.y -= screen.y / 2;
	k.z = sqrt((float)screen.x * screen.x + screen.y * screen.y) / 2.0f / tan(fov * 3.1416f / 180 / 2);
	float fovx = atan(screen.x / 2.0f / k.z);
	float fovy = atan(screen.y / 2.0f / k.z);
	float maxx = tan(fovx) * k.z;
	float maxy = tan(fovy) * k.z;
	k.x = coord.x * (maxx * 2.0f / screen.x);
	k.y = coord.y * (maxy * 2.0f / screen.y);
	return (k);
}

static float	sdf(cl_float3 origin, t_object *obj)
{
	float	distance = 0;
	cl_float3	local_pos;

	cl_float3 gup = (cl_float3){{0, 1, 0}};
	local_pos.v4 = origin.v4 - obj->transform.pos.v4;
	float cos = f3dot(gup, obj->transform.up);
	float sin = f3len(f3cross(gup, obj->transform.up));
	cl_float3 a = f3norm(f3cross(gup, obj->transform.up));
	if (fabs(a.x) < RM_FLT_EPSILON && fabs(a.y) < RM_FLT_EPSILON && fabs(a.z) < RM_FLT_EPSILON)
		a = (cl_float3) {{1, 0, 0}};
	cl_float3 new_local_pos = (cl_float3){{
			f3dot((cl_float3){{
					cos + (1 - cos) * a.x * a.x, (1 - cos) * a.x * a.y - sin * a.z, (1 - cos) * a.x * a.z + sin * a.y
			}}, local_pos),
			f3dot((cl_float3){{
					(1 - cos) * a.x * a.y + sin * a.z, cos + (1 - cos) * a.y * a.y, (1 - cos) * a.y * a.z - sin * a.x
			}}, local_pos),
			f3dot((cl_float3){{
					(1 - cos) * a.x * a.z - sin * a.y, (1 - cos) * a.y * a.z + sin * a.x, cos + (1 - cos) * a.z * a.z
			}}, local_pos)}};
	local_pos = new_local_pos;
//	if (0) // if obj->isRepeating or anything like this
//	local_pos = repeatSDF(local_pos, obj->transform.pos, 0, 0, 0);
	switch (obj->type)
	{
		case o_sphere:
			distance = sdf_sphere(local_pos, obj->params.sphere.radius);
			break;
		case o_box:
			distance = sdf_box(local_pos, obj->params.box.bounds);
			break;
		case o_round_box:
			distance = sdf_round_box(local_pos, obj->params.round_box.bounds, obj->params.round_box.r);
			break;
		case o_torus:
			distance = sdf_torus(local_pos, obj->params.torus.params);
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
	}
	return (distance);
}


static float	sceneSDF(cl_float3 O, t_scene *scene, t_raycast_hit *rh, cl_uint mask)
{
	float		dist_to_obj = 1000000.f;
	float		tmp_dist_to_obj;
	
	for (size_t i = 0; i < scene->objects_count; i++)
	{
		if (!(scene->objects[i].layer & mask))
			continue ;
		tmp_dist_to_obj = sdf(O, &scene->objects[i]);
		if (tmp_dist_to_obj < dist_to_obj && tmp_dist_to_obj > -F_EPS)
		{
			dist_to_obj = tmp_dist_to_obj;
			rh->hit = &scene->objects[i];
		}
	}
	return (dist_to_obj);
}

static void	get_normal(cl_float3 pos, float basic_dist, t_raycast_hit *rh)
{
	rh->normal = (cl_float3){{
		sdf((cl_float3){{pos.x + F_EPS, pos.y, pos.z}}, rh->hit),
		sdf((cl_float3){{pos.x, pos.y + F_EPS, pos.z}}, rh->hit),
		sdf((cl_float3){{pos.x, pos.y, pos.z + F_EPS}}, rh->hit)
	}};
	cl_float3 b = (cl_float3){{basic_dist, basic_dist, basic_dist}};
	rh->normal.v4 -= b.v4;
	rh->normal = f3norm(rh->normal);
}

char	raymarch(cl_float3 origin, cl_float3 direction, t_scene *scene, t_raycast_hit *rh, cl_uint mask)
{
	float	intersect_dist = 0;
	float	dist_to_obj;
	int		max_steps = 200;
	cl_float3	cur_ray_point;
	
	for (int i = 0; i < max_steps; i++)
	{
		cur_ray_point.v4 = origin.v4 + direction.v4 * intersect_dist;
		dist_to_obj = sceneSDF(cur_ray_point, scene, rh, mask);
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
		if (intersect_dist > scene->camera.clipping_planes.far)
			return (0);
	}
	return (0);
}

static char	raycast(t_scene *scene, int x, int y, t_raycast_hit *rh, cl_uint mask)
{
	cl_int2	screen = scene->camera.screen;
	cl_int2	pixel = (cl_int2){{x, y}};

	cl_float3	k = screen_to_world(pixel, screen, scene->camera.fov);

	t_transform t = scene->camera.transform;

	cl_float3	origin = t.pos;
	cl_float3	direction;
	direction.v4 = t.right.v4 * k.x + t.up.v4 * k.y + t.forward.v4 * k.z;
	direction.v4 = direction.v4 / sqrtf(powf(direction.x, 2) + powf(direction.y, 2) + powf(direction.z, 2));
	
	return (raymarch(origin, direction, scene, rh, mask));
}

int		rt_raycast(t_ui_main *ui, void *a)
{
	t_rt_main	*rt;
	t_scene		*s;
	int			x;
	int			y;

	(void)a;
	rt = ui->data;
	s = &rt->scenes[0];

	SDL_GetMouseState(&x, &y);
	y = s->camera.screen.y - y;

	t_raycast_hit	rh;
	if (raycast(s, x, y, &rh, ~IGNORE_RAYCAST_LAYER))
		change_selected((t_input_system *)rt->systems[INPUT_SYSTEM_INDEX], rh.hit);

	return (1);
}
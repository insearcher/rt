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

int		rt_raycast1(t_ui_main *ui, void *a)
{
	t_rt_main	*rt;
	cl_mem		cl_id;
	cl_mem		cl_scene;
	cl_mem		cl_objects;
	cl_mem		cl_lights;
	int			x;
	int			y;

	size_t		size = sizeof(int);

	(void)a;
	rt = ui->data;
	cl_id = clCreateBuffer(*rt->cl->context, CL_MEM_READ_WRITE, size, NULL, NULL);
	create_buffers(rt, &cl_scene, &cl_objects, &cl_lights);

	SDL_GetMouseState(&x, &y);
	y = rt->scenes[0].camera.screen.y - y;

	cl_kernel	*kernel = cl_get_kernel_by_name(rt->cl, "raycast");
	clSetKernelArg(*kernel, 0, sizeof(cl_mem), &cl_scene);
	clSetKernelArg(*kernel, 1, sizeof(cl_mem), &cl_objects);
	clSetKernelArg(*kernel, 2, sizeof(cl_mem), &cl_lights);
	clSetKernelArg(*kernel, 3, sizeof(int), &x);
	clSetKernelArg(*kernel, 4, sizeof(int), &y);
	clSetKernelArg(*kernel, 5, sizeof(cl_mem), &cl_id);
	clEnqueueNDRangeKernel(*rt->cl->queue, *kernel, 1, NULL, &size, NULL, 0, NULL, NULL);

	int	id = 777;
	clEnqueueReadBuffer(*rt->cl->queue, cl_id, CL_TRUE, 0, size, &id, 0, NULL, NULL);

	clReleaseMemObject(cl_id);
	clReleaseMemObject(cl_objects);
	clReleaseMemObject(cl_lights);
	clReleaseMemObject(cl_scene);
	return (1);
}

static float length(cl_float3 v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

static cl_float3 normalize(cl_float3 v)
{
	v.v4 /= length(v);
	return v;
}

static float	sdf_sphere(cl_float3 pos, float radius)
{
	return (length(pos) - radius);
}

static float	sdf_box(cl_float3 pos, cl_float3 bounds)
{
	cl_float3	temp = (cl_float3){{fabs(pos.x), fabs(pos.y), fabs(pos.z)}};
	cl_float3 d;
	d.v4 = temp.v4 - bounds.v4;
	temp = (cl_float3){{fmax(d.x, 0), fmax(d.y, 0), fmax(d.z, 0)}};
	return length(temp) + fmin(fmax(d.x, fmax(d.y, d.z)), 0);
}

static float	sdf_plane(cl_float3 p, cl_float3 n, float d)
{
	return p.x * n.x + p.y * n.y + p.z * n.z + d;
}

static float	sdf(cl_float3 origin, t_object *obj)
{
	float	distance = 0;
	cl_float3	local_pos;

	local_pos.v4 = origin.v4 - obj->transform.pos.v4;
//	if (0) // if obj->isRepeating or anything like this
//	local_pos = repeatSDF(local_pos, obj->transform.pos, 0, 0, 0);
	switch (obj->type)
	{
		case sphere:
			distance = sdf_sphere(local_pos, obj->params.sphere.radius);
			break;
		case box:
			distance = sdf_box(local_pos, obj->params.box.bounds);
			break;
		case round_box:
			distance = sdf_sphere(local_pos, obj->params.sphere.radius);
			break;
		case torus:
			distance = sdf_sphere(local_pos, obj->params.sphere.radius);
			break;
		case cylinder:
			distance = sdf_sphere(local_pos, obj->params.sphere.radius);
			break;
		case plane:
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
	rh->normal = normalize(rh->normal);
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
	direction.v4 = direction.v4 / sqrt(pow(direction.x, 2) + pow(direction.y, 2) + pow(direction.z, 2));
	
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
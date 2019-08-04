#include "config_cl.h"

static float	SDF(float3 ray_point, t_object *obj)
{
	float dist_to_obj = 0;
	float3 posc;

	posc = ray_point - obj->transform.pos;
	if (0) // if obj->isRepeating or anything like this
		posc = repeatSDF(ray_point, obj->transform.pos, 0, 0, 0);
	switch (obj->type)
	{
		case 1:
			dist_to_obj = sphereSDF(posc, 1);
			break;
		case 2:
			dist_to_obj = boxSDF(posc, 1);
			break;
	}
	return (dist_to_obj);
}

static float	sceneSDF(float3 O, t_scene1 *scene, t_object *closest_obj)
{
	float		dist_to_obj = 1000000.f;
	t_object	object;
	float		tmp_dist_to_obj;

	for (int i = 0; i < scene->objects_num; i++)
	{
		object = scene->objects[i];
		tmp_dist_to_obj = SDF(O, &object);
		if (tmp_dist_to_obj < dist_to_obj && tmp_dist_to_obj > -0.0001f)
		{
			dist_to_obj = tmp_dist_to_obj;
			*closest_obj = object;
		}
	}
	return (dist_to_obj);
}

static void		get_normal(float3 pos, float basic_dist, float3 *normal, t_object *obj)
{
	float eps = 0.001f;

	*normal = normalize((float3){SDF((float3){pos.x + eps, pos.y, pos.z}, obj),
							SDF((float3){pos.x, pos.y + eps, pos.z}, obj),
							SDF((float3){pos.x, pos.y, pos.z + eps}, obj)} -
									(float3){basic_dist, basic_dist, basic_dist});
}

static float	find_intersect_and_normal(float3 start_ray, float3 dir_ray,
		t_scene1 *scene, t_object *closest_obj, float3 *normal, float mult)
{
	float		intersect_dist = scene->min_distance * mult;
	float		dist_to_obj;
	int			max_steps = 1000;
	float		epsilon = 0.0001f;
	float3	cur_ray_point;

	for (int i = 0; i < max_steps; i++)
	{
		cur_ray_point = start_ray + dir_ray * intersect_dist;
		dist_to_obj = sceneSDF(cur_ray_point, scene, closest_obj);
		if (dist_to_obj < -epsilon)
			return (intersect_dist);
		if (dist_to_obj < epsilon)
		{
			get_normal(cur_ray_point, dist_to_obj, normal, closest_obj);
			return (intersect_dist);
		}
		intersect_dist += dist_to_obj;
		if (intersect_dist > scene->max_distance)
			return (-1);
	}
	return (-1);
}

float3	ray_marching(float3 start_ray, float3 dir_ray, t_scene1 *scene, float mult)
{
	float3	color;
	float		intersect_dist;
	t_object	closest_obj;
	float3	normal;

	if ((intersect_dist = find_intersect_and_normal(start_ray, dir_ray, scene, &closest_obj, &normal, mult)) >= 0)
		color = normal * 0.5f + (float3){0.5f, 0.5f, 0.5f};
	else
		color = (float3){0.36 - dir_ray.y * 0.6, 0.36 + dir_ray.y * 0.6, 0.6 - dir_ray.y * 0.6};
	color = pow(color, float3(0.4545));
	return (color);
}

#include "config_cl.h"

static float sphereSDF(t_vector3d pos, float radius)
{
	return (mv_length(pos) - radius);
}

static void	objSDF(t_vector3d O, t_object3d *obj, float *dist_to_obj)
{
	float	tmp_dist_to_obj;

	if (obj->type == 1)
		tmp_dist_to_obj = sphereSDF(mv_minus(O, obj->center), obj->radius);
	if (tmp_dist_to_obj > *dist_to_obj)
		*dist_to_obj = tmp_dist_to_obj;
}

static float	sceneSDF(t_vector3d O, t_scene *scene)
{
	float		dist_to_obj = 0.f;
	t_object3d	object;

	for (int i = 0; i < scene->objects_num; i++)
	{
		object = scene->objects[i];
		objSDF(O, &object, &dist_to_obj);
	}
	return (dist_to_obj);
}

static float	find_intersect(t_vector3d start_ray, t_vector3d dir_ray, t_scene *scene)
{
	float	intersect_dist = 0.f;
	float	dist_to_obj;
	int		max_steps = 200;
	float	epsilon = 0.001;

	for (int i = 0; i < max_steps; i++)
	{
		dist_to_obj = sceneSDF(mv_plus(start_ray, mv_mult_num(dir_ray, intersect_dist)), scene);
		if (dist_to_obj < epsilon)
			return (dist_to_obj);
		intersect_dist += dist_to_obj;
		if (intersect_dist > scene->max_distance)
			return (-1);
	}
	return (-1);
}

t_color	ray_marching(t_vector3d start_ray, t_vector3d dir_ray, t_scene *scene)
{
	t_color	color;
	float	intersect_dist = 0;

	if ((intersect_dist = find_intersect(start_ray, dir_ray, scene)) >= 0)
		color = (t_color){255, 20, 20};
	else
		color = (t_color){255, 255, 255};
	return (color);
}

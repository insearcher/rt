#include "config_cl.h"

static float mod2(float a, float b)
{
	return (a - ((int)(a / b)) * b);
}

static t_vector3d ft_mod(t_vector3d a, t_vector3d b)
{
//	return ((t_vector3d){mod2(a.x, a.x), mod2(a.y, a.y), mod2(a.z, a.z)});
	return ((t_vector3d){mod2(a.x, b.x), mod2(a.y, b.y), mod2(a.z, b.z)});

}

static float sphereSDF(t_vector3d pos, t_vector3d c, float radius)
{
	t_vector3d in;
	in = ft_mod(pos, c);
//	t_vector3d in = mv_mult(a, b);
	in = mv_minus(in, mv_mult_num(c, 0.5f));
//	in = mv_minus(in, c);
//	in = mv_minus(pos, c);
	return (mv_length(in) - radius);

//	return (mv_length(mv_minus(pos, c)) - radius);
}

static float	SDF(t_vector3d O, t_object3d *obj)
{
	float dist_to_obj;

	if (obj->type == 1)
		dist_to_obj = sphereSDF(O, obj->center, obj->radius);
	//	dist_to_obj = sphereSDF(mv_minus((t_vector3d){mod(O.x, obj->center.x),
	//								mod(O.y, obj->center.y), mod(O.z, obj->center.z)}, mv_mult_num(obj->center, 0.5)), obj->radius);
	return (dist_to_obj);
}

static float	sceneSDF(t_vector3d O, t_scene *scene, t_object3d *closest_obj)
{
	float		dist_to_obj = 1000000.f;
	t_object3d	object;
	float		tmp_dist_to_obj;

	for (int i = 0; i < scene->objects_num; i++)
	{
		object = scene->objects[i];
		tmp_dist_to_obj = SDF(O, &object);
		if (tmp_dist_to_obj < dist_to_obj)
		{
			dist_to_obj = tmp_dist_to_obj;
			*closest_obj = object;
		}
	}
	return (dist_to_obj);
}

static void		get_normal(t_vector3d pos, float basic_dist, t_vector3d *normal, t_object3d *obj)
{
	float eps = 0.001;

	*normal = mv_normalize(mv_minus((t_vector3d){SDF((t_vector3d){pos.x + eps, pos.y, pos.z}, obj),
							SDF((t_vector3d){pos.x, pos.y + eps, pos.z}, obj),
							SDF((t_vector3d){pos.x, pos.y, pos.z + eps}, obj)},
									(t_vector3d){basic_dist, basic_dist, basic_dist}));
}

static float	find_intersect_and_normal(t_vector3d start_ray, t_vector3d dir_ray,
		t_scene *scene, t_object3d *closest_obj, t_vector3d *normal)
{
	float		intersect_dist = 0.f;
	float		dist_to_obj;
	int			max_steps = 100;
	float		epsilon = 0.001;
	t_vector3d	cur_ray_point;

	for (int i = 0; i < max_steps; i++)
	{
		cur_ray_point = mv_plus(start_ray, mv_mult_num(dir_ray, intersect_dist));
		dist_to_obj = sceneSDF(cur_ray_point, scene, closest_obj);
		if (dist_to_obj < epsilon)
		{
			get_normal(cur_ray_point, dist_to_obj, normal, closest_obj);
		//	printf("check\n");
			return (intersect_dist);
		}
		intersect_dist += dist_to_obj;
		if (intersect_dist > scene->max_distance)
			return (-1);
	}
	return (-1);
}

t_vector3d	ray_marching(t_vector3d start_ray, t_vector3d dir_ray, t_scene *scene)
{
	t_vector3d	color;
	float		intersect_dist = 0;
	t_object3d	closest_obj;
	t_vector3d	normal;

	if ((intersect_dist = find_intersect_and_normal(start_ray, dir_ray, scene, &closest_obj, &normal)) >= 0)
	{
		color = mv_plus(mv_mult_num(normal, 0.5), (t_vector3d){0.5, 0.5, 0.5});
//		color = (t_vector3d){0.8, 0.2, 0.2};
	}
	else
	{
		color = mv_minus((t_vector3d){0.36, 0.36, 0.6}, (t_vector3d){dir_ray.y * 0.6, -dir_ray.y * 0.6, dir_ray.y * 0.6});
	}
	return (color);
}

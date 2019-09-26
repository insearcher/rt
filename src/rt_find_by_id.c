#include "rt.h"

t_transform	*rt_find_transform_by_id(t_scene *scene, cl_uint id)
{
	t_transform	*res;
	cl_uint		i;

	if (scene->camera.transform.id == id)
		return (&scene->camera.transform);
	i = -1;
	while (++i < scene->objects->size)
	{
		res = &((t_object *)vec_at(scene->objects, i))->transform;
		if (res->id == id)
			return (res);
	}
	i = -1;
	while (++i < scene->lights->size)
	{
		res = &((t_light *)vec_at(scene->lights, i))->transform;
		if (res->id == id)
			return (res);
	}
	return (NULL);
}

t_object	*rt_find_object_by_id(t_vec *objects, cl_uint id)
{
	t_object	*res;
	cl_uint		i;

	i = -1;
	while (++i < objects->size)
	{
		res = (t_object *)vec_at(objects, i);
		if (res->transform.id == id)
			return (res);
	}
	return (NULL);
}

t_light		*rt_find_light_by_id(t_vec *lights, cl_uint id)
{
	t_light	*res;
	cl_uint	i;

	i = -1;
	while (++i < lights->size)
	{
		res = (t_light *)vec_at(lights, i);
		if (res->transform.id == id)
			return (res);
	}
	return (NULL);
}

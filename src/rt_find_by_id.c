#include "rt.h"

t_object	*rt_find_object_by_id(t_object *objs, cl_uint objs_count, cl_uint id)
{
	cl_uint	i;

	i = -1;
	while (++i < objs_count)
	{
		if (objs[i].transform.id == id)
			return (&(objs[i]));
	}
	return (NULL);
}

t_transform	*rt_find_transform_by_id(t_scene *scene, cl_uint id)
{
	cl_uint	i;
	t_object	*objs;
	t_light		*lights;

	objs = scene->objects;
	lights = scene->lights;
	if (scene->camera.transform.id == id)
		return (&scene->camera.transform);
	i = -1;
	while (++i < scene->lights_count)
	{
		if (lights[i].transform.id == id)
			return (&lights[i].transform);
	}
	i = -1;
	while (++i < scene->objects_count)
	{
		if (objs[i].transform.id == id)
			return (&objs[i].transform);
	}
	return (NULL);
}

t_light	*rt_find_light_by_id(t_light *lights, cl_uint lights_count, cl_uint id)
{
	cl_uint	i;

	i = -1;
	while (++i < lights_count)
	{
		if (lights[i].transform.id == id)
			return (&(lights[i]));
	}
	return (NULL);
}

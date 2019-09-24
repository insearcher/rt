#include "rt.h"
#include "rt_jtoc.h"
#include "rt_raycast.h"

int	rt_jtoc_get_object_type(t_object *obj, t_jnode *n)
{
	char	*str;
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "type")) || tmp->type != string)
		return (rt_jtoc_sdl_log_error("TYPE ERROR OR TYPE IS MISSING", -1));
	str = jtoc_get_string(tmp);
	obj->type = 0;
	obj->type = ft_strcmp(str, "sphere") ? obj->type : o_sphere;
	obj->type = ft_strcmp(str, "box") ? obj->type : o_box;
	obj->type = ft_strcmp(str, "round_box") ? obj->type : o_round_box;
	obj->type = ft_strcmp(str, "torus") ? obj->type : o_torus;
	obj->type = ft_strcmp(str, "capped_torus") ? obj->type : o_capped_torus;
	obj->type = ft_strcmp(str, "link") ? obj->type : o_link;
	obj->type = ft_strcmp(str, "cylinder") ? obj->type : o_cylinder;
	obj->type = ft_strcmp(str, "cone") ? obj->type : o_cone;
	obj->type = ft_strcmp(str, "plane") ? obj->type : o_plane;
	obj->type = ft_strcmp(str, "mandelbulb") ? obj->type : o_mandelbulb;
	obj->type = ft_strcmp(str, "mandelbox") ? obj->type : o_mandelbox;
	if (obj->type == 0)
		return (FUNCTION_FAILURE);
	return (FUNCTION_SUCCESS);
}

int	rt_jtoc_get_object_layer(t_object *obj, t_jnode *n)
{
	t_jnode	*tmp;
	char	*str;

	if (!(tmp = jtoc_node_get_by_path(n, "layer")) || tmp->type != string)
		return (rt_jtoc_sdl_log_error("LAYER ERROR OR LAYER IS MISSING", -1));
	str = jtoc_get_string(tmp);
	obj->layer = 0;
	obj->layer |= ft_strcmp(str, "default_layer") ? DEFAULT_LAYER : obj->layer;
	obj->layer |= ft_strcmp(str, "ignore_raycast_layer") ? IGNORE_RAYCAST_LAYER : obj->layer;
	if (obj->layer == 0)
		obj->layer = DEFAULT_LAYER;
	return (FUNCTION_SUCCESS);
}

int	rt_jtoc_check_and_get_id_for_objs(t_object *obj, t_jnode *n, t_scene *scene, cl_uint objs_num)
{
	t_jnode		*tmp;
	cl_uint		id;

	id = 0;
	if ((tmp = jtoc_node_get_by_path(n, "id")) && tmp->type == integer)
	{
		id = jtoc_get_int(tmp);
		if (id <= 0)
			return (FUNCTION_FAILURE);
		if (scene->camera.transform.id == (cl_uint)id)
			return (rt_jtoc_sdl_log_error("THAT ID ALREADY EXISTS IN CAMERA", id));
		if (rt_find_light_by_id(scene->lights, scene->lights_count, id))
			return (rt_jtoc_sdl_log_error("THAT ID ALREADY EXISTS IN LIGHTS", id));
		if (objs_num != 0)
			if (rt_find_object_by_id(scene->objects, objs_num - 1, id) != NULL)
				return (rt_jtoc_sdl_log_error("THAT ID ALREADY EXISTS IN OBJECTS", id));
	}
	obj->transform.id = (cl_uint)id;
	return (FUNCTION_SUCCESS);
}

int	rt_jtoc_get_object(t_object *obj, t_jnode *n, t_scene *scene, cl_uint objs_num)
{
	t_jnode	*tmp;
	int		err;

	ft_bzero(obj, sizeof(t_object));
	if (rt_jtoc_get_object_type(obj, n))
		return (rt_jtoc_sdl_log_error("NOT VALID TYPE", -1));
	if (rt_jtoc_get_object_layer(obj, n))
		return (rt_jtoc_sdl_log_error("NOT VALID LAYER", -1));
	if (rt_jtoc_get_transform(&obj->transform, n))
		return (rt_jtoc_sdl_log_error("TRANSFORM ERROR", -1));
	if (!(tmp = jtoc_node_get_by_path(n, "color")) || tmp->type != object)
		return (rt_jtoc_sdl_log_error("COLOR TYPE ERROR OR COLOR IS MISSING", -1));
	if (rt_jtoc_get_float4(&obj->material.color, tmp))
		return (rt_jtoc_sdl_log_error("COLOR ERROR", -1));
	if (rt_jtoc_check_and_get_id_for_objs(obj, n, scene, objs_num))
		return (rt_jtoc_sdl_log_error("ID ERROR", -1));

	err = 0;
	err = obj->type == o_sphere ? rt_jtoc_get_sphere(obj, n) : err;
	err = obj->type == o_box ? rt_jtoc_get_box(obj, n) : err;
	err = obj->type == o_round_box ? rt_jtoc_get_round_box(obj, n) : err;
	err = obj->type == o_torus ? rt_jtoc_get_torus(obj, n) : err;
	err = obj->type == o_plane ? rt_jtoc_get_plane(obj, n) : err;
	err = obj->type == o_cone ? rt_jtoc_get_cone(obj, n) : err;
	err = obj->type == o_cylinder ? rt_jtoc_get_cylinder(obj, n) : err;
	err = obj->type == o_link ? rt_jtoc_get_link(obj, n) : err;
	err = obj->type == o_mandelbulb ? rt_jtoc_get_mandelbulb(obj, n) : err;
	err = obj->type == o_mandelbox ? rt_jtoc_get_mandelbox(obj, n) : err;
	if (err != 0)
		return (FUNCTION_FAILURE);

	return (FUNCTION_SUCCESS);
}

int	rt_jtoc_get_objects(t_scene *scene, t_jnode *n)
{
	t_jnode		*tmp;
	t_object	*objects;
	int			i;

	scene->objects_count = 0;
	if (rt_jtoc_get_objects_num_in_arr(&scene->objects_count, n))
		return (FUNCTION_FAILURE);
	objects = ft_x_memalloc(sizeof(t_object) * scene->objects_count);
	scene->objects = objects;
	tmp = n->down;
	i = 0;
	while (tmp)
	{
		if (tmp->type != object)
			return (rt_jtoc_sdl_log_error("OBJECT TYPE ERROR", i));
		if (rt_jtoc_get_object(&(objects[i]), tmp, scene, (cl_uint)i))
			return (rt_jtoc_sdl_log_error("OBJECT DATA ERROR", i));
		i++;
		tmp = tmp->right;
	}
	return (FUNCTION_SUCCESS);
}

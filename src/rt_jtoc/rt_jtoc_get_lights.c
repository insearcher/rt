//
// Created by Slaughterfish Becker on 2019-09-15.
//

#include "rt.h"
#include "rt_jtoc.h"

int		check_lights_and_get_lights_count(unsigned int *lights_num, t_jnode *n)
{
	t_jnode	*tmp;

	if ((!(tmp = jtoc_node_get_by_path(n, "ambient")) || tmp->type != object) &&
		(!(tmp = jtoc_node_get_by_path(n, "directional_lights")) || tmp->type != array) &&
		(!(tmp = jtoc_node_get_by_path(n, "point_lights")) || tmp->type != array))
		return (FUNCTION_FAILURE);
	if (rt_jtoc_get_objects_num_in_arr(lights_num, jtoc_node_get_by_path(n, "directional_lights")))
		return (FUNCTION_FAILURE);
	if (rt_jtoc_get_objects_num_in_arr(lights_num, jtoc_node_get_by_path(n, "point_lights")))
		return (FUNCTION_FAILURE);
	return (FUNCTION_SUCCESS);
}

int		rt_jtoc_check_and_get_id_for_lights(t_scene *scene, t_jnode *n, t_light *lights, int cur_light)
{
	t_jnode	*tmp;
	int		id;

	if (!(tmp = jtoc_node_get_by_path(n, "id")) || tmp->type != integer)
		return (FUNCTION_SUCCESS);
	id = jtoc_get_int(tmp);
	if (id <= 0)
		return (rt_jtoc_sdl_log_error("ID ERROR", -1));
	if (scene->camera.transform.id == id)
		return (rt_jtoc_sdl_log_error("THAT ID ALREADY EXISTS IN CAMERA", id));
	if (cur_light != 0)
		if (rt_find_light_by_id(lights, cur_light - 1, id) != NULL)
			return (rt_jtoc_sdl_log_error("THAT ID ALREADY EXISTS IN LIGHTS", id));
	lights[cur_light].transform.id = id;
	return (FUNCTION_SUCCESS);
}

int		get_directional_lights(t_scene *scene, t_light *lights, int *cur_light, t_jnode *n)
{
	t_jnode	*tmp;
	t_jnode	*tmp2;
	int		i;

	if (n == NULL)
		return (FUNCTION_SUCCESS);
	i = *cur_light;
	tmp = n->down;
	while (tmp)
	{
		if (tmp->type != object)
			return (rt_jtoc_sdl_log_error("TYPE ERROR", -1));
		lights[i].type = directional;

		if (!(tmp2 = jtoc_node_get_by_path(tmp, "color")) || tmp2->type != object)
			return (rt_jtoc_sdl_log_error("COLOR TYPE ERROR OR COLOR IS MISSING", -1));
		if (rt_jtoc_get_float3(&(lights[i].params.directional.color), tmp2))
			return (rt_jtoc_sdl_log_error("COLOR ERROR", -1));

		if (rt_jtoc_get_transform(&(lights[i].transform), tmp))
			return (rt_jtoc_sdl_log_error("TRANSFORM ERROR", -1));

		if (rt_jtoc_check_and_get_id_for_lights(scene, tmp, lights, *cur_light))
			return (rt_jtoc_sdl_log_error("ID ERROR", -1));

		i++;
		tmp = tmp->right;
	}
	*cur_light = i;
	return (FUNCTION_SUCCESS);
}

int		get_point_lights(t_scene *scene, t_light *lights, int *cur_light, t_jnode *n)
{
	t_jnode	*tmp;
	t_jnode	*tmp2;
	int		i;

	if (n == NULL)
		return (FUNCTION_SUCCESS);
	i = *cur_light;
	tmp = n->down;
	while (tmp)
	{
		if (tmp->type != object)
			return (rt_jtoc_sdl_log_error("TYPE ERROR", -1));

		lights[i].type = point;

		if (!(tmp2 = jtoc_node_get_by_path(tmp, "color")) || tmp2->type != object)
			return (rt_jtoc_sdl_log_error("COLOR TYPE ERROR OR COLOR IS MISSING", -1));
		if (rt_jtoc_get_float3(&(lights[i].params.point.color), tmp2))
			return (rt_jtoc_sdl_log_error("COLOR ERROR", -1));

		if (rt_jtoc_get_transform(&(lights[i].transform), tmp))
			return (rt_jtoc_sdl_log_error("TRANSFORM ERROR", -1));

		if (!(tmp2 = jtoc_node_get_by_path(tmp, "distance")) || tmp2->type != fractional)
			return (rt_jtoc_sdl_log_error("DISTANCE TYPE ERROR OR DISTANCE IS MISSING", -1));
		lights[i].params.point.distance = jtoc_get_float(tmp2);

		if (rt_jtoc_check_and_get_id_for_lights(scene, tmp, lights, *cur_light))
			return (rt_jtoc_sdl_log_error("ID ERROR", -1));

		i++;
		tmp = tmp->right;
	}
	*cur_light = i;
	return (FUNCTION_SUCCESS);
}

int	rt_jtoc_get_lights(t_scene *scene, t_jnode *n)
{
	t_jnode	*tmp;
	t_light	*lights;
	int		cur_light;

	scene->lights_count = 0;
	if (check_lights_and_get_lights_count(&(scene->lights_count), n))
		return (rt_jtoc_sdl_log_error("LIGHTS IS NOT SET OR LIGHT TYPE ERROR", -1));
	if ((tmp = jtoc_node_get_by_path(n, "ambient")) && tmp->type == object)
		if (rt_jtoc_get_float3(&(scene->ambient), tmp))
			return (rt_jtoc_sdl_log_error("AMBIENT ERROR", -1));

	if (scene->lights_count != 0)
	{
		lights = (t_light *)ft_x_memalloc(sizeof(t_light) * scene->lights_count);
		cur_light = 0;
		if (get_directional_lights(scene, lights, &cur_light, jtoc_node_get_by_path(n, "directional_lights")))
			return (rt_jtoc_sdl_log_error("DIRECTIONAL LIGHTS ERROR", -1));
		if (get_point_lights(scene, lights, &cur_light, jtoc_node_get_by_path(n, "point_lights")))
			return (rt_jtoc_sdl_log_error("POINT LIGHTS ERROR", -1));
		scene->lights = lights;
	}
	return (FUNCTION_SUCCESS);
}

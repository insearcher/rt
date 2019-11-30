/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_jtoc_get_lights.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:15:06 by sbednar           #+#    #+#             */
/*   Updated: 2019/09/26 14:15:43 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int		rt_jtoc_check_and_get_id_for_light(t_scene *scene,
		t_jnode *n, t_light *light)
{
	t_jnode		*tmp;
	cl_uint		id;

	if (!(tmp = jtoc_node_get_by_path(n, "id")) || tmp->type != integer)
		return (FUNCTION_SUCCESS);
	id = jtoc_get_int(tmp);
	if (id <= 0)
		return (rt_jtoc_sdl_log_error("ID ERROR", -1));
	if (scene->camera.transform.id == (cl_uint)id)
		return (rt_jtoc_sdl_log_error("THAT ID ALREADY EXISTS IN CAMERA", id));
	if (rt_find_light_by_id(scene->lights, id) != NULL)
		return (rt_jtoc_sdl_log_error("THAT ID ALREADY EXISTS IN LIGHTS", id));
	light->transform.id = (cl_uint)id;
	return (FUNCTION_SUCCESS);
}

int		get_directional_lights(t_scene *scene, t_jnode *n)
{
	t_light	light;
	t_jnode	*tmp;
	t_jnode	*tmp2;

	if (n == NULL)
		return (FUNCTION_SUCCESS);
	tmp = n->down;
	while (tmp)
	{
		if (tmp->type != object)
			return (rt_jtoc_sdl_log_error("TYPE ERROR", -1));
		ft_bzero(&light, sizeof(t_light));
		light.type = directional;
		if (!(tmp2 = jtoc_node_get_by_path(tmp, "color")) || tmp2->type != object)
			return (rt_jtoc_sdl_log_error("COLOR TYPE ERROR OR COLOR IS MISSING", -1));
		if (rt_jtoc_get_float3(&light.params.directional.color, tmp2) ||
			rt_jtoc_is01_float3(&light.params.directional.color))
			return (rt_jtoc_sdl_log_error("COLOR ERROR", -1));
		if (rt_jtoc_get_transform(&light.transform, tmp))
			return (rt_jtoc_sdl_log_error("TRANSFORM ERROR", -1));
		if (rt_jtoc_check_and_get_id_for_light(scene, tmp, &light))
			return (rt_jtoc_sdl_log_error("ID ERROR", -1));
		vec_push_back(scene->lights, &light);
		tmp = tmp->right;
	}
	return (FUNCTION_SUCCESS);
}

int		get_point_lights(t_scene *scene, t_jnode *n)
{
	t_light	light;
	t_jnode	*tmp;
	t_jnode	*tmp2;

	if (n == NULL)
		return (FUNCTION_SUCCESS);
	tmp = n->down;
	while (tmp)
	{
		if (tmp->type != object)
			return (rt_jtoc_sdl_log_error("TYPE ERROR", -1));
		ft_bzero(&light, sizeof(t_light));
		light.type = point;
		if (!(tmp2 = jtoc_node_get_by_path(tmp, "color")) || tmp2->type != object)
			return (rt_jtoc_sdl_log_error("COLOR TYPE ERROR OR COLOR IS MISSING", -1));
		if (rt_jtoc_get_float3(&light.params.point.color, tmp2) ||
			rt_jtoc_is01_float3(&light.params.point.color))
			return (rt_jtoc_sdl_log_error("COLOR ERROR", -1));
		if (rt_jtoc_get_transform(&light.transform, tmp))
			return (rt_jtoc_sdl_log_error("TRANSFORM ERROR", -1));
		if (!(tmp2 = jtoc_node_get_by_path(tmp, "distance")) || tmp2->type != fractional)
			return (rt_jtoc_sdl_log_error("DISTANCE TYPE ERROR OR DISTANCE IS MISSING", -1));
		light.params.point.distance = jtoc_get_float(tmp2);
		if (light.params.point.distance <= 0)
			return (rt_jtoc_sdl_log_error("DISTANCE ERROR", -1));
		if (rt_jtoc_check_and_get_id_for_light(scene, tmp, &light))
			return (rt_jtoc_sdl_log_error("ID ERROR", -1));
		vec_push_back(scene->lights, &light);
		tmp = tmp->right;
	}
	return (FUNCTION_SUCCESS);
}

int	rt_jtoc_get_lights(t_scene *scene, t_jnode *n)
{
	t_jnode	*tmp;
	uint	c;

	c = 0;
	if (check_lights_and_get_lights_count(&c, n))
		return (rt_jtoc_sdl_log_error("LIGHTS IS NOT SET OR LIGHT TYPE ERROR", -1));
	if ((tmp = jtoc_node_get_by_path(n, "ambient")) && tmp->type == object)
		if (rt_jtoc_get_float3(&(scene->ambient), tmp) || rt_jtoc_ispos_float3(&scene->ambient))
			return (rt_jtoc_sdl_log_error("AMBIENT ERROR", -1));
	if (!(scene->lights = vec_init(c, sizeof(t_light))))
		return (FUNCTION_FAILURE);
	if (scene->lights->capacity > 0)
	{
		if (get_directional_lights(scene, jtoc_node_get_by_path(n, "directional_lights")))
			return (rt_jtoc_sdl_log_error("DIRECTIONAL LIGHTS ERROR", -1));
		if (get_point_lights(scene, jtoc_node_get_by_path(n, "point_lights")))
			return (rt_jtoc_sdl_log_error("POINT LIGHTS ERROR", -1));
	}
	return (FUNCTION_SUCCESS);
}

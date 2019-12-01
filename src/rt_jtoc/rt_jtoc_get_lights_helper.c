/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_jtoc_get_lights_helper.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 18:48:36 by edraugr-          #+#    #+#             */
/*   Updated: 2019/12/01 18:48:39 by edraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_jtoc.h"

static int	cagi(t_scene *scene, t_jnode *n, t_light *light)
{
	t_jnode	*tmp;
	cl_uint	id;

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

int gpl_helper(t_jnode	*t, t_scene *scene, t_light	*light)
{
	t_jnode	*p;

	if (t->type != object)
		return (rt_jtoc_sdl_log_error("TYPE ERROR", -1));
	ft_bzero(light, sizeof(t_light));
	light->type = point;
	if (!(p = jtoc_node_get_by_path(t, "color")) || p->type != object)
		return (rt_jtoc_sdl_log_error("COLOR ERROR", -1));
	if (rt_jtoc_get_float3(&light->params.point.color, p) ||
		rt_jtoc_is01_float3(&light->params.point.color))
		return (rt_jtoc_sdl_log_error("COLOR ERROR", -1));
	if (rt_jtoc_get_transform(&light->transform, t))
		return (rt_jtoc_sdl_log_error("TRANSFORM ERROR", -1));
	if (!(p = jtoc_node_get_by_path(t, "distance")) || p->type != fractional)
		return (rt_jtoc_sdl_log_error("DISTANCE ERROR", -1));
	light->params.point.distance = jtoc_get_float(p);
	if (light->params.point.distance <= 0)
		return (rt_jtoc_sdl_log_error("DISTANCE ERROR", -1));
	if (cagi(scene, t, light))
		return (rt_jtoc_sdl_log_error("ID ERROR", -1));
	vec_push_back(scene->lights, light);
	return (FUNCTION_SUCCESS);
}

int gdl_helper(t_jnode	*t, t_scene *scene, t_light	*light)
{
	t_jnode	*m;

	if (t->type != object)
		return (rt_jtoc_sdl_log_error("TYPE ERROR", -1));
	ft_bzero(light, sizeof(t_light));
	light->type = directional;
	if (!(m = jtoc_node_get_by_path(t, "color")) || m->type != object)
		return (rt_jtoc_sdl_log_error("COLOR ERROR", -1));
	if (rt_jtoc_get_float3(&light->params.directional.color, m) ||
		rt_jtoc_is01_float3(&light->params.directional.color))
		return (rt_jtoc_sdl_log_error("COLOR ERROR", -1));
	if (rt_jtoc_get_transform(&light->transform, t))
		return (rt_jtoc_sdl_log_error("TRANSFORM ERROR", -1));
	if (cagi(scene, t, light))
		return (rt_jtoc_sdl_log_error("ID ERROR", -1));
	vec_push_back(scene->lights, light);
	return (FUNCTION_SUCCESS);
}
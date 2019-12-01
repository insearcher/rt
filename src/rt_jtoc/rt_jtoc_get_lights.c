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

static int	claglc(unsigned int *lights_num, t_jnode *n)
{
	t_jnode	*t;

	if ((!(t = jtoc_node_get_by_path(n, "ambient")) || t->type != object) &&
		(!(t = jtoc_node_get_by_path(n, "directional_lights"))
		|| t->type != array) &&
		(!(t = jtoc_node_get_by_path(n, "point_lights")) || t->type != array))
		return (FUNCTION_FAILURE);
	if (rt_jtoc_get_objects_num_in_arr(lights_num,
		jtoc_node_get_by_path(n, "directional_lights")))
		return (FUNCTION_FAILURE);
	if (rt_jtoc_get_objects_num_in_arr(lights_num,
		jtoc_node_get_by_path(n, "point_lights")))
		return (FUNCTION_FAILURE);
	return (FUNCTION_SUCCESS);
}

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

static int	gdl(t_scene *scene, t_jnode *n)
{
	t_light	light;
	t_jnode	*t;
	t_jnode	*m;

	if (n == NULL)
		return (FUNCTION_SUCCESS);
	t = n->down;
	while (t)
	{
		if (t->type != object)
			return (rt_jtoc_sdl_log_error("TYPE ERROR", -1));
		ft_bzero(&light, sizeof(t_light));
		light.type = directional;
		if (!(m = jtoc_node_get_by_path(t, "color")) || m->type != object)
			return (rt_jtoc_sdl_log_error("COLOR ERROR", -1));
		if (rt_jtoc_get_float3(&light.params.directional.color, m) ||
			rt_jtoc_is01_float3(&light.params.directional.color))
			return (rt_jtoc_sdl_log_error("COLOR ERROR", -1));
		if (rt_jtoc_get_transform(&light.transform, t))
			return (rt_jtoc_sdl_log_error("TRANSFORM ERROR", -1));
		if (cagi(scene, t, &light))
			return (rt_jtoc_sdl_log_error("ID ERROR", -1));
		vec_push_back(scene->lights, &light);
		t = t->right;
	}
	return (FUNCTION_SUCCESS);
}

static int	gpl(t_scene *scene, t_jnode *n)
{
	t_light	light;
	t_jnode	*t;
	t_jnode	*p;

	if (n == NULL)
		return (FUNCTION_SUCCESS);
	t = n->down;
	while (t)
	{
		if (t->type != object)
			return (rt_jtoc_sdl_log_error("TYPE ERROR", -1));
		ft_bzero(&light, sizeof(t_light));
		light.type = point;
		if (!(p = jtoc_node_get_by_path(t, "color")) || p->type != object)
			return (rt_jtoc_sdl_log_error("COLOR ERROR", -1));
		if (rt_jtoc_get_float3(&light.params.point.color, p) ||
			rt_jtoc_is01_float3(&light.params.point.color))
			return (rt_jtoc_sdl_log_error("COLOR ERROR", -1));
		if (rt_jtoc_get_transform(&light.transform, t))
			return (rt_jtoc_sdl_log_error("TRANSFORM ERROR", -1));
		if (!(p = jtoc_node_get_by_path(t, "distance")) || p->type != fractional)
			return (rt_jtoc_sdl_log_error("DISTANCE ERROR", -1));
		light.params.point.distance = jtoc_get_float(p);
		if (light.params.point.distance <= 0)
			return (rt_jtoc_sdl_log_error("DISTANCE ERROR", -1));
		if (cagi(scene, t, &light))
			return (rt_jtoc_sdl_log_error("ID ERROR", -1));
		vec_push_back(scene->lights, &light);
		t = t->right;
	}
	return (FUNCTION_SUCCESS);
}

int		rt_jtoc_get_lights(t_scene *scene, t_jnode *n)
{
	t_jnode	*t;
	uint	c;

	c = 0;
	if (claglc(&c, n))
		return (rt_jtoc_sdl_log_error("LIGHTS ERROR", -1));
	if ((t = jtoc_node_get_by_path(n, "ambient")) && t->type == object)
		if (rt_jtoc_get_float3(&(scene->ambient), t)
			|| rt_jtoc_ispos_float3(&scene->ambient))
			return (rt_jtoc_sdl_log_error("AMBIENT ERROR", -1));
	if (!(scene->lights = vec_init(c, sizeof(t_light))))
		return (FUNCTION_FAILURE);
	if (scene->lights->capacity > 0)
	{
		if (gdl(scene,
				jtoc_node_get_by_path(n, "directional_lights")))
			return (rt_jtoc_sdl_log_error("DIRECTIONAL LIGHTS ERROR", -1));
		if (gpl(scene, jtoc_node_get_by_path(n, "point_lights")))
			return (rt_jtoc_sdl_log_error("POINT LIGHTS ERROR", -1));
	}
	return (FUNCTION_SUCCESS);
}

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

static int	gdl(t_scene *scene, t_jnode *n)
{
	t_light	light;
	t_jnode	*t;

	if (n == NULL)
		return (FUNCTION_SUCCESS);
	t = n->down;
	while (t)
	{
		if (gdl_helper(t, scene, &light))
			return (FUNCTION_FAILURE);
		t = t->right;
	}
	return (FUNCTION_SUCCESS);
}

static int	gpl(t_scene *scene, t_jnode *n)
{
	t_light	light;
	t_jnode	*t;

	if (n == NULL)
		return (FUNCTION_SUCCESS);
	t = n->down;
	while (t)
	{
		if (gpl_helper(t, scene, &light))
			return (FUNCTION_FAILURE);
		t = t->right;
	}
	return (FUNCTION_SUCCESS);
}

int			rt_jtoc_get_lights(t_scene *scene, t_jnode *n)
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

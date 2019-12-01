/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_jtoc_get_objects_params.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 05:13:21 by sbecker           #+#    #+#             */
/*   Updated: 2019/12/01 15:10:48 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_jtoc.h"

int			rt_jtoc_get_link(t_object *obj, t_jnode *n)
{
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "le")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("LE TYPE ERROR OR LE IS MISSING", -1));
	obj->params.link.le = jtoc_get_float(tmp);
	if (obj->params.link.le < 0)
		return (rt_jtoc_sdl_log_error("LE ERROR", -1));
	if (!(tmp = jtoc_node_get_by_path(n, "r1")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("R1 TYPE ERROR OR R1 IS MISSING", -1));
	obj->params.link.r1 = jtoc_get_float(tmp);
	if (obj->params.link.r1 <= 0)
		return (rt_jtoc_sdl_log_error("R1 ERROR", -1));
	if (!(tmp = jtoc_node_get_by_path(n, "r2")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("R2 TYPE ERROR OR R2 IS MISSING", -1));
	obj->params.link.r2 = jtoc_get_float(tmp);
	if (obj->params.link.r2 <= 0)
		return (rt_jtoc_sdl_log_error("R2 ERROR", -1));
	return (FUNCTION_SUCCESS);
}

int 		rt_jtoc_get_octahedron(t_object *obj, t_jnode *n)
{
	t_jnode *tmp;
	if (!(tmp = jtoc_node_get_by_path(n, "bounds")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("BOUNDS ERROR OR MISSING", -1));
	obj->params.octahedron.bounds = jtoc_get_float(tmp);
	if (obj->params.octahedron.bounds <= 0)
		return (rt_jtoc_sdl_log_error("BOUNDS ERROR", -1));
	return (FUNCTION_SUCCESS);
}

int			rt_jtoc_get_mandelbulb(t_object *obj, t_jnode *n)
{
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "power")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("POWER ERROR", -1));
	obj->params.mandelbulb.power = jtoc_get_float(tmp);
	if (!(tmp = jtoc_node_get_by_path(n, "iteration")) || tmp->type != integer)
		return (rt_jtoc_sdl_log_error("ITERTATION ERROR", -1));
	obj->params.mandelbulb.iteration = jtoc_get_int(tmp);
	if (!(tmp = jtoc_node_get_by_path(n, "breakout")) || tmp->type != integer)
		return (rt_jtoc_sdl_log_error("BREAKOUT ERROR", -1));
	obj->params.mandelbulb.breakout = jtoc_get_int(tmp);
	if (obj->params.mandelbulb.breakout <= 0 ||
		obj->params.mandelbulb.breakout >= 50)
		return (rt_jtoc_sdl_log_error("BREAKOUT ERROR", -1));
	return (FUNCTION_SUCCESS);
}

int			rt_jtoc_get_mandelbox(t_object *obj, t_jnode *n)
{
	t_jnode	*t;

	if (!(t = jtoc_node_get_by_path(n, "scale")) || t->type != fractional)
		return (rt_jtoc_sdl_log_error("POWER SCALE ERROR", -1));
	obj->params.mandelbox.scale = jtoc_get_float(t);
	if (obj->params.mandelbox.scale <= 0)
		return (rt_jtoc_sdl_log_error("SCALE ERROR", -1));
	if (!(t = jtoc_node_get_by_path(n, "fixedradius")) || t->type != fractional)
		return (rt_jtoc_sdl_log_error("FIXEDRADUIS TYPE ERROR", -1));
	obj->params.mandelbox.fixedradius = jtoc_get_float(t);
	if (obj->params.mandelbox.fixedradius <= 0)
		return (rt_jtoc_sdl_log_error("FIXED RADIUS ERROR", -1));
	if (!(t = jtoc_node_get_by_path(n, "minradius")) || t->type != fractional)
		return (rt_jtoc_sdl_log_error("MINRADIUS ERROR", -1));
	obj->params.mandelbox.minradius = jtoc_get_float(t);
	if (obj->params.mandelbox.minradius <= 0)
		return (rt_jtoc_sdl_log_error("MIN RADIUS ERROR", -1));
	if (!(t = jtoc_node_get_by_path(n, "iteration")) || t->type != integer)
		return (rt_jtoc_sdl_log_error("ITERTATION ERROR", -1));
	obj->params.mandelbox.iteration = jtoc_get_int(t);
	if (!(t = jtoc_node_get_by_path(n, "cube_size")) || t->type != object)
		return (rt_jtoc_sdl_log_error("CUBE SIZE ERROR", -1));
	if (rt_jtoc_get_float3(&obj->params.mandelbox.cube_size, t) ||
		rt_jtoc_ispos_float3(&obj->params.mandelbox.cube_size))
		return (rt_jtoc_sdl_log_error("CUBE SIZE ERROR", -1));
	return (FUNCTION_SUCCESS);
}

int			rt_jtoc_get_menger_sponge(t_object *obj, t_jnode *n)
{
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "scale")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("POWER ERROR", -1));
	obj->params.menger_sponge.scale = jtoc_get_float(tmp);
	if (obj->params.menger_sponge.scale <= 0)
		return (rt_jtoc_sdl_log_error("SCALE ERROR", -1));
	if (!(tmp = jtoc_node_get_by_path(n, "iteration")) || tmp->type != integer)
		return (rt_jtoc_sdl_log_error("ITERTATION ERROR", -1));
	obj->params.menger_sponge.iteration = jtoc_get_int(tmp);
	if (!(tmp = jtoc_node_get_by_path(n, "offset")) || tmp->type != object)
		return (rt_jtoc_sdl_log_error("OFFSET ERROR", -1));
	if (rt_jtoc_get_float3(&obj->params.menger_sponge.offset, tmp))
		return (rt_jtoc_sdl_log_error("OFFSET ERROR", -1));
	return (FUNCTION_SUCCESS);
}

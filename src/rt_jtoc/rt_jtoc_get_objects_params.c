/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_jtoc_get_objects_params.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 05:13:21 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/03 20:16:18 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_jtoc.h"

int			rt_jtoc_get_sphere(t_object *obj, t_jnode *n)
{
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "radius")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("RADIUS TYPE ERROR OR RADIUS IS MISSING", -1));
	obj->params.sphere.radius = jtoc_get_float(tmp);
	if (obj->params.sphere.radius <= 0 || obj->params.sphere.radius >= 1000)
		return (rt_jtoc_sdl_log_error("RADIUS ERROR", -1));
	return (FUNCTION_SUCCESS);
}

int			rt_jtoc_get_box(t_object *obj, t_jnode *n)
{
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "bounds")) || tmp->type != object)
		return (rt_jtoc_sdl_log_error("BOUNDS TYPE ERROR OR BOUNDS IS MISSING", -1));
	if (rt_jtoc_get_float3(&obj->params.box.bounds, tmp) ||
		rt_jtoc_ispos_float3(&obj->params.box.bounds))
		return (rt_jtoc_sdl_log_error("BOUNDS ERROR", -1));
	return (FUNCTION_SUCCESS);
}

int			rt_jtoc_get_round_box(t_object *obj, t_jnode *n)
{
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "bounds")) || tmp->type != object)
		return (rt_jtoc_sdl_log_error("BOUNDS TYPE ERROR OR BOUNDS IS MISSING", -1));
	if (rt_jtoc_get_float3(&obj->params.round_box.bounds, tmp))
		return (rt_jtoc_sdl_log_error("BOUNDS ERROR", -1));
	if (rt_jtoc_ispos_float3(&obj->params.round_box.bounds))
		return (rt_jtoc_sdl_log_error("BOUNDS ERROR", -1));
	if (!(tmp = jtoc_node_get_by_path(n, "rounding_radius")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("ROUNDING_RADIUS TYPE ERROR"
			" OR ROUNDING_RADIUS IS MISSING", -1));
	obj->params.round_box.r = jtoc_get_float(tmp);
	if (obj->params.round_box.r <= 0 || obj->params.round_box.r >= 1000)
		return (rt_jtoc_sdl_log_error("RADIUS ERROR", -1));
	return (FUNCTION_SUCCESS);
}

int			rt_jtoc_get_torus(t_object *obj, t_jnode *n)
{
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "radius")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("RADIUS TYPE ERROR OR RADIUS IS MISSING", -1));
	obj->params.torus.radius = jtoc_get_float(tmp);
	if (obj->params.torus.radius <= 0 || obj->params.torus.radius >= 1000)
		return (rt_jtoc_sdl_log_error("RADIUS ERROR", -1));
	if (!(tmp = jtoc_node_get_by_path(n, "inner_radius")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("INNER_RADIUS TYPE ERROR"
			" OR INNER_RADIUS IS MISSING", -1));
	obj->params.torus.inner_radius = jtoc_get_float(tmp);
	if (obj->params.torus.inner_radius <= 0 || obj->params.torus.inner_radius >= 1000)
		return (rt_jtoc_sdl_log_error("INNER RADIUS ERROR", -1));
	return (FUNCTION_SUCCESS);
}

int			rt_jtoc_get_plane(t_object *obj, t_jnode *n)
{
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "distance")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("DISTANCE TYPE ERROR OR DISTANCE IS MISSING", -1));
	obj->params.plane.distance = jtoc_get_float(tmp);
	if (obj->params.plane.distance >= 1000)
		return (rt_jtoc_sdl_log_error("DISTANCE ERROR", -1));
	return (FUNCTION_SUCCESS);
}

int			rt_jtoc_get_cone(t_object *obj, t_jnode *n)
{
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "params")) || tmp->type != object)
		return (rt_jtoc_sdl_log_error("PARAMS TYPE ERROR OR PARAMS IS MISSING", -1));
	if (rt_jtoc_get_float2(&obj->params.cone.c, tmp) ||
			rt_jtoc_ispos_float2(&obj->params.cone.c))
		return (rt_jtoc_sdl_log_error("PARAMS ERROR", -1));
	return (FUNCTION_SUCCESS);
}

int			rt_jtoc_get_cylinder(t_object *obj, t_jnode *n)
{
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "params")) || tmp->type != object)
		return (rt_jtoc_sdl_log_error("PARAMS TYPE ERROR OR PARAMS IS MISSING", -1));
	if (rt_jtoc_get_float3(&obj->params.cylinder.params, tmp) ||
			rt_jtoc_ispos_float3(&obj->params.cylinder.params))
		return (rt_jtoc_sdl_log_error("PARAMS ERROR", -1));
	return (FUNCTION_SUCCESS);
}

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
		return (rt_jtoc_sdl_log_error("POWER TYPE ERROR OR POWER IS MISSING", -1));
	obj->params.mandelbulb.power = jtoc_get_float(tmp);
	if (!(tmp = jtoc_node_get_by_path(n, "iteration")) || tmp->type != integer)
		return (rt_jtoc_sdl_log_error("ITERTATION TYPE ERROR OR ITERTATION IS MISSING", -1));
	obj->params.mandelbulb.iteration = jtoc_get_int(tmp);
	if (!(tmp = jtoc_node_get_by_path(n, "breakout")) || tmp->type != integer)
		return (rt_jtoc_sdl_log_error("BREAKOUT TYPE ERROR OR BREAKOUT IS MISSING", -1));
	obj->params.mandelbulb.breakout = jtoc_get_int(tmp);
	if (obj->params.mandelbulb.breakout <= 0 ||
		obj->params.mandelbulb.breakout >= 50)
		return (rt_jtoc_sdl_log_error("BREAKOUT ERROR", -1));
	return (FUNCTION_SUCCESS);
}

int			rt_jtoc_get_mandelbox(t_object *obj, t_jnode *n)
{
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "scale")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("POWER SCALE ERROR OR SCALE IS MISSING", -1));
	obj->params.mandelbox.scale = jtoc_get_float(tmp);
	if (obj->params.mandelbox.scale <= 0)
		return (rt_jtoc_sdl_log_error("SCALE ERROR", -1));
	if (!(tmp = jtoc_node_get_by_path(n, "fixedradius")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("FIXEDRADUIS TYPE ERROR OR FIXEDRADIUS IS MISSING", -1));
	obj->params.mandelbox.fixedradius = jtoc_get_float(tmp);
	if (obj->params.mandelbox.fixedradius <= 0)
		return (rt_jtoc_sdl_log_error("FIXED RADIUS ERROR", -1));
	if (!(tmp = jtoc_node_get_by_path(n, "minradius")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("MINRADIUS TYPE ERROR OR MINRADIUS IS MISSING", -1));
	obj->params.mandelbox.minradius = jtoc_get_float(tmp);
	if (obj->params.mandelbox.minradius <= 0)
		return (rt_jtoc_sdl_log_error("MIN RADIUS ERROR", -1));
	if (!(tmp = jtoc_node_get_by_path(n, "iteration")) || tmp->type != integer)
		return (rt_jtoc_sdl_log_error("ITERTATION TYPE ERROR OR ITERTATION IS MISSING", -1));
	obj->params.mandelbox.iteration = jtoc_get_int(tmp);
	if (!(tmp = jtoc_node_get_by_path(n, "cube_size")) || tmp->type != object)
		return (rt_jtoc_sdl_log_error("CUBE SIZE TYPE ERROR OR CUBE SIZE IS MISSING", -1));
	if (rt_jtoc_get_float3(&obj->params.mandelbox.cube_size, tmp) ||
		rt_jtoc_ispos_float3(&obj->params.mandelbox.cube_size))
		return (rt_jtoc_sdl_log_error("CUBE SIZE ERROR", -1));
	return (FUNCTION_SUCCESS);
}

int			rt_jtoc_get_menger_sponge(t_object *obj, t_jnode *n)
{
    t_jnode	*tmp;

    if (!(tmp = jtoc_node_get_by_path(n, "scale")) || tmp->type != fractional)
        return (rt_jtoc_sdl_log_error("POWER SCALE ERROR OR SCALE IS MISSING", -1));
    obj->params.menger_sponge.scale = jtoc_get_float(tmp);
	if (obj->params.menger_sponge.scale <= 0)
		return (rt_jtoc_sdl_log_error("SCALE ERROR", -1));
    if (!(tmp = jtoc_node_get_by_path(n, "iteration")) || tmp->type != integer)
    	return (rt_jtoc_sdl_log_error("ITERTATION TYPE ERROR OR ITERTATION IS MISSING", -1));
    obj->params.menger_sponge.iteration = jtoc_get_int(tmp);
    if (!(tmp = jtoc_node_get_by_path(n, "offset")) || tmp->type != object)
        return (rt_jtoc_sdl_log_error("OFFSET TYPE ERROR OR OFFSET IS MISSING", -1));
    if (rt_jtoc_get_float3(&obj->params.menger_sponge.offset, tmp))
        return (rt_jtoc_sdl_log_error("OFFSET ERROR", -1));
    return (FUNCTION_SUCCESS);
}
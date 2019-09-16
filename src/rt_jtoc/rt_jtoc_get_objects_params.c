#include "rt.h"
#include "rt_jtoc.h"

int			rt_jtoc_get_sphere(t_object *obj, t_jnode *n)
{
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "radius")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("RADIUS TYPE ERROR OR RADIUS IS MISSING", -1));
	obj->params.sphere.radius = jtoc_get_float(tmp);
	return (FUNCTION_SUCCESS);
}

int			rt_jtoc_get_box(t_object *obj, t_jnode *n)
{
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "bounds")) || tmp->type != object)
		return (rt_jtoc_sdl_log_error("BOUNDS TYPE ERROR OR BOUNDS IS MISSING", -1));
	if (rt_jtoc_get_float3(&obj->params.box.bounds, tmp))
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
	if (!(tmp = jtoc_node_get_by_path(n, "rounding_radius")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("ROUNDING_RADIUS TYPE ERROR"
									  " OR ROUNDING_RADIUS IS MISSING", -1));
	obj->params.round_box.r = jtoc_get_float(tmp);
	return (FUNCTION_SUCCESS);
}

int			rt_jtoc_get_torus(t_object *obj, t_jnode *n)
{
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "radius")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("RADIUS TYPE ERROR OR RADIUS IS MISSING", -1));
	obj->params.torus.radius = jtoc_get_float(tmp);
	if (!(tmp = jtoc_node_get_by_path(n, "inner_radius")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("INNER_RADIUS TYPE ERROR"
								" OR INNER_RADIUS IS MISSING", -1));
	obj->params.torus.inner_radius = jtoc_get_float(tmp);
	return (FUNCTION_SUCCESS);
}

int			rt_jtoc_get_plane(t_object *obj, t_jnode *n)
{
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "distance")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("DISTANCE TYPE ERROR OR DISTANCE IS MISSING", -1));
	obj->params.plane.distance = jtoc_get_float(tmp);
	return (FUNCTION_SUCCESS);
}

int			rt_jtoc_get_cone(t_object *obj, t_jnode *n)
{
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "params")) || tmp->type != object)
		return (rt_jtoc_sdl_log_error("PARAMS TYPE ERROR OR PARAMS IS MISSING", -1));
	if (rt_jtoc_get_float2(&obj->params.cone.c, tmp))
		return (rt_jtoc_sdl_log_error("PARAMS ERROR", -1));
	return (FUNCTION_SUCCESS);
}

int			rt_jtoc_get_cylinder(t_object *obj, t_jnode *n)
{
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "params")) || tmp->type != object)
		return (rt_jtoc_sdl_log_error("PARAMS TYPE ERROR OR PARAMS IS MISSING", -1));
	if (rt_jtoc_get_float3(&obj->params.cylinder.params, tmp))
		return (rt_jtoc_sdl_log_error("PARAMS ERROR", -1));
	return (FUNCTION_SUCCESS);
}

int			rt_jtoc_get_link(t_object *obj, t_jnode *n)
{
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "le")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("LE TYPE ERROR OR LE IS MISSING", -1));
	obj->params.link.le = jtoc_get_float(tmp);
	if (!(tmp = jtoc_node_get_by_path(n, "r1")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("R1 TYPE ERROR OR R1 IS MISSING", -1));
	obj->params.link.r1 = jtoc_get_float(tmp);
	if (!(tmp = jtoc_node_get_by_path(n, "r2")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("R2 TYPE ERROR OR R2 IS MISSING", -1));
	obj->params.link.r2 = jtoc_get_float(tmp);
	return (FUNCTION_SUCCESS);
}

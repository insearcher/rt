//
// Created by Slaughterfish Becker on 2019-09-13.
//

#include "rt.h"
#include "rt_jtoc.h"

static int	rt_jtoc_get_clipping_planes(t_clipping *clipping_planes, t_jnode *n)
{
	t_jnode	*tmp;

	if (!(n = jtoc_node_get_by_path(n, "clipping_planes")) || n->type != object)
		return (rt_jtoc_sdl_log_error("CLIPPING_PLANES TYPE ERROR OR CLIPPING_PLANES MISSING", -1));
	if (!(tmp = jtoc_node_get_by_path(n, "near")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("NEAR ERROR", -1));
	clipping_planes->near = jtoc_get_float(tmp);
	if (!(tmp = jtoc_node_get_by_path(n, "far")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("FAR ERROR", -1));
	clipping_planes->far = jtoc_get_float(tmp);
	return (FUNCTION_SUCCESS);
}

int			rt_jtoc_get_camera(t_camera *camera, t_jnode *n)
{
	t_jnode		*tmp;
	int			i;

	ft_bzero(camera, sizeof(t_camera));
	if (!(tmp = jtoc_node_get_by_path(n, "fov")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("FOV ERROR", -1));
	camera->fov = jtoc_get_float(tmp);
	if (rt_jtoc_get_clipping_planes(&(camera->clipping_planes), n))
		return (rt_jtoc_sdl_log_error("CLIPPING_PLANES ERROR", -1));
	if (rt_jtoc_get_transform(&(camera->transform), n))
		return (rt_jtoc_sdl_log_error("TRANSFORM ERROR", -1));

	if (!(tmp = jtoc_node_get_by_path(n, "id")) || tmp->type != integer)
		return (rt_jtoc_sdl_log_error("CAMERA ID ERROR", -1));
	i = jtoc_get_int(tmp);
	if (i <= 0)
		return (rt_jtoc_sdl_log_error("CAMERA ID ERROR", -1));
	camera->transform.id = i;

	return (FUNCTION_SUCCESS);
}

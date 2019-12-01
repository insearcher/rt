/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_jtoc_get_camera.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:15:06 by sbednar           #+#    #+#             */
/*   Updated: 2019/09/26 14:15:43 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_jtoc.h"

static int	rt_jtoc_get_clipping_planes(t_clipping *clipping_planes, t_jnode *n)
{
	t_jnode	*tmp;

	if (!(n = jtoc_node_get_by_path(n, "clipping_planes")) || n->type != object)
		return (rt_jtoc_sdl_log_error("CP TYPE ERROR OR CP MISSING", -1));
	if (!(tmp = jtoc_node_get_by_path(n, "near")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("NEAR ERROR", -1));
	clipping_planes->near = jtoc_get_float(tmp);
	if (clipping_planes->near < 0)
		return (rt_jtoc_sdl_log_error("NEAR ERROR", -1));
	if (!(tmp = jtoc_node_get_by_path(n, "far")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("FAR ERROR", -1));
	clipping_planes->far = jtoc_get_float(tmp);
	if (clipping_planes->far < 0 || clipping_planes->far
		<= clipping_planes->near)
		return (rt_jtoc_sdl_log_error("FAR ERROR", -1));
	return (FUNCTION_SUCCESS);
}

int			rt_jtoc_get_camera(t_camera *camera, t_jnode *n)
{
	t_jnode	*tmp;
	int		i;

	ft_bzero(camera, sizeof(t_camera));
	if (!(tmp = jtoc_node_get_by_path(n, "fov")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("FOV ERROR", -1));
	camera->fov = jtoc_get_float(tmp);
	if (camera->fov < 30 || camera->fov > 180)
		return (rt_jtoc_sdl_log_error("FOV ERROR", -1));
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

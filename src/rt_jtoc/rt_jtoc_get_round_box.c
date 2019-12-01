/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_jtoc_get_round_box.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 15:08:03 by sbednar           #+#    #+#             */
/*   Updated: 2019/12/01 15:31:30 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_jtoc.h"

int	rt_jtoc_get_round_box(t_object *obj, t_jnode *n)
{
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "bounds")) || tmp->type != object)
		return (rt_jtoc_sdl_log_error("BOUNDSERROR", -1));
	if (rt_jtoc_get_float3(&obj->params.round_box.bounds, tmp))
		return (rt_jtoc_sdl_log_error("BOUNDS ERROR", -1));
	if (rt_jtoc_ispos_float3(&obj->params.round_box.bounds))
		return (rt_jtoc_sdl_log_error("BOUNDS ERROR", -1));
	if (!(tmp = jtoc_node_get_by_path(n, "rounding_radius"))
		|| tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("ROUNDING_RADIUS ERROR", -1));
	obj->params.round_box.r = jtoc_get_float(tmp);
	if (obj->params.round_box.r <= 0 || obj->params.round_box.r >= 1000)
		return (rt_jtoc_sdl_log_error("RADIUS ERROR", -1));
	return (FUNCTION_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_jtoc_get_box.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 15:07:18 by sbednar           #+#    #+#             */
/*   Updated: 2019/12/01 15:07:18 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_jtoc.h"

int	rt_jtoc_get_box(t_object *obj, t_jnode *n)
{
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "bounds")) || tmp->type != object)
		return (rt_jtoc_sdl_log_error("BOUNDS ERROR", -1));
	if (rt_jtoc_get_float3(&obj->params.box.bounds, tmp) ||
		rt_jtoc_ispos_float3(&obj->params.box.bounds))
		return (rt_jtoc_sdl_log_error("BOUNDS ERROR", -1));
	return (FUNCTION_SUCCESS);
}

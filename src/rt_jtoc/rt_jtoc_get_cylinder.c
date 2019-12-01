/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_jtoc_get_cylinder.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 15:11:05 by sbednar           #+#    #+#             */
/*   Updated: 2019/12/01 15:11:05 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_jtoc.h"

int			rt_jtoc_get_cylinder(t_object *obj, t_jnode *n)
{
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "params")) || tmp->type != object)
		return (rt_jtoc_sdl_log_error("PARAMS ERROR", -1));
	if (rt_jtoc_get_float3(&obj->params.cylinder.params, tmp) ||
		rt_jtoc_ispos_float3(&obj->params.cylinder.params))
		return (rt_jtoc_sdl_log_error("PARAMS ERROR", -1));
	return (FUNCTION_SUCCESS);
}

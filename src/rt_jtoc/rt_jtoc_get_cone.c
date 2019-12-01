/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_jtoc_get_cone.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 15:10:17 by sbednar           #+#    #+#             */
/*   Updated: 2019/12/01 15:10:17 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_jtoc.h"

int			rt_jtoc_get_cone(t_object *obj, t_jnode *n)
{
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "params")) || tmp->type != object)
		return (rt_jtoc_sdl_log_error("PARAMS ERROR", -1));
	if (rt_jtoc_get_float2(&obj->params.cone.c, tmp) ||
		rt_jtoc_ispos_float2(&obj->params.cone.c))
		return (rt_jtoc_sdl_log_error("PARAMS ERROR", -1));
	return (FUNCTION_SUCCESS);
}

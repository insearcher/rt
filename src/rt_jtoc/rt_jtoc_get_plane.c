/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_jtoc_get_plane.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 15:09:42 by sbednar           #+#    #+#             */
/*   Updated: 2019/12/01 15:09:42 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_jtoc.h"

int			rt_jtoc_get_plane(t_object *obj, t_jnode *n)
{
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "distance"))
		|| tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("DISTANCE ERROR", -1));
	obj->params.plane.distance = jtoc_get_float(tmp);
	if (obj->params.plane.distance >= 1000)
		return (rt_jtoc_sdl_log_error("DISTANCE ERROR", -1));
	return (FUNCTION_SUCCESS);
}

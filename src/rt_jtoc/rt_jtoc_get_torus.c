/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_jtoc_get_torus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 15:08:51 by sbednar           #+#    #+#             */
/*   Updated: 2019/12/01 15:08:51 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_jtoc.h"

int	rt_jtoc_get_torus(t_object *obj, t_jnode *n)
{
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "radius")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("RADIUS ERROR", -1));
	obj->params.torus.radius = jtoc_get_float(tmp);
	if (obj->params.torus.radius <= 0 || obj->params.torus.radius >= 1000)
		return (rt_jtoc_sdl_log_error("RADIUS ERROR", -1));
	if (!(tmp = jtoc_node_get_by_path(n, "inner_radius"))
		|| tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("INNER_RADIUS ERROR", -1));
	obj->params.torus.inner_radius = jtoc_get_float(tmp);
	if (obj->params.torus.inner_radius <= 0
		|| obj->params.torus.inner_radius >= 1000)
		return (rt_jtoc_sdl_log_error("INNER RADIUS ERROR", -1));
	return (FUNCTION_SUCCESS);
}

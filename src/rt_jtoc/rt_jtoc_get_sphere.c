/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_jtoc_get_sphere.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 15:06:25 by sbednar           #+#    #+#             */
/*   Updated: 2019/12/01 15:07:15 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_jtoc.h"

int	rt_jtoc_get_sphere(t_object *obj, t_jnode *n)
{
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "radius")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("RADIUS ERROR", -1));
	obj->params.sphere.radius = jtoc_get_float(tmp);
	if (obj->params.sphere.radius <= 0 || obj->params.sphere.radius >= 1000)
		return (rt_jtoc_sdl_log_error("RADIUS ERROR", -1));
	return (FUNCTION_SUCCESS);
}

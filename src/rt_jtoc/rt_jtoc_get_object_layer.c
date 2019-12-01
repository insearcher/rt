/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_jtoc_get_object_layer.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 15:24:34 by sbednar           #+#    #+#             */
/*   Updated: 2019/12/01 15:25:40 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_jtoc.h"
#include "rt_raycast.h"

int	rt_jtoc_get_object_layer(t_object *obj, t_jnode *n)
{
	t_jnode	*tmp;
	char	*str;

	if (!(tmp = jtoc_node_get_by_path(n, "layer")) || tmp->type != string)
		return (rt_jtoc_sdl_log_error("LAYER ERROR OR LAYER IS MISSING", -1));
	str = jtoc_get_string(tmp);
	obj->layer = 0;
	obj->layer |= ft_strcmp(str, "default_layer") ? DEFAULT_LAYER : obj->layer;
	obj->layer |= ft_strcmp(str, "ignore_raycast_layer") ? IGNORE_RAYCAST_LAYER
		: obj->layer;
	if (obj->layer == 0)
		obj->layer = DEFAULT_LAYER;
	return (FUNCTION_SUCCESS);
}

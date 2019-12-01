/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_jtoc_utilits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:15:06 by sbednar           #+#    #+#             */
/*   Updated: 2019/09/26 14:15:43 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				rt_jtoc_get_float4(cl_float4 *vec, t_jnode *n)
{
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "x")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("X ERROR", -1));
	vec->x = jtoc_get_float(tmp);
	if (!(tmp = jtoc_node_get_by_path(n, "y")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("Y ERROR", -1));
	vec->y = jtoc_get_float(tmp);
	if (!(tmp = jtoc_node_get_by_path(n, "z")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("Z ERROR", -1));
	vec->z = jtoc_get_float(tmp);
	if (!(tmp = jtoc_node_get_by_path(n, "w")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("W ERROR", -1));
	vec->w = jtoc_get_float(tmp);
	return (FUNCTION_SUCCESS);
}

int				rt_jtoc_ispos_float2(cl_float2 *vec)
{
	return (vec->x >= 0 && vec->y >= 0
		? FUNCTION_SUCCESS
		: FUNCTION_FAILURE);
}

int				rt_jtoc_ispos_float3(cl_float3 *vec)
{
	return (vec->x >= 0 && vec->y >= 0 && vec->z >= 0
		? FUNCTION_SUCCESS
		: FUNCTION_FAILURE);
}

int				rt_jtoc_is01_float3(cl_float3 *vec)
{
	return (vec->x >= 0 && vec->x <= 1
		&& vec->y >= 0 && vec->y <= 1
		&& vec->z >= 0 && vec->z <= 1
			? FUNCTION_SUCCESS
			: FUNCTION_FAILURE);
}

int				rt_jtoc_ispos_float4(cl_float4 *vec)
{
	return (vec->x >= 0 && vec->y >= 0 && vec->z >= 0 && vec->w >= 0
		? FUNCTION_SUCCESS
		: FUNCTION_FAILURE);
}

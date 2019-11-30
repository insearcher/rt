/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_sdf2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 05:13:21 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/03 20:16:18 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_raycast.h"

float		f3len(cl_float3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

cl_float3	f3cross(cl_float3 v1, cl_float3 v2)
{
	return ((cl_float3){{v1.z * v2.y
		- v1.y * v2.z, v1.x * v2.z - v1.z * v2.x, v1.x * v2.y - v1.y * v2.x}});
}

cl_float2	f2norm(cl_float2 v)
{
	float	n;

	n = f2len(v);
	return ((cl_float2){{v.x / n, v.y / n}});
}

cl_float3	f3norm(cl_float3 v)
{
	float	len;

	len = f3len(v);
	if (len > RM_FLT_EPSILON)
		v.v4 /= f3len(v);
	return (v);
}

float		sdf_sphere(cl_float3 pos, float radius)
{
	return (f3len(pos) - radius);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_sdf3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 05:13:21 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/03 20:16:18 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_raycast.h"

float	sdf_box(cl_float3 pos, cl_float3 bounds)
{
	cl_float3	d;

	d = f3abs(pos);
	d.v4 -= bounds.v4;
	return (f3len(f3max(d, (cl_float3){{0, 0, 0}})) +
		fmin(fmax(d.x, fmax(d.y, d.z)), 0));
}

float	sdf_round_box(cl_float3 pos, cl_float3 bounds, float r)
{
	cl_float3	d;

	d = f3abs(pos);
	d.v4 -= bounds.v4;
	return (f3len(f3max(d, (cl_float3){{0, 0, 0}})) -
		r + fmin(fmax(d.x, fmax(d.y, d.z)), 0));
}

float	sdf_torus(cl_float3 pos, cl_float radius, cl_float inner_radius)
{
	cl_float2	q;

	q = (cl_float2){{f2len((cl_float2){{pos.x, pos.z}}) -
		radius, pos.y}};
	return (f2len(q) - inner_radius);
}

float	sdf_capped_torus(cl_float3 pos, cl_float2 sc, float ra, float rb)
{
	float	k;

	pos.x = fabs(pos.x);
	k = (sc.y * pos.x > sc.x * pos.y)
		? f2dot((cl_float2){{pos.x, pos.y}}, sc)
		: f2len((cl_float2){{pos.x, pos.y}});
	return (sqrt(f3dot(pos, pos) + ra * ra - 2.0f * ra * k) - rb);
}

float	sdf_link(cl_float3 pos, float le, float r1, float r2)
{
	cl_float3	q;

	q = (cl_float3){{pos.x, fmax(fabs(pos.y) - le, 0.0f), pos.z}};
	return (f2len((cl_float2){
		{f2len((cl_float2){{q.x, q.y}}) - r1, q.z}}) - r2);
}

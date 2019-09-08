/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_sdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 05:13:21 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/03 20:16:18 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_raycast.h"

static cl_float3	f3abs(cl_float3 v)
{
	return (cl_float3){{fabs(v.x), fabs(v.y), fabs(v.z)}};
}

static cl_float3	f3max(cl_float3 v1, cl_float3 v2)
{
	return (cl_float3){{fmax(v1.x, v2.x), fmax(v1.y, v2.y), fmax(v1.z, v2.z)}};
}

//static cl_float3	f3min(cl_float3 v1, cl_float3 v2)
//{
//	return (cl_float3){{fmin(v1.x, v2.x), fmin(v1.y, v2.y), fmin(v1.z, v2.z)}};
//}

static float		f2dot(cl_float2 v1, cl_float2 v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

float				f3dot(cl_float3 v1, cl_float3 v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

static float		f2len(cl_float2 v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

float				f3len(cl_float3 v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

cl_float3			f3cross(cl_float3 v1, cl_float3 v2)
{
	return (cl_float3){{v1.z * v2.y - v1.y * v2.z, v1.x * v2.z - v1.z * v2.x, v1.x * v2.y - v1.y * v2.x}};
}

static cl_float2	f2norm(cl_float2 v)
{
	float n = f2len(v);
	return (cl_float2){{v.x / n, v.y / n}};
}

cl_float3			f3norm(cl_float3 v)
{
	float	len;

	len = f3len(v);
	if (len > RM_FLT_EPSILON)
		v.v4 /= f3len(v);
	return v;
}

float	sdf_sphere(cl_float3 pos, float radius)
{
	return f3len(pos) - radius;
}

float	sdf_box(cl_float3 pos, cl_float3 bounds)
{
	cl_float3 d = f3abs(pos);
	d.v4 -= bounds.v4;
	return f3len(f3max(d, (cl_float3){{0, 0, 0}})) + fmin(fmax(d.x, fmax(d.y, d.z)), 0);
}

float	sdf_round_box(cl_float3 pos, cl_float3 bounds, float r)
{
	cl_float3 d = f3abs(pos);
	d.v4 -= bounds.v4;
	return f3len(f3max(d, (cl_float3){{0, 0, 0}})) - r + fmin(fmax(d.x, fmax(d.y, d.z)), 0);
}

float	sdf_torus(cl_float3 pos, cl_float2 t)
{
	cl_float2 q = (cl_float2){{f2len((cl_float2){{pos.x, pos.z}}) - t.x, pos.y}};
	return f2len(q) - t.y;
}

float	sdf_capped_torus(cl_float3 pos, cl_float2 sc, float ra, float rb)
{
	pos.x = fabs(pos.x);
	float k = (sc.y * pos.x > sc.x * pos.y) ? f2dot((cl_float2){{pos.x, pos.y}}, sc) : f2len((cl_float2){{pos.x, pos.y}});
	return sqrt(f3dot(pos, pos) + ra * ra - 2.0f * ra * k) - rb;
}

float	sdf_link(cl_float3 pos, float le, float r1, float r2)
{
	cl_float3 q = (cl_float3){{pos.x, fmax(fabs(pos.y) - le, 0.0f), pos.z}};
	return f2len((cl_float2){{f2len((cl_float2){{q.x, q.y}}) - r1, q.z}}) - r2;
}

float	sdf_cylinder(cl_float3 pos, cl_float3 c)
{
	return f2len((cl_float2){{pos.x - c.x, pos.y - c.y}}) - c.z;
}

float	sdf_cone(cl_float3 pos, cl_float2 c)
{
	float q = f2len((cl_float2){{pos.x, pos.y}});
	return f2dot(f2norm(c), (cl_float2){{q, pos.z}});
}

float	sdf_plane(cl_float3 pos, cl_float3 n, float d)
{
	return f3dot(pos, n) + d;
}
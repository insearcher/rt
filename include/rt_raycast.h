/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_raycast.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 17:50:06 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/23 17:50:07 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_RAYCAST_H
# define RT_RAYCAST_H

# include "rt.h"
# include "rt_object.h"

# include "rt_raycast_hit.h"

# define DEFAULT_LAYER			(1 << 0)
# define IGNORE_RAYCAST_LAYER	(1 << 1)

cl_float3						f3cross(cl_float3 v1, cl_float3 v2);
float							f3len(cl_float3 v);
float							f3dot(cl_float3 v1, cl_float3 v2);
cl_float3						f3norm(cl_float3 v);

float							sdf_sphere(cl_float3 pos, float radius);
float							sdf_box(cl_float3 pos, cl_float3 bounds);
float							sdf_round_box(cl_float3 pos, cl_float3 bounds,
		float r);
float							sdf_capped_torus(cl_float3 pos, cl_float2 sc,
		float ra, float rb);
float							sdf_link(cl_float3 pos, float le, float r1,
		float r2);
float							sdf_cylinder(cl_float3 pos, cl_float3 c);
float							sdf_cone(cl_float3 pos, cl_float2 c);
float							sdf_plane(cl_float3 pos, cl_float3 n, float d);
float							sdf_torus(cl_float3 pos, cl_float radius,
		cl_float inner_radius);

cl_float2						f2norm(cl_float2 v);
cl_float3						f3abs(cl_float3 v);
cl_float3						f3max(cl_float3 v1, cl_float3 v2);
float							f2dot(cl_float2 v1, cl_float2 v2);
float							f3dot(cl_float3 v1, cl_float3 v2);
float							f2len(cl_float2 v);

int								rt_raycast(t_ui_main *ui, void *a);

#endif

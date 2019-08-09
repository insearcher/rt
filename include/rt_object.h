/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 05:13:21 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/03 20:16:18 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_OBJECT_H
# define RT_OBJECT_H

# ifndef OPENCL___
#  include <OpenCL/opencl.h>
# endif

# include "transform.h"

typedef struct			s_sphere
{
# ifndef OPENCL___
	cl_float			radius;
# else
	float				radius;
# endif
}						t_sphere;

typedef struct			s_box
{
# ifndef OPENCL___
	cl_float3			bounds;
# else
	float3				bounds;
# endif
}						t_box;

typedef struct			s_round_box
{
# ifndef OPENCL___
	cl_float4			bounds;
# else
	float4				bounds;
# endif
}						t_round_box;

typedef struct			s_torus
{
# ifndef OPENCL___
	cl_float2			params;
# else
	float2				params;
# endif
}						t_torus;

typedef struct			s_cylinder
{
# ifndef OPENCL___
	cl_float3			params;
# else
	float3				params;
# endif
}						t_cylinder;

typedef struct			s_plane
{
# ifndef OPENCL___
	cl_float			distance;
# else
	float				distance;
# endif
}						t_plane;

union					u_oparams
{
	t_sphere			sphere;
	t_box				box;
	t_round_box			round_box;
	t_torus				torus;
	t_cylinder			cylinder;
	t_plane				plane;
};

enum					e_object_type
{
	sphere,
	box,
	round_box,
	torus,
	cylinder,
	plane
};

typedef struct			s_omaterial
{
# ifndef OPENCL___
	cl_float4			color;
# else
	float4				color;
# endif
}						t_omaterial;

typedef struct			s_object
{
	t_transform			transform;
	union u_oparams		params;
	enum e_object_type	type;
	t_omaterial			material;
	int					layer;

# ifndef OPENCL___
	t_rb				rb;
# else
	char				trash[112];
# endif
}						t_object;

#endif

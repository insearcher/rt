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
# ifdef APPLE___
# include <OpenCL/opencl.h>
# else
# include <opencl.h>
# endif
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
	cl_float3			bounds;
	cl_float			r;
# else
	float3				bounds;
	float				r;
# endif
}						t_round_box;

typedef struct			s_torus
{
# ifndef OPENCL___
	cl_float	radius;
	cl_float	inner_radius;
# else
	float	radius;
	float	inner_radius;
# endif
}						t_torus;

typedef struct			s_capped_torus
{
# ifndef OPENCL___
	cl_float2			sc;
	cl_float			ra;
	cl_float			rb;
# else
	float2				sc;
	float				ra;
	float				rb;
# endif
}						t_capped_torus;

typedef struct			s_link
{
# ifndef OPENCL___
	cl_float			le;
	cl_float			r1;
	cl_float			r2;
# else
	float				le;
	float				r1;
	float				r2;
# endif
}						t_link;

typedef struct			s_cylinder
{
# ifndef OPENCL___
	cl_float3			params;
# else
	float3				params;
# endif
}						t_cylinder;

typedef struct			s_cone
{
# ifndef OPENCL___
	cl_float2			c;
# else
	float2				c;
# endif
}						t_cone;

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
	t_capped_torus		capped_torus;
	t_link				link;
	t_cylinder			cylinder;
	t_cone				cone;
	t_plane				plane;
};

enum					e_object_type
{
	o_sphere = 1,
	o_box,
	o_round_box,
	o_torus,
	o_capped_torus,
	o_link,
	o_cylinder,
	o_cone,
	o_plane
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
}						t_object;

#endif

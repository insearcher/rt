/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_light.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 05:13:21 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/03 20:16:18 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_LIGHT_H
# define RT_LIGHT_H

# ifndef OPENCL___
#  ifdef APPLE___
#   include <OpenCL/opencl.h>
#  else
#   include <OpenCL/opencl.h>
#  endif
# endif

# include "transform.h"

typedef struct			s_directional
{
# ifndef OPENCL___

	cl_float3			color;
# else

	float3				color;
# endif

}						t_directional;

typedef struct			s_point
{
# ifndef OPENCL___

	cl_float3			color;
	cl_float			distance;
# else

	float3				color;
	float				distance;
# endif

}						t_point;

union					u_lparams
{
	t_directional		directional;
	t_point				point;
};

enum					e_light_type
{
	directional,
	point
};

typedef struct			s_light
{
	t_transform			transform;
	union u_lparams		params;
	enum e_light_type	type;
}						t_light;

#endif

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
#  include <OpenCL/opencl.h>
# endif

# include "transform.h"

typedef struct			s_directional
{
# ifndef OPENCL___
	cl_float3			intensity;
# else
	float3				intensity;
# endif
}						t_directional;

union					u_lparams
{
	t_directional		directional;
};

enum					e_light_type
{
	directional
};

typedef struct			s_light
{
	t_transform			transform;
	union u_lparams		params;
	enum e_light_type	type;
}						t_light;

#endif

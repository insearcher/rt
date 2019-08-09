/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_raycast_hit.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 05:13:21 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/03 20:16:18 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_RAYCAST_HIT_H
# define RT_RAYCAST_HIT_H

# include "rt_object.h"

typedef struct			s_raycast_hit
{
# ifndef OPENCL___
	t_object			*hit;
	cl_float3			normal;
	cl_float3			point;
	cl_float			distance;
# else
	__global t_object	*hit;
	float3				normal;
	float3				point;
	float				distance;
# endif
}						t_raycast_hit;

#endif

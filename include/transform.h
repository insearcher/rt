/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 05:13:21 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/03 20:16:18 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORM_H
# define TRANSFORM_H

typedef struct		s_transform
{
# ifndef OPENCL___
	cl_uint			id;
	cl_float3		pos;
	cl_float3		right;
	cl_float3		up;
	cl_float3		forward;
# else
	uint			id;
	float3			pos;
	float3			right;
	float3			up;
	float3			forward;
# endif
}					t_transform;

#endif

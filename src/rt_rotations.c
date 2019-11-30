/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_rotations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 05:13:21 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/03 20:16:18 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_rotations.h"

void	fill_rotation_matrix(float *m, cl_float3 v, float a)
{
	float	rads;
	float	c;
	float	s;

	rads = a / 180 * 3.1416;
	c = cosf(rads);
	s = sinf(rads);
	m[0] = c + v.x * v.x * (1 - c);
	m[1] = v.x * v.y * (1 - c) - v.z * s;
	m[2] = v.x * v.z * (1 - c) + v.y * s;
	m[3] = v.x * v.y * (1 - c) + v.z * s;
	m[4] = c + v.y * v.y * (1 - c);
	m[5] = v.y * v.z * (1 - c) - v.x * s;
	m[6] = v.x * v.z * (1 - c) - v.y * s;
	m[7] = v.y * v.z * (1 - c) + v.x * s;
	m[8] = c + v.z * v.z * (1 - c);
}

void	mult(float *m, cl_float3 *v)
{
	cl_float3	temp;

	temp = *v;
	temp.x = m[0] * v->x + m[1] * v->y + m[2] * v->z;
	temp.y = m[3] * v->x + m[4] * v->y + m[5] * v->z;
	temp.z = m[6] * v->x + m[7] * v->y + m[8] * v->z;
	*v = temp;
}

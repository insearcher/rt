/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_vec2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 20:25:31 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/03 20:26:11 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_vec.h"
#include <math.h>

t_vector3d	mv_get_vector3d(float x, float y, float z)
{
	t_vector3d	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

float		mv_length(const t_vector3d a)
{
	float	length;

	length = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	return (length);
}

t_vector3d	mv_normalize(const t_vector3d a)
{
	t_vector3d	vec;
	float		len;

	len = mv_length(a);
	if (len == 0)
		return (a);
	vec = mv_mult_num(a, 1 / len);
	return (vec);
}

t_vector3d	mv_inverse(const t_vector3d a)
{
	t_vector3d	vec;

	vec.x = -a.x;
	vec.y = -a.y;
	vec.z = -a.z;
	return (vec);
}

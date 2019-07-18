/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_vec1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 20:27:04 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/03 20:27:06 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_vec.h"
#include <math.h>

t_vector3d	mv_minus(const t_vector3d a, const t_vector3d b)
{
	t_vector3d	c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return (c);
}

t_vector3d	mv_plus(const t_vector3d a, const t_vector3d b)
{
	t_vector3d	c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}

t_vector3d	mv_mult_num(const t_vector3d a, float num)
{
	t_vector3d	c;

	c.x = a.x * num;
	c.y = a.y * num;
	c.z = a.z * num;
	return (c);
}

t_vector3d	mv_dev_num(const t_vector3d a, float num)
{
	t_vector3d	c;

	c.x = a.x / num;
	c.y = a.y / num;
	c.z = a.z / num;
	return (c);
}

float		mv_scalar_mult(const t_vector3d a, const t_vector3d b)
{
	float	scalar_mult;

	scalar_mult = a.x * b.x + a.y * b.y + a.z * b.z;
	return (scalar_mult);
}

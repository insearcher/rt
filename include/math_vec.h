/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_vec.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 19:47:50 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/03 19:47:52 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_VEC_H
# define MATH_VEC_H

typedef struct	s_vector3d
{
	float		x;
	float		y;
	float		z;
}				t_vector3d;

float			mv_scalar_mult(const t_vector3d a, const t_vector3d b);
t_vector3d		mv_get_vector3d(float x, float y, float z);
t_vector3d		mv_minus(const t_vector3d a, const t_vector3d b);
t_vector3d		mv_plus(const t_vector3d a, const t_vector3d b);
t_vector3d		mv_mult_num(const t_vector3d a, float num);
t_vector3d		mv_dev_num(const t_vector3d a, float num);
float			mv_length(const t_vector3d a);
t_vector3d		mv_normalize(const t_vector3d a);
t_vector3d		mv_mult(t_vector3d a, t_vector3d b);
t_vector3d		mv_inverse(const t_vector3d a);

#endif

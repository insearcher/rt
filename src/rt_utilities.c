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

#include "rt_utilities.h"

void	rotate_transform_around_axis(t_transform *t, cl_float3 a, float d)
{
	float	rot_matrix[9];

	fill_rotation_matrix(&rot_matrix[0], a, d);
	mult(&rot_matrix[0], &t->right);
	mult(&rot_matrix[0], &t->up);
	mult(&rot_matrix[0], &t->forward);
}

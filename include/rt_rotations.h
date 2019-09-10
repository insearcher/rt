/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_rotations.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 05:13:21 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/03 20:16:18 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_ROTATIONS_H
# define RT_ROTATIONS_H

# ifndef OPENCL___
#  include <opencl.h>
#  include "math.h"
# endif

void	fill_rotation_matrix(float *m, cl_float3 v, float a);
void	mult(float *m, cl_float3 *v);

#endif

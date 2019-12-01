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

#ifndef RT_UTILITIES_H
# define RT_UTILITIES_H

# ifndef OPENCL___
#  ifdef APPLE___
#   include <OpenCL/opencl.h>
#  else
#   include <opencl.h>
#  endif
#  include "math.h"
#  include "rt_rotations.h"
#  include "transform.h"
# endif

void	rotate_transform_around_axis(t_transform *t, cl_float3 a, float d);
int		rt_jtoc_sdl_log_error(const char *p, const int id);

#endif

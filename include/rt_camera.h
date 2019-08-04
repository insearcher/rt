/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_camera.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 05:13:21 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/03 20:16:18 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_CAMERA_H
# define RT_CAMERA_H

# ifndef OPENCL___
#  include "libui.h"
#  include "rt_physics_system.h"
#  include <OpenCL/opencl.h>
# endif

# include "transform.h"

typedef	struct			s_clipping
{
# ifndef OPENCL___
	cl_float			near;
	cl_float			far;
#else
	float				near;
	float				far;
#endif
}						t_clipping;

typedef struct			s_camera
{
	t_transform			transform;
	t_clipping			clipping_planes;

# ifndef OPENCL___
	/// Temp
	cl_float			fov;
	cl_int				mx;
	cl_int				my;
	cl_int				quality;
	t_rb				rb;
# else
	/// Temp
	float				fov;
	int					mx;
	int					my;
	int					quality;
	char				trash[112];
# endif

}						t_camera;

#endif

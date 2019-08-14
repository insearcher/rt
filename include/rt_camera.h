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

# define CAMERA_ID		1

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
	cl_int2				screen;
	cl_float			fov;
	cl_int				mx;
	cl_int				my;
	cl_int				quality;
# else
	int2				screen;
	float				fov;
	int					mx;
	int					my;
	int					quality;
# endif

}						t_camera;

#endif

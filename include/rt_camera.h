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

# include "libui.h"
# include "rt_physics.h"
# include <OpenCL/opencl.h>

typedef	struct			s_clipping
{
# ifndef OPENCL___
	cl_float			near;
	cl_float			far;
#elif
	float				near;
	float				far;
#endif
}						t_clipping;

typedef struct			s_camera
{
	t_transform			transform;
	t_rb				rb;
	t_clipping			clipping_planes;

# ifndef OPENCL___

	/// Temp
	cl_float				fov;
	cl_int					mx;
	cl_int					my;

# else

	/// Temp
	float				fov;
	int					mx;
	int					my;

# endif

}						t_camera;

void	move_camera(t_ui_main *m);
void	rotate_camera(t_ui_main *m);

#endif

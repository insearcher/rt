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

typedef struct			s_camera
{
	t_transform			transform;
	t_rb				rb;

# ifndef OPENCL___

	/// Rendering
	cl_float 				aspect_ratio;
	cl_float				min_distance;
	cl_float				max_distance;
	/// Temp
	cl_int					mx;
	cl_int					my;

# else

	/// Rendering
	float 				aspect_ratio;
	float				min_distance;
	float				max_distance;
	/// Temp
	int					mx;
	int					my;

# endif

}						t_camera;

void	move_camera(t_ui_main *m);
void	rotate_camera(t_ui_main *m);

#endif

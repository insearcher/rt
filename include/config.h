/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbosmer <sbosmer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 02:46:07 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/18 20:35:20 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# define CL_SILENCE_DEPRECATION

# include <OpenCL/opencl.h>
# include <math.h>
# include "libft.h"
# include "rt.h"
# include "rt_camera.h"
# include <stdio.h>
# include "libui.h"
# include "libcl.h"

typedef struct			s_config
{
	int					objects_num;
	t_object3d			*objects;
	t_camera			camera;
	t_cl				*cl;
}						t_conf;

void					setup_camera(t_camera *camera);
void					setup_scene(t_conf *conf);
int						ray_marching_render(t_ui_main *m, void *a);
#endif

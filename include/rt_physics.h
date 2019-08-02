/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_physics.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 05:13:21 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/03 20:16:18 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_PHYSICS_H
# define RT_PHYSICS_H

# define CL_SILENCE_DEPRECATION

# ifndef OPENCL___
#  include <OpenCL/opencl.h>
#  include <SDL.h>
#  include "libft.h"
# endif

typedef	int			(t_phys_func)(void *);

typedef	struct		s_local
{
	cl_float3		right;
	cl_float3		up;
	cl_float3		forward;
}					t_local;

typedef struct		s_transform
{
	cl_float3		pos;
	t_local			local;
}					t_transform;

typedef struct		s_move_params
{
	cl_float3		vel;
	cl_float3		raw_vel;
	cl_float		acc;
	cl_float		speed;
	cl_float		speed_mult;
}					t_move_params;

typedef struct		s_rb
{
	t_move_params	move;
	t_move_params	rot;
	t_transform		*transform;
}					t_rb;

typedef struct		s_physics_system
{
	SDL_Thread		*thread;
	size_t			rbs_count;
	t_rb			**rbs;
	size_t			delay;
}					t_physics_system;

int					ps_start(t_physics_system *p);
t_physics_system	*ps_init(t_phys_func *f);

int					ps_func(void *psv);

#endif

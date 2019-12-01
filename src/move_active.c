/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_active.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 18:30:53 by sbednar           #+#    #+#             */
/*   Updated: 2019/12/01 18:34:29 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_input_system.h"

void	move_active(t_input_system *s)
{
	t_camera	*cam;
	float		d;

	s->active->move.raw_vel = (cl_float3){{
		get_axis(s->state, SDL_SCANCODE_A, SDL_SCANCODE_D),
		get_axis(s->state, SDL_SCANCODE_Q, SDL_SCANCODE_E),
		get_axis(s->state, SDL_SCANCODE_S, SDL_SCANCODE_W)
	}};
	if (s->state[SDL_SCANCODE_LSHIFT])
		s->active->move.raw_vel.v4 *= s->active->move.speed_mult;
	if (s->active->transform->id == CAMERA_ID)
	{
		cam = (t_camera *)s->active->transform;
		d = get_axis(s->state, SDL_SCANCODE_T, SDL_SCANCODE_Y);
		if (d != 0)
			cam->fov += d * 0.1f;
	}
	if (s->state[SDL_SCANCODE_M])
		change_selected(s, NULL);
}

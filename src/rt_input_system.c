/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_physics_system.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 03:01:47 by sbecker           #+#    #+#             */
/*   Updated: 2019/12/01 18:35:11 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_input_system.h"

float			get_axis(const Uint8 *state,
		SDL_Scancode low, SDL_Scancode high)
{
	if (!(state[low] ^ state[high]))
		return (0);
	if (state[high])
		return (1);
	if (state[low])
		return (-1);
	return (0);
}

void			process_selected(t_input_system *s)
{
	cl_float3	raw_dir;

	raw_dir = (cl_float3){{
		get_axis(s->state, SDL_SCANCODE_J, SDL_SCANCODE_L),
		get_axis(s->state, SDL_SCANCODE_O, SDL_SCANCODE_U),
		get_axis(s->state, SDL_SCANCODE_I, SDL_SCANCODE_K)
	}};
	s->selected->pos.v4 += raw_dir.v4 * 0.01f;
}

void			change_selected(t_input_system *s, t_object *o)
{
	t_object	*obj;

	obj = (t_object *)s->selected;
	if (obj)
		obj->material.color = (cl_float4){{0, 1, 1, 1}};
	s->selected = &o->transform;
	obj = (t_object *)s->selected;
	if (obj)
		obj->material.color = (cl_float4){{0, 0, 1, 1}};
}

int				is_func(void *isv)
{
	t_input_system	*is;

	is = (t_input_system *)isv;
	is->system.now = SDL_GetPerformanceCounter();
	is->system.last = 0;
	while (is)
	{
		is->system.delta_time = (float)(is->system.now - is->system.last) /
				SDL_GetPerformanceFrequency();
		move_active(is);
		rotate_active(is);
		if (is->selected)
			process_selected(is);
		is->system.last = is->system.now;
		is->system.now = SDL_GetPerformanceCounter();
	}
	return (0);
}

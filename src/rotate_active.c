/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_active.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 18:32:31 by sbednar           #+#    #+#             */
/*   Updated: 2019/12/01 18:32:31 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_input_system.h"

void	rotate_active(t_input_system *s)
{
	t_rb	*active;

	active = s->active;
	active->rot.raw_vel = (cl_float3){{
		get_axis(s->state, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN),
		get_axis(s->state, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT),
		0
	}};
}

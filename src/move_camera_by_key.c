/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_camera_by_key.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 05:13:21 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/03 20:16:18 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_camera.h"

void	move_camera(t_ui_main *m)
{
	t_camera	*cam;

	cam = &((t_conf *)m->data)->camera;

	if (m->state[SDL_SCANCODE_A])
		cam->velocity.x = -1;
	else if (m->state[SDL_SCANCODE_D])
		cam->velocity.x = 1;
	else if (!m->state[SDL_SCANCODE_A] && !m->state[SDL_SCANCODE_D])
		cam->velocity.x = 0;

	if (m->state[SDL_SCANCODE_Q])
		cam->velocity.y = -1;
	else if (m->state[SDL_SCANCODE_E])
		cam->velocity.y = 1;
	else if (!m->state[SDL_SCANCODE_Q] && !m->state[SDL_SCANCODE_E])
		cam->velocity.y = 0;

	if (m->state[SDL_SCANCODE_S])
		cam->velocity.z = -1;
	else if (m->state[SDL_SCANCODE_W])
		cam->velocity.z = 1;
	else if (!m->state[SDL_SCANCODE_S] && !m->state[SDL_SCANCODE_W])
		cam->velocity.z = 0;

	float mult = (m->state[225] ? 2 : 1);
	if (cam->velocity.x != 0)
		cam->pos.x += cam->velocity.x * cam->speed * mult;
	if (cam->velocity.y != 0)
		cam->pos.y += cam->velocity.y * cam->speed * mult;
	if (cam->velocity.z != 0)
		cam->pos.z += cam->velocity.z * cam->speed * mult;
}
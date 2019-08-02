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

#include <config.h>
#include "rt_camera.h"

static void	get_x_rot_matrix(float *m, cl_float3 *v, float a)
{
	float rads = a / 180 * M_PI;
	float c = cosf(rads);
	float s = sinf(rads);

	m[0] = c + v->x * v->x * (1 - c);
	m[1] = v->x * v->y * (1 - c) - v->z * s;
	m[2] = v->x * v->z * (1 - c) + v->y * s;
	m[3] = v->x * v->y * (1 - c) + v->z * s;
	m[4] = c + v->y * v->y * (1 - c);
	m[5] = v->y * v->z * (1 - c) - v->x * s;
	m[6] = v->x * v->z * (1 - c) - v->y * s;
	m[7] = v->y * v->z * (1 - c) + v->x * s;
	m[8] = c + v->z * v->z * (1 - c);
}

static void	get_y_rot_matrix(float *m, float a)
{
	float rads = a / 180 * M_PI;

	m[0] = cosf(rads);
	m[1] = 0;
	m[2] = sinf(rads);
	m[3] = 0;
	m[4] = 1;
	m[5] = 0;
	m[6] = -sinf(rads);
	m[7] = 0;
	m[8] = cosf(rads);
}

static void	mult_matrix_to_vec(float *m, cl_float3 *v)
{
	cl_float3 temp = *v;

	temp.x = m[0] * v->x + m[1] * v->y + m[2] * v->z;
	temp.y = m[3] * v->x + m[4] * v->y + m[5] * v->z;
	temp.z = m[6] * v->x + m[7] * v->y + m[8] * v->z;
	*v = temp;
}

void	rotate_camera(t_ui_main *m)
{
	t_camera	*cam;
	cl_float3	raw_rot_velocity;

	cam = &((t_conf *)m->data)->camera;

	/// Arrows mode
	if (m->state[SDL_SCANCODE_DOWN])
		raw_rot_velocity.x = 1;
	else if (m->state[SDL_SCANCODE_UP])
		raw_rot_velocity.x = -1;
	else if (!m->state[SDL_SCANCODE_DOWN] && !m->state[SDL_SCANCODE_UP])
		raw_rot_velocity.x = 0;

	if (m->state[SDL_SCANCODE_LEFT])
		raw_rot_velocity.y = -1;
	else if (m->state[SDL_SCANCODE_RIGHT])
		raw_rot_velocity.y = 1;
	else if (!m->state[SDL_SCANCODE_LEFT] && !m->state[SDL_SCANCODE_RIGHT])
		raw_rot_velocity.y = 0;
	/// End of arrows mode

//	/// Mouse mode
//	int x, y;
//	SDL_GetMouseState(&x, &y);
//	if (!raw_rot_velocity.y)
//		raw_rot_velocity.y = (x - cam->mx) / 1440.f * 300;
//	if (!raw_rot_velocity.x)
//		raw_rot_velocity.x = (y - cam->my) / 810.f * 300;
//	/// End of mouse mode

	cam->rb.rot.vel.x = ft_lerp(cam->rb.rot.vel.x, raw_rot_velocity.x,
			ft_fmin(1, cam->rb.rot.acc / fabs(cam->rb.rot.vel.x -
			raw_rot_velocity.x)));
	cam->rb.rot.vel.y = ft_lerp(cam->rb.rot.vel.y, raw_rot_velocity.y,
			ft_fmin(1, cam->rb.rot.acc / fabs(cam->rb.rot.vel.y -
			raw_rot_velocity.y)));

	float rot_matrix[9];
	get_x_rot_matrix(&rot_matrix[0], &cam->transform.local.right, cam->rb.rot.vel.x *
	cam->rb.rot.speed);
	mult_matrix_to_vec(&rot_matrix[0], &cam->transform.local.right);
	mult_matrix_to_vec(&rot_matrix[0], &cam->transform.local.up);
	mult_matrix_to_vec(&rot_matrix[0], &cam->transform.local.forward);
	get_y_rot_matrix(&rot_matrix[0], cam->rb.rot.vel.y * cam->rb.rot.speed);
	mult_matrix_to_vec(&rot_matrix[0], &cam->transform.local.right);
	mult_matrix_to_vec(&rot_matrix[0], &cam->transform.local.up);
	mult_matrix_to_vec(&rot_matrix[0], &cam->transform.local.forward);

//	cam->mx = x;
//	cam->my = y;
}

void	move_camera(t_ui_main *m)
{
	t_camera	*cam;
	cl_float3	raw_velocity;

	cam = &((t_conf *)m->data)->camera;

	if (m->state[SDL_SCANCODE_A])
		raw_velocity.x = -1;
	else if (m->state[SDL_SCANCODE_D])
		raw_velocity.x = 1;
	else if (!m->state[SDL_SCANCODE_A] && !m->state[SDL_SCANCODE_D])
		raw_velocity.x = 0;

	if (m->state[SDL_SCANCODE_Q])
		raw_velocity.y = -1;
	else if (m->state[SDL_SCANCODE_E])
		raw_velocity.y = 1;
	else if (!m->state[SDL_SCANCODE_Q] && !m->state[SDL_SCANCODE_E])
		raw_velocity.y = 0;

	if (m->state[SDL_SCANCODE_S])
		raw_velocity.z = -1;
	else if (m->state[SDL_SCANCODE_W])
		raw_velocity.z = 1;
	else if (!m->state[SDL_SCANCODE_S] && !m->state[SDL_SCANCODE_W])
		raw_velocity.z = 0;

	float mult = (m->state[225] ? 2 : 1);
	cam->rb.move.vel.x = ft_lerp(cam->rb.move.vel.x, raw_velocity.x * mult,
			ft_fmin(1, cam->rb.move.acc / fabs(cam->rb.move.vel.x - raw_velocity.x)));
	cam->rb.move.vel.y = ft_lerp(cam->rb.move.vel.y, raw_velocity.y * mult,
			ft_fmin(1, cam->rb.move.acc / fabs(cam->rb.move.vel.y - raw_velocity.y)));
	cam->rb.move.vel.z = ft_lerp(cam->rb.move.vel.z, raw_velocity.z * mult,
			ft_fmin(1, cam->rb.move.acc / fabs(cam->rb.move.vel.z - raw_velocity.z)));

	cam->transform.pos.v4 += cam->transform.local.right.v4 * cam->rb.move.vel.x * cam->rb.move.speed;
	cam->transform.pos.v4 += cam->transform.local.up.v4 * cam->rb.move.vel.y * cam->rb.move.speed;
	cam->transform.pos.v4 += cam->transform.local.forward.v4 * cam->rb.move.vel.z * cam->rb.move.speed;
}
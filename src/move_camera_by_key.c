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

static void	get_x_rot_matrix(float *m, t_vector3d *v, float a)
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

static void	mult_matrix_to_vec(float *m, t_vector3d *v)
{
	t_vector3d temp = *v;

	temp.x = m[0] * v->x + m[1] * v->y + m[2] * v->z;
	temp.y = m[3] * v->x + m[4] * v->y + m[5] * v->z;
	temp.z = m[6] * v->x + m[7] * v->y + m[8] * v->z;
	*v = temp;
}

void	rotate_camera(t_ui_main *m)
{
	t_camera	*cam;
	t_vector3d	raw_rot_velocity;

	cam = &((t_conf *)m->data)->camera;

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

	cam->rot_velocity.x = ft_lerp(cam->rot_velocity.x, raw_rot_velocity.x,
			ft_fmin(1, cam->rot_acc / fabs(cam->rot_velocity.x -
			raw_rot_velocity.x)));
	cam->rot_velocity.y = ft_lerp(cam->rot_velocity.y, raw_rot_velocity.y,
			ft_fmin(1, cam->rot_acc / fabs(cam->rot_velocity.y -
			raw_rot_velocity.y)));

	float rot_matrix[9];
	get_x_rot_matrix(&rot_matrix[0], &cam->local_x, cam->rot_velocity.x *
	cam->rot_speed);
	mult_matrix_to_vec(&rot_matrix[0], &cam->local_x);
	mult_matrix_to_vec(&rot_matrix[0], &cam->local_y);
	mult_matrix_to_vec(&rot_matrix[0], &cam->local_z);
	get_y_rot_matrix(&rot_matrix[0], cam->rot_velocity.y * cam->rot_speed);
	mult_matrix_to_vec(&rot_matrix[0], &cam->local_x);
	mult_matrix_to_vec(&rot_matrix[0], &cam->local_y);
	mult_matrix_to_vec(&rot_matrix[0], &cam->local_z);
}

void	move_camera(t_ui_main *m)
{
	t_camera	*cam;
	t_vector3d	raw_velocity;

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
	cam->velocity.x = ft_lerp(cam->velocity.x, raw_velocity.x * mult,
			ft_fmin(1, cam->pos_acc / fabs(cam->velocity.x - raw_velocity.x)));
	cam->velocity.y = ft_lerp(cam->velocity.y, raw_velocity.y * mult,
			ft_fmin(1, cam->pos_acc / fabs(cam->velocity.y - raw_velocity.y)));
	cam->velocity.z = ft_lerp(cam->velocity.z, raw_velocity.z * mult,
			ft_fmin(1, cam->pos_acc / fabs(cam->velocity.z - raw_velocity.z)));

	cam->pos = mv_plus(cam->pos, mv_mult_num(cam->local_x,
			cam->velocity.x * cam->speed));
	cam->pos = mv_plus(cam->pos, mv_mult_num(cam->local_y,
			cam->velocity.y * cam->speed));
	cam->pos = mv_plus(cam->pos, mv_mult_num(cam->local_z,
			cam->velocity.z * cam->speed));
}
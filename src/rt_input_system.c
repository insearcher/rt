/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_physics_system.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 03:01:47 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/03 19:48:39 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_input_system.h"

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

static float	get_axis(const Uint8 *state, SDL_Scancode low, SDL_Scancode high)
{
	if (!(state[low] ^ state[high]))
		return (0);
	if (state[high])
		return (1);
	if (state[low])
		return (-1);
	return (0);
}

void	rotate_active(t_input_system *s)
{
	t_rb		*active;

	active = s->active;

	/// Arrows mode

	active->rot.raw_vel = (cl_float3){{
		get_axis(s->state, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN),
		get_axis(s->state, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT),
		0
	}};
	/// End of arrows mode

//	/// Mouse mode
//	int x, y;
//	SDL_GetMouseState(&x, &y);
//	if (!raw_rot_velocity.y)
//		raw_rot_velocity.y = (x - cam->mx) / 1440.f * 300;
//	if (!raw_rot_velocity.x)
//		raw_rot_velocity.x = (y - cam->my) / 810.f * 300;
//	/// End of mouse mode

	active->rot.vel.x = ft_lerp(active->rot.vel.x, active->rot.raw_vel.x,
								ft_fmin(1, active->rot.acc / fabs(active->rot.vel.x -
																		 active->rot.raw_vel.x)));
	active->rot.vel.y = ft_lerp(active->rot.vel.y, active->rot.raw_vel.y,
								ft_fmin(1, active->rot.acc / fabs(active->rot.vel.y -
																		 active->rot.raw_vel.y)));

	float rot_matrix[9];
//	SDL_LockMutex(s->system.mutex);

	get_x_rot_matrix(&rot_matrix[0], &active->transform->local.right, active->rot.vel.x * active->rot.speed * s->system.delta_time);
	mult_matrix_to_vec(&rot_matrix[0], &active->transform->local.right);
	mult_matrix_to_vec(&rot_matrix[0], &active->transform->local.up);
	mult_matrix_to_vec(&rot_matrix[0], &active->transform->local.forward);

	get_y_rot_matrix(&rot_matrix[0], active->rot.vel.y * active->rot.speed * s->system.delta_time);
	mult_matrix_to_vec(&rot_matrix[0], &active->transform->local.right);
	mult_matrix_to_vec(&rot_matrix[0], &active->transform->local.up);
	mult_matrix_to_vec(&rot_matrix[0], &active->transform->local.forward);

//	SDL_UnlockMutex(s->system.mutex);

//	cam->mx = x;
//	cam->my = y;
}

void	move_active(t_input_system *s)
{
//	SDL_LockMutex(s->system.mutex);
	s->active->move.raw_vel = (cl_float3){{
		get_axis(s->state, SDL_SCANCODE_A, SDL_SCANCODE_D),
		get_axis(s->state, SDL_SCANCODE_Q, SDL_SCANCODE_E),
		get_axis(s->state, SDL_SCANCODE_S, SDL_SCANCODE_W)
	}};
	s->active->move.speed_mult = (s->state[225] ? 2 : 1);
//	SDL_UnlockMutex(s->system.mutex);
}

int					is_func(void *isv)
{
	t_input_system	*is;

	is = (t_input_system *)isv;
	is->system.now = SDL_GetPerformanceCounter();
	is->system.last = 0;
	while (is)
	{
		is->system.delta_time = (is->system.now - is->system.last) / (double)SDL_GetPerformanceFrequency();
		move_active(is);
		rotate_active(is);
		SDL_Delay(is->system.delay);
		is->system.last = is->system.now;
		is->system.now = SDL_GetPerformanceCounter();
	}
	return (0);
}
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

#include "rt_physics_system.h"

static int		ps_move(t_physics_system *ps, const int i)
{
	if (fabs(ps->rbs[i].move.vel.x - ps->rbs[i].move.raw_vel.x) > RM_FLT_EPSILON)
		ps->rbs[i].move.vel.x = ft_lerp(
				ps->rbs[i].move.vel.x,
				ps->rbs[i].move.raw_vel.x,
				ps->rbs[i].move.braking_coef);
	if (fabs(ps->rbs[i].move.vel.y - ps->rbs[i].move.raw_vel.y) > RM_FLT_EPSILON)
		ps->rbs[i].move.vel.y = ft_lerp(
				ps->rbs[i].move.vel.y,
				ps->rbs[i].move.raw_vel.y,
				ps->rbs[i].move.braking_coef);
	if (fabs(ps->rbs[i].move.vel.z - ps->rbs[i].move.raw_vel.z) > RM_FLT_EPSILON)
		ps->rbs[i].move.vel.z = ft_lerp(
				ps->rbs[i].move.vel.z,
				ps->rbs[i].move.raw_vel.z,
				ps->rbs[i].move.braking_coef);

	if (fabs(ps->rbs[i].move.vel.x) > RM_FLT_EPSILON)
		ps->rbs[i].transform->pos.v4 += ps->rbs[i].transform->right.v4 * ps->rbs[i].move.vel.x *
									ps->rbs[i].move.speed * ps->system.delta_time;
	if (fabs(ps->rbs[i].move.vel.y) > RM_FLT_EPSILON)
		ps->rbs[i].transform->pos.v4 += ps->rbs[i].transform->up.v4 * ps->rbs[i].move.vel.y *
									ps->rbs[i].move.speed * ps->system.delta_time;
	if (fabs(ps->rbs[i].move.vel.z) > RM_FLT_EPSILON)
		ps->rbs[i].transform->pos.v4 += ps->rbs[i].transform->forward.v4 * ps->rbs[i].move.vel.z *
										ps->rbs[i].move.speed * ps->system.delta_time;

	return (fabs(ps->rbs[i].move.vel.x) > RM_FLT_EPSILON ||
		fabs(ps->rbs[i].move.vel.y) > RM_FLT_EPSILON ||
		fabs(ps->rbs[i].move.vel.z) > RM_FLT_EPSILON);
}

static int		ps_rot(t_physics_system *ps, const int i)
{
	if (fabs(ps->rbs[i].rot.vel.x - ps->rbs[i].rot.raw_vel.x) > RM_FLT_EPSILON)
		ps->rbs[i].rot.vel.x = ft_lerp(
				ps->rbs[i].rot.vel.x, 
				ps->rbs[i].rot.raw_vel.x, 
				ps->rbs[i].rot.braking_coef);
	if (fabs(ps->rbs[i].rot.vel.y - ps->rbs[i].rot.raw_vel.y) > RM_FLT_EPSILON)
		ps->rbs[i].rot.vel.y = ft_lerp(
				ps->rbs[i].rot.vel.y,
				ps->rbs[i].rot.raw_vel.y, 
				ps->rbs[i].rot.braking_coef);

	float rot_matrix[9];

	if (fabs(ps->rbs[i].rot.vel.x) > RM_FLT_EPSILON)
	{
		fill_rotation_matrix(&rot_matrix[0], ps->rbs[i].transform->right, ps->rbs[i].rot.vel.x * ps->rbs[i].rot.speed * ps->system.delta_time);
		mult(&rot_matrix[0], &ps->rbs[i].transform->right);
		mult(&rot_matrix[0], &ps->rbs[i].transform->up);
		mult(&rot_matrix[0], &ps->rbs[i].transform->forward);
	}

	if (fabs(ps->rbs[i].rot.vel.y) > RM_FLT_EPSILON)
	{
		fill_rotation_matrix(&rot_matrix[0], (cl_float3){{0, 1, 0}}, ps->rbs[i].rot.vel.y * ps->rbs[i].rot.speed * ps->system.delta_time);
		mult(&rot_matrix[0], &ps->rbs[i].transform->right);
		mult(&rot_matrix[0], &ps->rbs[i].transform->up);
		mult(&rot_matrix[0], &ps->rbs[i].transform->forward);
	}

	return (fabs(ps->rbs[i].rot.vel.x) > RM_FLT_EPSILON ||
			fabs(ps->rbs[i].rot.vel.y) > RM_FLT_EPSILON ||
			fabs(ps->rbs[i].rot.vel.z) > RM_FLT_EPSILON);
}


int					ps_func(void *psv)
{
	t_physics_system	*ps;
	size_t				i;

	ps = (t_physics_system *)psv;
	ps->system.now = SDL_GetPerformanceCounter();
	ps->system.last = ps->system.now;
	while (ps->rbs)
	{
		ps->change_indicator = 0;
		i = -1;
		ps->system.delta_time = (double)(ps->system.now - ps->system.last) / SDL_GetPerformanceFrequency() / 1000;
		while (++i < ps->rbs_count)
		{
			ps->change_indicator |= ps_move(ps, i);
			ps->change_indicator |= ps_rot(ps, i);
		}
		SDL_Delay(ps->system.delay);
		ps->system.last = ps->system.now;
		ps->system.now = SDL_GetPerformanceCounter();
	}
	return (0);
}

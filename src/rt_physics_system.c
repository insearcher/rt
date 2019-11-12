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
	t_rb	*rbs;

	rbs = (t_rb *)ps->rbs.storage;
	if (fabs(rbs[i].move.vel.x - rbs[i].move.raw_vel.x) > RM_FLT_EPSILON)
		rbs[i].move.vel.x = ft_lerp(
				rbs[i].move.vel.x,
				rbs[i].move.raw_vel.x,
				rbs[i].move.acc);
	if (fabs(rbs[i].move.vel.y - rbs[i].move.raw_vel.y) > RM_FLT_EPSILON)
		rbs[i].move.vel.y = ft_lerp(
				rbs[i].move.vel.y,
				rbs[i].move.raw_vel.y,
				rbs[i].move.acc);
	if (fabs(rbs[i].move.vel.z - rbs[i].move.raw_vel.z) > RM_FLT_EPSILON)
		rbs[i].move.vel.z = ft_lerp(
				rbs[i].move.vel.z,
				rbs[i].move.raw_vel.z,
				rbs[i].move.acc);

	if (fabs(rbs[i].move.vel.x) > RM_FLT_EPSILON)
		rbs[i].transform->pos.v4 += rbs[i].transform->right.v4 * rbs[i].move.vel.x *
									rbs[i].move.speed * ps->system.delta_time;
	if (fabs(rbs[i].move.vel.y) > RM_FLT_EPSILON)
		rbs[i].transform->pos.v4 += rbs[i].transform->up.v4 * rbs[i].move.vel.y *
									rbs[i].move.speed * ps->system.delta_time;
	if (fabs(rbs[i].move.vel.z) > RM_FLT_EPSILON)
		rbs[i].transform->pos.v4 += rbs[i].transform->forward.v4 * rbs[i].move.vel.z *
										rbs[i].move.speed * ps->system.delta_time;

	return (fabs(rbs[i].move.vel.x) > RM_FLT_EPSILON ||
		fabs(rbs[i].move.vel.y) > RM_FLT_EPSILON ||
		fabs(rbs[i].move.vel.z) > RM_FLT_EPSILON);
}

static int		ps_rot(t_physics_system *ps, const int i)
{
	t_rb	*rbs;

	rbs = (t_rb *)ps->rbs.storage;
	if (fabs(rbs[i].rot.vel.x - rbs[i].rot.raw_vel.x) > RM_FLT_EPSILON)
		rbs[i].rot.vel.x = ft_lerp(
				rbs[i].rot.vel.x, 
				rbs[i].rot.raw_vel.x, 
				rbs[i].rot.acc);
	if (fabs(rbs[i].rot.vel.y - rbs[i].rot.raw_vel.y) > RM_FLT_EPSILON)
		rbs[i].rot.vel.y = ft_lerp(
				rbs[i].rot.vel.y,
				rbs[i].rot.raw_vel.y, 
				rbs[i].rot.acc);

//	float rot_matrix[9];

	if (fabs(rbs[i].rot.vel.x) > RM_FLT_EPSILON)
	{
		rotate_transform_around_axis(rbs[i].transform, rbs[i].transform->right, rbs[i].rot.vel.x * rbs[i].rot.speed * ps->system.delta_time);
//		fill_rotation_matrix(&rot_matrix[0], rbs[i].transform->right, rbs[i].rot.vel.x * rbs[i].rot.speed * ps->system.delta_time);
//		mult(&rot_matrix[0], &rbs[i].transform->right);
//		mult(&rot_matrix[0], &rbs[i].transform->up);
//		mult(&rot_matrix[0], &rbs[i].transform->forward);
	}

	if (fabs(rbs[i].rot.vel.y) > RM_FLT_EPSILON)
	{
		rotate_transform_around_axis(rbs[i].transform, (cl_float3){{0, 1, 0}}, rbs[i].rot.vel.y * rbs[i].rot.speed * ps->system.delta_time);
//		fill_rotation_matrix(&rot_matrix[0], (cl_float3){{0, 1, 0}}, rbs[i].rot.vel.y * rbs[i].rot.speed * ps->system.delta_time);
//		mult(&rot_matrix[0], &rbs[i].transform->right);
//		mult(&rot_matrix[0], &rbs[i].transform->up);
//		mult(&rot_matrix[0], &rbs[i].transform->forward);
	}

	return (fabs(rbs[i].rot.vel.x) > RM_FLT_EPSILON ||
			fabs(rbs[i].rot.vel.y) > RM_FLT_EPSILON ||
			fabs(rbs[i].rot.vel.z) > RM_FLT_EPSILON);
}


int					ps_func(void *psv)
{
	t_physics_system	*ps;
	size_t				i;

	SDL_SetThreadPriority(SDL_THREAD_PRIORITY_HIGH);
	ps = (t_physics_system *)psv;
	ps->system.now = SDL_GetPerformanceCounter();
	ps->system.last = ps->system.now;
	while (ps->rbs.storage)
	{
		ps->change_indicator = 0;
		i = -1;
		ps->system.delta_time = (double)(ps->system.now - ps->system.last) / SDL_GetPerformanceFrequency() / 1000;
		while (++i < ps->rbs.size)
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

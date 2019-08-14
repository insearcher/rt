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

int					ps_func(void *psv)
{
	t_physics_system	*ps;
	size_t				i;

	ps = (t_physics_system *)psv;
	ps->system.now = SDL_GetPerformanceCounter();
	ps->system.last = ps->system.now;
	while (ps->rbs)
	{
//		SDL_LockMutex(ps->system.mutex);
		i = -1;
		ps->system.delta_time = (ps->system.now - ps->system.last) / (double)SDL_GetPerformanceFrequency() / 1000;
		while (++i < ps->rbs_count)
		{
			if (fabs(ps->rbs[i].move.vel.x - ps->rbs[i].move.raw_vel.x) > CL_FLT_EPSILON)
				ps->rbs[i].move.vel.x = ft_lerp(
						ps->rbs[i].move.vel.x,
						ps->rbs[i].move.raw_vel.x,
						ps->rbs[i].move.acc);
			if (fabs(ps->rbs[i].move.vel.y - ps->rbs[i].move.raw_vel.y) > CL_FLT_EPSILON)
				ps->rbs[i].move.vel.y = ft_lerp(
						ps->rbs[i].move.vel.y,
						ps->rbs[i].move.raw_vel.y,
						ps->rbs[i].move.acc);
			if (fabs(ps->rbs[i].move.vel.z - ps->rbs[i].move.raw_vel.z) > CL_FLT_EPSILON)
				ps->rbs[i].move.vel.z = ft_lerp(
						ps->rbs[i].move.vel.z,
						ps->rbs[i].move.raw_vel.z,
						ps->rbs[i].move.acc);

			ps->rbs[i].transform->pos.v4 += ps->rbs[i].transform->forward.v4 * ps->rbs[i].move.vel.z *
										 ps->rbs[i].move.speed * ps->system.delta_time;
			ps->rbs[i].transform->pos.v4 += ps->rbs[i].transform->right.v4 * ps->rbs[i].move.vel.x *
										 ps->rbs[i].move.speed * ps->system.delta_time;
			ps->rbs[i].transform->pos.v4 += ps->rbs[i].transform->up.v4 * ps->rbs[i].move.vel.y *
										 ps->rbs[i].move.speed * ps->system.delta_time;
		}
//		SDL_UnlockMutex(ps->system.mutex);
		SDL_Delay(ps->system.delay);
		ps->system.last = ps->system.now;
		ps->system.now = SDL_GetPerformanceCounter();
	}
	return (0);
}

/// PHYSICS SYSTEM
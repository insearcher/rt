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
	t_rb				*curps;

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
			curps = ps->rbs[i];
			if (fabs(curps->move.vel.x - curps->move.raw_vel.x * curps->move.speed_mult) > CL_FLT_EPSILON)
				curps->move.vel.x = ft_lerp(
						curps->move.vel.x,
						curps->move.raw_vel.x * curps->move.speed_mult,
						curps->move.acc);
			if (fabs(curps->move.vel.y - curps->move.raw_vel.y * curps->move.speed_mult) > CL_FLT_EPSILON)
				curps->move.vel.y = ft_lerp(
						curps->move.vel.y,
						curps->move.raw_vel.y * curps->move.speed_mult,
						curps->move.acc);
			if (fabs(curps->move.vel.z - curps->move.raw_vel.z * curps->move.speed_mult) > CL_FLT_EPSILON)
				curps->move.vel.z = ft_lerp(
						curps->move.vel.z,
						curps->move.raw_vel.z * curps->move.speed_mult,
						curps->move.acc);

			curps->transform->pos.v4 += curps->transform->forward.v4 * curps->move.vel.z *
										 curps->move.speed * curps->move.speed_mult * ps->system.delta_time;
			curps->transform->pos.v4 += curps->transform->right.v4 * curps->move.vel.x *
										 curps->move.speed * curps->move.speed_mult * ps->system.delta_time;
			curps->transform->pos.v4 += curps->transform->up.v4 * curps->move.vel.y *
										 curps->move.speed * curps->move.speed_mult * ps->system.delta_time;
		}
//		SDL_UnlockMutex(ps->system.mutex);
		SDL_Delay(ps->system.delay);
		ps->system.last = ps->system.now;
		ps->system.now = SDL_GetPerformanceCounter();
	}
	return (0);
}

/// PHYSICS SYSTEM
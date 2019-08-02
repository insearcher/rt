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

#include "rt_physics.h"

int					ps_func(void *psv)
{
	t_physics_system	*ps;
	size_t				i;

	ps = (t_physics_system *)psv;
	while (ps->rbs)
	{
		i = -1;
		while (++i < ps->rbs_count)
		{
			if (ps->rbs[i]->move.vel.x != ps->rbs[i]->move.raw_vel.x)
				ps->rbs[i]->move.vel.x = ft_lerp(
						ps->rbs[i]->move.vel.x,
						ps->rbs[i]->move.raw_vel.x * ps->rbs[i]->move.speed_mult,
						ft_fmin(1, ps->rbs[i]->move.acc / fabs(ps->rbs[i]->move.vel.x -
														   ps->rbs[i]->move.raw_vel.x)));
			if (ps->rbs[i]->move.vel.y != ps->rbs[i]->move.raw_vel.y)
				ps->rbs[i]->move.vel.y = ft_lerp(
						ps->rbs[i]->move.vel.y,
						ps->rbs[i]->move.raw_vel.y * ps->rbs[i]->move.speed_mult,
						ft_fmin(1, ps->rbs[i]->move.acc / fabs(ps->rbs[i]->move.vel.y -
														   ps->rbs[i]->move.raw_vel.y)));
			if (ps->rbs[i]->move.vel.z != ps->rbs[i]->move.raw_vel.z)
				ps->rbs[i]->move.vel.z = ft_lerp(
						ps->rbs[i]->move.vel.z,
						ps->rbs[i]->move.raw_vel.z * ps->rbs[i]->move.speed_mult,
						ft_fmin(1, ps->rbs[i]->move.acc / fabs(ps->rbs[i]->move.vel.z -
														   ps->rbs[i]->move.raw_vel.z)));

			ps->rbs[i]->transform->pos.v4 += ps->rbs[i]->transform->local.forward.v4 *
										 ps->rbs[i]->move.speed;
			ps->rbs[i]->transform->pos.v4 += ps->rbs[i]->transform->local.right.v4 *
										 ps->rbs[i]->move.speed;
			ps->rbs[i]->transform->pos.v4 += ps->rbs[i]->transform->local.up.v4 *
										 ps->rbs[i]->move.speed;
		}
		SDL_Delay(ps->delay);
	}
	return (0);
}

/// PHYSICS SYSTEM

t_physics_system	*ps_init(t_phys_func *f)
{
	t_physics_system	*ps;

	if (!(ps = ft_memalloc(sizeof(t_physics_system))) ||
		!(ps->thread = SDL_CreateThread(f, "physics", ps)))
		return (NULL);
	return (ps);
}

int					ps_start(t_physics_system *p)
{
	if (!p)
		return (-1);
	SDL_DetachThread(p->thread);
	return (0);
}
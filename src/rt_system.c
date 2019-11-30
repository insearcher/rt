/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_system.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 05:13:21 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/03 20:16:18 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_system.h"

int	system_setup(t_system *s, const char *n, t_system_func *f, const size_t d)
{
	if (!(s->thread = SDL_CreateThread(f, n, s->parent)))
		return (-1);
	s->delay = d;
	return (0);
}

int	system_start(t_system *s)
{
	if (!s)
		return (-1);
	SDL_DetachThread(s->thread);
	return (0);
}

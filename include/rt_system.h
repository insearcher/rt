/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_system.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 05:13:21 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/03 20:16:18 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_SYSTEM_H
# define RT_SYSTEM_H

# ifndef OPENCL___
#  include <SDL.h>
#  include "libft.h"
# endif

typedef struct	s_system
{
	SDL_Thread	*thread;
	SDL_mutex	*mutex;
	size_t		delay;
}				t_system;

typedef	int		(t_system_func)(void *);

int				system_setup(t_system *s, const char *n, t_system_func *f, const size_t d);
int				system_start(t_system *s);

#endif

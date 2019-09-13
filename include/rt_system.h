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
# ifdef APPLE___
# include <OpenCL/opencl.h>
# else
# include <opencl.h>
# endif
#  include <SDL.h>
#  include "libft.h"
# endif

typedef struct	s_system
{
	SDL_Thread	*thread;
	size_t		delay;
	Uint64		last;
	Uint64		now;
	cl_float	delta_time;
	void		*parent;
}				t_system;

typedef	int		(t_system_func)(void *);

int				system_setup(t_system *s, const char *n, t_system_func *f, const size_t d);
int				system_start(t_system *s);

#endif

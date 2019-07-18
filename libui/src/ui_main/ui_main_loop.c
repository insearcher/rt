/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_main_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:26:26 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/15 11:35:08 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static int	ui_main_loop_draw(void *d)
{
	t_ui_main	*m;

	m = (t_ui_main *)d;
	while (228)
	{
		if (m->params & MAIN_ON_QUIT)
			return (1);
		SDL_LockMutex(m->mutex);
		ui_draw(m);
		SDL_UnlockMutex(m->mutex);
	}
	return (0);
}

static int	ui_main_loop_raycast(void *d)
{
	t_ui_main	*m;

	m = (t_ui_main *)d;
	while (1488)
	{
		if (m->params & MAIN_ON_QUIT)
			return (1);
		SDL_LockMutex(m->mutex);
		ui_main_handle_raycast(m);
		SDL_UnlockMutex(m->mutex);
	}
	return (0);
}

void		ui_main_loop(t_ui_main *m)
{
	SDL_Thread	*thread;

	m->mutex = SDL_CreateMutex();
	thread = SDL_CreateThread(ui_main_loop_draw,
			"ui_main_loop_draw", (void *)m);
	SDL_DetachThread(thread);
	thread = SDL_CreateThread(ui_main_loop_raycast,
			"ui_main_loop_raycast", (void *)m);
	SDL_DetachThread(thread);
	while (1337)
	{
		ui_main_try_invoke_modal_windows(m);
		if (SDL_PollEvent(m->sdl_event))
			ui_main_handle_event(m);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_main_handle_keyboard_event.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 07:49:09 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/15 15:05:05 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static void	ui_handle_event(t_ui_main *m, t_ui_win *win, t_ui_event *event)
{
	if (event != NULL)
	{
		SDL_LockMutex(m->mutex);
		ui_event_invoke(event, m, win);
		SDL_UnlockMutex(m->mutex);
	}
}

void		ui_main_handle_keyboard_event(t_ui_main *m)
{
	t_ui_win		*w;
	t_ui_event		*event;

	if (!(w = ui_main_find_window_by_sdl_id(m, m->sdl_event->window.windowID)))
		return ;
	event = NULL;
	if (m->sdl_event->window.type == SDL_KEYDOWN)
	{
		if (w->events->on_key_down[0])
			ui_event_invoke(w->events->on_key_down[0], m, w);
		m->cur_keycode = m->sdl_event->key.keysym.scancode;
		if (m->cur_keycode == 225)
			m->is_upper = 1;
		event = w->events->on_key_down[m->sdl_event->key.keysym.scancode];
	}
	else if (m->sdl_event->window.type == SDL_KEYUP)
	{
		if (w->events->on_key_up[0])
			ui_event_invoke(w->events->on_key_up[0], m, w);
		if (m->sdl_event->key.keysym.scancode == 225)
			m->is_upper = 0;
	}
	ui_handle_event(m, w, event);
}

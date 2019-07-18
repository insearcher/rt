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

void	ui_main_handle_keyboard_event(t_ui_main *m)
{
	t_ui_win		*win;
	t_ui_event		*event;

	if ((win = ui_main_find_window_by_sdl_id(m,
					m->sdl_event->window.windowID)) == NULL)
		return ;
	event = NULL;
	if (m->sdl_event->window.type == SDL_KEYDOWN)
	{
		m->cur_keycode = m->sdl_event->key.keysym.scancode;
		if (m->cur_keycode == 225)
			m->is_upper = 1;
		event = win->events->on_key_down[m->sdl_event->key.keysym.scancode];
	}
	else if (m->sdl_event->window.type == SDL_KEYUP
			&& m->sdl_event->key.keysym.scancode == 225)
		m->is_upper = 0;
	if (event != NULL)
	{
		SDL_LockMutex(m->mutex);
		ui_event_invoke(event, m, win);
		SDL_UnlockMutex(m->mutex);
	}
}

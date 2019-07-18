/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_main_handle_window_event.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 02:19:12 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/15 15:04:46 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static void	invoke_event_with_lock_mutex(t_ui_event *event,
		t_ui_main *m, t_ui_win *win)
{
	SDL_LockMutex(m->mutex);
	ui_event_invoke(event, m, win);
	SDL_UnlockMutex(m->mutex);
}

void		ui_main_handle_window_event(t_ui_main *m)
{
	t_ui_win	*win;
	t_ui_event	*event;

	if ((win = ui_main_find_window_by_sdl_id(m,
			m->sdl_event->window.windowID)) == NULL)
		return ;
	event = NULL;
	if (m->sdl_event->window.event == SDL_WINDOWEVENT_CLOSE)
		event = win->events->on_close;
	else if (m->sdl_event->window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
		event = win->events->on_focus_gained;
	else if (m->sdl_event->window.event == SDL_WINDOWEVENT_FOCUS_LOST)
		event = win->events->on_focus_lost;
	else if (m->sdl_event->window.event == SDL_WINDOWEVENT_ENTER)
		event = win->events->on_focus_gained;
	else if (m->sdl_event->window.event == SDL_WINDOWEVENT_LEAVE)
		event = win->events->on_focus_lost;
	else if (m->sdl_event->window.event == SDL_WINDOWEVENT_RESIZED)
		event = win->events->on_resize;
	else if (m->sdl_event->window.event == SDL_WINDOWEVENT_MOVED)
		event = win->events->on_moved;
	if (event != NULL)
		invoke_event_with_lock_mutex(event, m, win);
}

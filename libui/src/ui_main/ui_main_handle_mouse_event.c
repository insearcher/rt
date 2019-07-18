/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_main_handle_mouse_event.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 00:47:51 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/15 17:50:57 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static t_ui_event	*check_mousewheel(t_ui_main *m, t_ui_win *win)
{
	t_ui_event	*event;

	event = NULL;
	if (m->sdl_event->wheel.y < 0)
		event = win->events->on_scroll_up;
	else if (m->sdl_event->wheel.y > 0)
		event = win->events->on_scroll_down;
	return (event);
}

void				ui_main_handle_mouse_event(t_ui_main *m)
{
	t_ui_win	*win;
	t_ui_event	*event;

	if ((win = ui_main_find_window_by_sdl_id(m,
			m->sdl_event->window.windowID)) == NULL)
		return ;
	event = NULL;
	if (m->sdl_event->type == SDL_MOUSEMOTION)
		event = win->events->on_pointer_moved;
	else if (m->sdl_event->type == SDL_MOUSEBUTTONDOWN &&
			m->sdl_event->button.button == SDL_BUTTON_LEFT)
		event = win->events->on_pointer_left_button_pressed;
	else if (m->sdl_event->type == SDL_MOUSEBUTTONDOWN &&
			m->sdl_event->button.button == SDL_BUTTON_RIGHT)
		event = win->events->on_pointer_right_button_pressed;
	else if (m->sdl_event->type == SDL_MOUSEBUTTONUP &&
			m->sdl_event->button.button == SDL_BUTTON_LEFT)
		event = win->events->on_pointer_left_button_released;
	else if (m->sdl_event->type == SDL_MOUSEBUTTONUP &&
			m->sdl_event->button.button == SDL_BUTTON_RIGHT)
		event = win->events->on_pointer_right_button_released;
	else if (m->sdl_event->type == SDL_MOUSEWHEEL)
		event = check_mousewheel(m, win);
	if (event != NULL)
		ui_event_invoke(event, m, win);
}

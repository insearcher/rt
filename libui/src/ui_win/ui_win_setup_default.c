/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_win_setup_default.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 05:38:36 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/15 15:23:17 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static int	ui_win_invoke_key_down_on_focused_el(t_ui_main *m, void *a)
{
	t_ui_el	*el;

	(void)a;
	el = m->focused_el;
	if (!el)
		return (1);
	if (m->cur_keycode == SDL_SCANCODE_ESCAPE)
		m->focused_el = NULL;
	else
		ui_event_invoke(el->events->on_key_down[m->cur_keycode], m, el);
	return (1);
}

static void	ui_win_setup_default_logs(t_ui_win *w)
{
	ui_event_add_listener(w->events->on_focus_lost, ui_log_window_focus_lost);
	ui_event_add_listener(w->events->on_focus_gained,
			ui_log_window_focus_gained);
	ui_event_add_listener(w->events->on_resize, ui_log_window_resized);
	ui_event_add_listener(w->events->on_close, ui_log_window_closed);
	ui_event_add_listener(w->events->on_moved, ui_log_window_moved);
}

static void	ui_win_setup_default_keyboard_events(t_ui_win *w)
{
	int	i;

	i = -1;
	while (++i < KEYS_COUNT)
		ui_event_add_listener(w->events->on_key_down[i],
				ui_win_invoke_key_down_on_focused_el);
}

void		ui_win_setup_default(t_ui_win *w)
{
	ui_win_setup_default_keyboard_events(w);
	ui_event_add_listener(w->events->on_pointer_moved,
			ui_main_event_pointer_moved);
	ui_event_add_listener(w->events->on_pointer_left_button_pressed,
			ui_main_event_lmb_pressed);
	ui_event_add_listener(w->events->on_pointer_left_button_released,
			ui_main_event_lmb_released);
	ui_event_add_listener(w->events->on_pointer_right_button_pressed,
			ui_main_event_rmb_pressed);
	ui_event_add_listener(w->events->on_pointer_right_button_released,
			ui_main_event_rmb_released);
	ui_event_add_listener(w->events->on_scroll_up, ui_main_event_scroll_up);
	ui_event_add_listener(w->events->on_scroll_down, ui_main_event_scroll_down);
	ui_event_add_listener(w->events->on_focus_gained,
			ui_win_event_focus_gained);
	ui_event_add_listener(w->events->on_focus_lost, ui_win_event_focus_lost);
	ui_event_add_listener(w->events->on_focus_lost, ui_main_event_lmb_released);
	ui_event_add_listener(w->events->on_focus_lost, ui_main_event_rmb_released);
	if (DEBUG_STATUS == 1)
		ui_win_setup_default_logs(w);
}

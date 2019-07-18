/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_event_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 17:13:44 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/15 14:56:56 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

t_ui_event		*ui_event_init(void)
{
	t_ui_event	*e;

	if (!(e = (t_ui_event *)malloc(sizeof(t_ui_event))))
		ui_sdl_deinit(228);
	ft_bzero(e, sizeof(t_ui_event));
	return (e);
}

t_ui_el_events	*ui_event_el_events_init(void)
{
	t_ui_el_events *e;

	if (!(e = (t_ui_el_events *)malloc(sizeof(t_ui_el_events))))
		ui_sdl_deinit(228);
	ft_bzero(e, sizeof(t_ui_el_events));
	if (!(e->on_pointer_enter = ui_event_init()) ||
		!(e->on_pointer_stay = ui_event_init()) ||
		!(e->on_pointer_exit = ui_event_init()) ||
		!(e->on_pointer_left_button_pressed = ui_event_init()) ||
		!(e->on_pointer_left_button_hold = ui_event_init()) ||
		!(e->on_pointer_left_button_released = ui_event_init()) ||
		!(e->on_pointer_right_button_pressed = ui_event_init()) ||
		!(e->on_pointer_right_button_hold = ui_event_init()) ||
		!(e->on_pointer_right_button_released = ui_event_init()) ||
		!(e->on_scroll_up = ui_event_init()) ||
		!(e->on_scroll_down = ui_event_init()) ||
		!(e->on_render = ui_event_init()) ||
		!(e->on_resize = ui_event_init()))
		ui_sdl_deinit(228);
	return (e);
}

static void		init_keyboard_events(t_ui_win_events *w)
{
	int	i;

	i = KEYS_COUNT;
	if (!(w->on_key_up = (t_ui_event **)malloc(KEYS_COUNT *
			sizeof(t_ui_event *))) ||
		!(w->on_key_down = (t_ui_event **)malloc(KEYS_COUNT *
				sizeof(t_ui_event *))))
		ui_sdl_deinit(228);
	while (--i >= 0)
	{
		if (!(w->on_key_down[i] = ui_event_init()) ||
			!(w->on_key_up[i] = ui_event_init()))
			ui_sdl_deinit(228);
	}
}

t_ui_win_events	*ui_event_win_events_init(void)
{
	t_ui_win_events	*w;

	if (!(w = (t_ui_win_events *)malloc(sizeof(t_ui_win_events))))
		ui_sdl_deinit(228);
	ft_bzero(w, sizeof(t_ui_win_events));
	if (!(w->on_pointer_moved = ui_event_init()) ||
		!(w->on_pointer_enter = ui_event_init()) ||
		!(w->on_pointer_exit = ui_event_init()) ||
		!(w->on_pointer_left_button_pressed = ui_event_init()) ||
		!(w->on_pointer_left_button_released = ui_event_init()) ||
		!(w->on_pointer_right_button_pressed = ui_event_init()) ||
		!(w->on_pointer_right_button_released = ui_event_init()) ||
		!(w->on_scroll_up = ui_event_init()) ||
		!(w->on_scroll_down = ui_event_init()) ||
		!(w->on_focus_gained = ui_event_init()) ||
		!(w->on_focus_lost = ui_event_init()) ||
		!(w->on_resize = ui_event_init()) ||
		!(w->on_close = ui_event_init()) ||
		!(w->on_moved = ui_event_init()))
		ui_sdl_deinit(228);
	init_keyboard_events(w);
	return (w);
}

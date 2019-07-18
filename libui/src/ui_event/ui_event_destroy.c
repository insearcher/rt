/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_event_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 21:27:39 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/15 15:02:19 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_event_destroy(t_ui_event *e)
{
	t_list	*p;
	t_list	*l;

	l = e->events;
	p = l;
	while (l)
	{
		free(l->content);
		l = l->next;
		p->next = NULL;
		free(p);
		p = l;
	}
	free(e);
}

void	ui_event_win_events_destroy(t_ui_win_events *we)
{
	int i;

	ui_event_destroy(we->on_pointer_moved);
	ui_event_destroy(we->on_pointer_enter);
	ui_event_destroy(we->on_pointer_exit);
	ui_event_destroy(we->on_pointer_left_button_pressed);
	ui_event_destroy(we->on_pointer_left_button_released);
	ui_event_destroy(we->on_pointer_right_button_pressed);
	ui_event_destroy(we->on_pointer_right_button_released);
	ui_event_destroy(we->on_scroll_up);
	ui_event_destroy(we->on_scroll_down);
	ui_event_destroy(we->on_focus_gained);
	ui_event_destroy(we->on_focus_lost);
	ui_event_destroy(we->on_resize);
	ui_event_destroy(we->on_close);
	ui_event_destroy(we->on_moved);
	i = KEYS_COUNT;
	while (--i >= 0)
	{
		ui_event_destroy(we->on_key_down[i]);
		ui_event_destroy(we->on_key_up[i]);
	}
	free(we->on_key_down);
	free(we->on_key_up);
	free(we);
}

void	ui_event_el_events_destroy(t_ui_el_events *ee)
{
	ui_event_destroy(ee->on_pointer_enter);
	ui_event_destroy(ee->on_pointer_stay);
	ui_event_destroy(ee->on_pointer_exit);
	ui_event_destroy(ee->on_pointer_left_button_pressed);
	ui_event_destroy(ee->on_pointer_left_button_hold);
	ui_event_destroy(ee->on_pointer_left_button_released);
	ui_event_destroy(ee->on_pointer_right_button_pressed);
	ui_event_destroy(ee->on_pointer_right_button_hold);
	ui_event_destroy(ee->on_pointer_right_button_released);
	ui_event_destroy(ee->on_scroll_up);
	ui_event_destroy(ee->on_scroll_down);
	ui_event_destroy(ee->on_render);
	ui_event_destroy(ee->on_resize);
	free(ee);
}

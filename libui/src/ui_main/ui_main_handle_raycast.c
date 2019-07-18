/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_main_handle_raycast.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 00:43:05 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/15 15:23:57 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static void	invoke_status_pointer_events(t_ui_main *m,
		t_ui_el *prev, t_ui_el *cur)
{
	if (prev != NULL && cur != NULL && prev->id != cur->id)
	{
		ui_event_invoke(prev->events->on_pointer_left_button_released, m, prev);
		ui_event_invoke(prev->events->on_pointer_right_button_released,
				m, prev);
		ui_event_invoke(prev->events->on_pointer_exit, m, prev);
		ui_event_invoke(cur->events->on_pointer_enter, m, cur);
		m->raycaster->selected = cur;
	}
	else if (prev == NULL && cur != NULL)
	{
		ui_event_invoke(cur->events->on_pointer_enter, m, cur);
		m->raycaster->selected = cur;
	}
	else if (cur == NULL && prev != NULL)
	{
		ui_event_invoke(prev->events->on_pointer_left_button_released, m, prev);
		ui_event_invoke(prev->events->on_pointer_right_button_released,
				m, prev);
		ui_event_invoke(prev->events->on_pointer_exit, m, prev);
		m->raycaster->selected = NULL;
	}
}

static void	invoke_button_events(t_ui_main *m, t_ui_el *cur)
{
	if (m->params & MAIN_LMB_PRESSED)
	{
		if ((cur->params & EL_IS_TEXT) &&
				(cur->text_area->params & TEXT_IS_INPUTTING))
			m->focused_el = cur;
		ui_event_invoke(cur->events->on_pointer_left_button_pressed, m, cur);
		m->params &= ~MAIN_LMB_PRESSED;
	}
	else if (m->params & MAIN_LMB_RELEASED)
	{
		ui_event_invoke(cur->events->on_pointer_left_button_released, m, cur);
		m->params &= ~MAIN_LMB_RELEASED;
	}
	else if (m->params & MAIN_RMB_PRESSED)
	{
		ui_event_invoke(cur->events->on_pointer_right_button_pressed, m, cur);
		m->params &= ~MAIN_RMB_PRESSED;
	}
	else if (m->params & MAIN_RMB_RELEASED)
	{
		ui_event_invoke(cur->events->on_pointer_right_button_released, m, cur);
		m->params &= ~MAIN_RMB_RELEASED;
	}
}

void		ui_main_handle_raycast(t_ui_main *m)
{
	t_ui_el *prev;
	t_ui_el *cur;

	prev = m->raycaster->selected;
	cur = ui_raycast(m, m->raycaster->focused_win);
	if (prev == NULL && cur == NULL)
		return ;
	invoke_status_pointer_events(m, prev, cur);
	cur = m->raycaster->selected;
	if (cur)
	{
		if (cur->params & EL_IS_SCROLLABLE && m->params &
				(MAIN_SCROLL_DOWN | MAIN_SCROLL_UP))
		{
			if (m->params & MAIN_SCROLL_DOWN)
				ui_event_invoke(cur->events->on_scroll_down, m, cur);
			if (m->params & MAIN_SCROLL_UP)
				ui_event_invoke(cur->events->on_scroll_up, m, cur);
			m->params &= ~(MAIN_SCROLL_DOWN | MAIN_SCROLL_UP);
		}
		else
			invoke_button_events(m, cur);
	}
	if (cur)
		ui_main_handle_continious_event(m, cur);
}

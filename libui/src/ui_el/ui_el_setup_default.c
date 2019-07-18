/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_el_setup_default.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 05:50:32 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/15 15:25:14 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static void	ui_el_setup_default_logs(t_ui_el *el)
{
	ui_event_add_listener(el->events->on_pointer_enter,
			ui_log_el_pointer_enter);
	ui_event_add_listener(el->events->on_pointer_exit, ui_log_el_pointer_exit);
	ui_event_add_listener(el->events->on_pointer_stay, ui_log_el_pointer_stay);
	ui_event_add_listener(el->events->on_pointer_left_button_hold,
			ui_log_el_left_button_hold);
	ui_event_add_listener(el->events->on_pointer_left_button_pressed,
			ui_log_el_left_button_pressed);
	ui_event_add_listener(el->events->on_pointer_left_button_released,
			ui_log_el_left_button_released);
	ui_event_add_listener(el->events->on_pointer_right_button_hold,
			ui_log_el_right_button_hold);
	ui_event_add_listener(el->events->on_pointer_right_button_pressed,
			ui_log_el_right_button_pressed);
	ui_event_add_listener(el->events->on_pointer_right_button_released,
			ui_log_el_right_button_released);
}

void		ui_el_setup_default(t_ui_el *el)
{
	el->current_texture = ft_strhash("default");
	ui_event_add_listener(el->events->on_render, ui_el_event_default_draw);
	ui_event_add_listener(el->events->on_pointer_enter,
			ui_el_event_default_pointer_enter);
	ui_event_add_listener(el->events->on_pointer_exit,
			ui_el_event_default_pointer_exit);
	if (DEBUG_STATUS == 1)
		ui_el_setup_default_logs(el);
}

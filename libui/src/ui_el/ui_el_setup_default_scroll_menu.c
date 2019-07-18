/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_el_setup_default_scroll_menu.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 01:15:33 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/15 14:48:12 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static void	ui_el_setup_default_scroll_menu_logs(t_ui_el *el)
{
	ui_event_add_listener(el->events->on_scroll_down, ui_log_el_scroll_down);
	ui_event_add_listener(el->events->on_scroll_up, ui_log_el_scroll_up);
}

void		ui_el_setup_default_scroll_menu(t_ui_el *el)
{
	el->params |= EL_IS_SCROLLABLE;
	ui_event_add_listener(el->events->on_scroll_up, ui_el_event_scroll_menu_up);
	ui_event_add_listener(el->events->on_scroll_down,
			ui_el_event_scroll_menu_down);
	if (DEBUG_STATUS == 1)
		ui_el_setup_default_scroll_menu_logs(el);
}

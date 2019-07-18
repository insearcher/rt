/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_el_setup_default_scroll_menu_elem.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 21:40:00 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/15 15:25:29 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_el_setup_default_scroll_menu_elem(t_ui_el *el)
{
	el->params |= EL_IS_SCROLLABLE;
	el->params |= EL_IS_DEPENDENT;
	ui_event_add_listener(el->events->on_scroll_up,
			ui_el_event_scroll_child_menu_up);
	ui_event_add_listener(el->events->on_scroll_down,
			ui_el_event_scroll_child_menu_down);
	if (DEBUG_STATUS == 1)
	{
		ui_event_add_listener(el->events->on_scroll_up, ui_log_el_scroll_up);
		ui_event_add_listener(el->events->on_scroll_down,
				ui_log_el_scroll_down);
	}
}

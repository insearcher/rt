/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_el_setup_horizontal_draggable.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 15:52:20 by edraugr-          #+#    #+#             */
/*   Updated: 2019/07/15 14:50:27 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_el_setup_horizontal_draggable(t_ui_el *el)
{
	ui_event_add_listener(el->events->on_pointer_left_button_hold,
		ui_el_event_hor_slider_drag);
}

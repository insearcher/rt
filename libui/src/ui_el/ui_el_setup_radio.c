/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_el_setup_radio.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 19:46:25 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/15 14:50:51 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_el_setup_radio(t_ui_el *el)
{
	ui_event_add_listener(el->events->on_pointer_left_button_pressed,
			ui_el_event_switch_radio);
}

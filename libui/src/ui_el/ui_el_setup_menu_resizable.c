/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_el_setup_menu_resizable.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 20:22:08 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/15 14:51:29 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_el_setup_menu_resizable(t_ui_el *el)
{
	ui_event_add_listener(el->events->on_resize, ui_el_event_menu_resize);
}

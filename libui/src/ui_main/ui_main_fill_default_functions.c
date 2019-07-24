/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_main_fill_default_functions.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 22:43:25 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/24 22:44:38 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void        ui_main_fill_default_functions(t_ui_main *m)
{
	ui_main_add_function_by_id(m, ui_win_event_update_size,
			"ui_win_event_update_size");
	ui_main_add_function_by_id(m, ui_main_event_close_program,
			"ui_main_event_close_program");
	ui_main_add_function_by_id(m, ui_main_event_close_window,
			"ui_main_event_close_window");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_function_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:34:17 by edraugr-          #+#    #+#             */
/*   Updated: 2019/09/26 14:34:20 by edraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

void	rt_uix_add_functions(t_ui_main *m)
{
	ui_main_add_function_by_id(m, rt_uix_on_button_enter, "on_button_enter");
	ui_main_add_function_by_id(m, rt_uix_on_button_exit, "on_button_exit");
	ui_main_add_function_by_id(m, rt_uix_button_choose, "button_choose");
	ui_main_add_function_by_id(m, rt_uix_button_select, "button_select");
	ui_main_add_function_by_id(m, rt_uix_choose_none, "choose_none");
	ui_main_add_function_by_id(m, rt_uix_choose_path_trace, "choose_path_trace");
	ui_main_add_function_by_id(m, rt_uix_choose_pong, "choose_pong");
	ui_main_add_function_by_id(m, rt_uix_switch_gauss_blur, "switch_gauss_blur");
	ui_main_add_function_by_id(m, rt_uix_show_menu, "show_menu");
//	ui_main_add_function_by_id(m, rt_uix_hide_menu, "hide_menu");
}

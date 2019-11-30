/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uix_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 17:58:14 by sbednar           #+#    #+#             */
/*   Updated: 2019/09/28 17:58:19 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

static void	setup_el_data(t_ui_main *ui)
{
	t_ui_win	*uix_w;

	uix_w = ui_main_find_window_by_id(ui, 1);
	ui_win_find_el_by_id(uix_w, 20)->data = (void *)ACTIVE_MENU;
}

void	rt_uix_interface_setup(t_ui_main *ui, const char *json_path)
{
	ui_main_fill_default_functions(ui);
	rt_uix_fill_default_images(ui);
	rt_uix_add_functions(ui);
	ui_main_fill_default_fonts(ui);
	ui_jtoc_main_from_json(ui, json_path);
	setup_el_data(ui);
}

void	rt_uix_scene_setup(t_ui_main *ui)
{
	t_ui_el	*obj_menu;

	obj_menu = ui_win_find_el_by_id(ui_main_find_window_by_id(ui, 1), 52);
	fill_scene(ui, obj_menu);
}
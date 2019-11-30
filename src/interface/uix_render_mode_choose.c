/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uix_render_mode_choose.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 15:59:02 by sbednar           #+#    #+#             */
/*   Updated: 2019/09/26 15:59:05 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

int		rt_uix_choose_path_trace(t_ui_main *main, void *el_v)
{
	(void)el_v;
	((t_rt_main *)main->data)->scene->params = RT_PATH_TRACE;
	rt_render_update(main,
			ui_win_find_el_by_id(ui_main_find_window_by_id(main, 0), 1));
	return (1);
}

int		rt_uix_choose_none(t_ui_main *main, void *el_v)
{
	(void)el_v;
	((t_rt_main *)main->data)->scene->params = 0;
	rt_render_update(main,
			  ui_win_find_el_by_id(ui_main_find_window_by_id(main, 0), 1));
	return (1);
}

int		rt_uix_choose_pong(t_ui_main *main, void *el_v)
{
	(void)el_v;
	((t_rt_main *)main->data)->scene->params = RT_PHONG;
	rt_render_update(main,
			  ui_win_find_el_by_id(ui_main_find_window_by_id(main, 0), 1));
	return (1);
}

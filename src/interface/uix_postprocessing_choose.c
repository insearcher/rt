/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uix_posprocessing_choose.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 17:28:21 by sbednar           #+#    #+#             */
/*   Updated: 2019/09/26 17:28:23 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

int	rt_uix_switch_blur(t_ui_main *main, void *el_v)
{
	t_rt_main	*rt;

	rt = (t_rt_main *)main->data;
	(void)el_v;
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_blur_x"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_blur_y"));
	rt_render_update(main,
		ui_win_find_el_by_id(ui_main_find_window_by_id(main, 0), 1));
	return (1);
}

int	rt_uix_switch_monochrome(t_ui_main *main, void *el_v)
{
	t_rt_main	*rt;

	rt = (t_rt_main *)main->data;
	(void)el_v;
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_monochrome"));
	rt_render_update(main,
		ui_win_find_el_by_id(ui_main_find_window_by_id(main, 0), 1));
	return (1);
}

int	rt_uix_switch_anaglyph(t_ui_main *main, void *el_v)
{
	t_rt_main	*rt;

	rt = (t_rt_main *)main->data;
	(void)el_v;
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_anaglyph"));
	rt_render_update(main,
		ui_win_find_el_by_id(ui_main_find_window_by_id(main, 0), 1));
	return (1);
}

int	rt_uix_switch_dithering(t_ui_main *main, void *el_v)
{
	t_rt_main	*rt;

	rt = (t_rt_main *)main->data;
	(void)el_v;
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_dithering"));
	rt_render_update(main,
		ui_win_find_el_by_id(ui_main_find_window_by_id(main, 0), 1));
	return (1);
}

int	rt_uix_clear_pp(t_ui_main *main, void *el_v)
{
	t_rt_main	*rt;

	rt = (t_rt_main *)main->data;
	(void)el_v;
	vec_clear(rt->pp);
	rt_render_update(main,
		ui_win_find_el_by_id(ui_main_find_window_by_id(main, 0), 1));
	return (1);
}

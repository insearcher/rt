/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uix_posprocessing_choose.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 17:28:21 by edraugr-          #+#    #+#             */
/*   Updated: 2019/09/26 17:28:23 by edraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

int	rt_uix_switch_gauss_blur(t_ui_main *main, void *el_v)
{
	(void)el_v;
	((t_rt_main *)main->data)->params ^= RT_GAUSS_BLUR;
	rt_render_update(main,
					 ui_win_find_el_by_id(ui_main_find_window_by_id(main, 0), 1));
	return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uix_choose_obj_from_scene.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 15:19:23 by edraugr-          #+#    #+#             */
/*   Updated: 2019/10/05 15:19:27 by edraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

int			rt_uix_choose_obj_from_scene(t_ui_main *main, void *el_v)
{
	t_ui_el	*inspector;

	inspector = ui_win_find_el_by_id(
			ui_main_find_window_by_id(main, 1), INSPECTOR_EL_ID);
	inspector->data = ((t_ui_el *)el_v)->data;
	rt_uix_update_inspector_values(main);
	return 1;
}
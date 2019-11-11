/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_uix_update_inspector.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 15:28:07 by edraugr-          #+#    #+#             */
/*   Updated: 2019/10/05 15:28:10 by edraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

static void	update_transform_pos(t_object *obj, t_ui_win *win)
{
	t_ui_el	*tmp;
	char 	*new_val;

	new_val = malloc(8);
	tmp = ui_win_find_el_by_id(win, 42120);
	sprintf(new_val, "%03.3f", obj->transform.pos.x);
	ui_el_update_text(tmp, new_val);
	tmp = ui_win_find_el_by_id(win, 42220);
	sprintf(new_val, "%03.3f", obj->transform.pos.y);
	ui_el_update_text(tmp, new_val);
	tmp = ui_win_find_el_by_id(win, 42320);
	sprintf(new_val, "%03.3f", obj->transform.pos.z);
	ui_el_update_text(tmp, new_val);
	free(new_val);
}

void		rt_uix_update_inspector_values(t_ui_main *m)
{
	t_object	*obj;
	t_ui_win	*win;

	win = ui_main_find_window_by_id(m, 1);
	t_ui_el *el = ui_win_find_el_by_id(win, INSPECTOR_EL_ID);
	obj = (t_object *)(el->data);
	if (!obj)
		return ;
	update_transform_pos(obj, win);
}
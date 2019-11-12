/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uix_inspector_change_pos_button.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 16:45:24 by edraugr-          #+#    #+#             */
/*   Updated: 2019/10/05 16:45:26 by edraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

int			rt_uix_inspector_pos_button(t_ui_main *main, void *el_v)
{
	t_ui_el		*el;
	t_object	*obj;
	int 		dir;

	el = ui_win_find_el_by_id(
			ui_main_find_window_by_id(main, 1), INSPECTOR_EL_ID);
	obj = (t_object *)el->data;
	if (!obj)
		return 1;
	el = (t_ui_el *)el_v;
	dir = (el->id % 10 == 1) ? -1 : 1;
	if ((el->id / 10) % 10 == 1)
		obj->transform.pos.x += (float)dir * CHANGE_POS_SPEED;
	else if ((el->id / 10) % 10 == 2)
		obj->transform.pos.y += (float)dir * CHANGE_POS_SPEED;
	else if ((el->id / 10) % 10 == 3)
		obj->transform.pos.z += (float)dir * CHANGE_POS_SPEED;
	rt_uix_update_inspector_values(main);
	rt_render_update(main,
					 ui_win_find_el_by_id(ui_main_find_window_by_id(main, 0), 1));
	return 1;
}

int			rt_uix_inspector_rot_button(t_ui_main *main, void *el_v)
{
	t_ui_el		*el;
	t_object	*obj;
	int 		dir;

	el = ui_win_find_el_by_id(
			ui_main_find_window_by_id(main, 1), INSPECTOR_EL_ID);
	obj = (t_object *)el->data;
	if (!obj)
		return 1;
	el = (t_ui_el *)el_v;
	dir = (el->id % 10 == 1) ? -1 : 1;
	if ((el->id / 10) % 10 == 1)
		rotate_transform_around_axis(&obj->transform, (cl_float3){{1, 0, 0}}, (float)dir * CHANGE_ROT_SPEED);
	else if ((el->id / 10) % 10 == 2)
		rotate_transform_around_axis(&obj->transform, (cl_float3){{0, 1, 0}}, (float)dir * CHANGE_ROT_SPEED);
	else if ((el->id / 10) % 10 == 3)
		rotate_transform_around_axis(&obj->transform, (cl_float3){{0, 0, 1}}, (float)dir * CHANGE_ROT_SPEED);
	rt_uix_update_inspector_values(main);
	rt_render_update(main,
					 ui_win_find_el_by_id(ui_main_find_window_by_id(main, 0), 1));
	return 1;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_jtoc_efj_helper2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 07:23:40 by edraugr-          #+#    #+#             */
/*   Updated: 2019/07/15 15:13:47 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static int	ui_el_from_json_texture2(t_ui_el *e, t_jnode *n, t_jnode *t)
{
	if (t->type != string ||
			(!ft_strcmp(jtoc_get_string(t), "empty") &&
				ui_el_from_json_empty_texture(e, n)) || (!ft_strcmp(
				jtoc_get_string(t), "white") && ui_el_from_json_white_texture(
					e, n)) || (!ft_strcmp(jtoc_get_string(t), "color") &&
				ui_el_from_json_color_texture(e, n)) || (!ft_strcmp(
					jtoc_get_string(t), "gradient") &&
				ui_el_from_json_gradient_texture(e, n)))
		return (ui_jtoc_sdl_log_error("NODE EL (TEXTURE TYPE)", e->id));
	return (FUNCTION_SUCCESS);
}

int			ui_el_from_json_texture(t_ui_main *m, t_ui_el *e, t_jnode *n)
{
	t_jnode	*t;
	char	*mi;
	char	*ei;

	if ((t = jtoc_node_get_by_path(n, "type")))
	{
		if (ui_el_from_json_texture2(e, n, t))
			return (FUNCTION_FAILURE);
	}
	else
	{
		if (!(t = jtoc_node_get_by_path(n, "main_id")) ||
			!(mi = jtoc_get_string(t)) || t->type != string ||
			!(t = jtoc_node_get_by_path(n, "el_id")) || t->type != string ||
			!(ei = jtoc_get_string(t)))
			return (ui_jtoc_sdl_log_error("NODE EL (TEXTURE)", e->id));
		ui_el_add_texture_from_main_by_id(m, e, mi, ei);
	}
	return (FUNCTION_SUCCESS);
}

t_ui_event	*ui_jtoc_el_from_json_get_event_by_name(t_ui_el *e, const char *n)
{
	int			h;
	t_ui_event	*r;

	h = ft_strhash(n);
	r = NULL;
	r = (h == ft_strhash("onPointerEnter") ? e->events->on_pointer_enter : r);
	r = (h == ft_strhash("onPointerStay") ? e->events->on_pointer_stay : r);
	r = (h == ft_strhash("onPointerExit") ? e->events->on_pointer_exit : r);
	r = (h == ft_strhash("onPointerLeftButtonPressed") ?
		e->events->on_pointer_left_button_pressed : r);
	r = (h == ft_strhash("onPointerLeftButtonHold") ?
		e->events->on_pointer_left_button_hold : r);
	r = (h == ft_strhash("onPointerLeftButtonReleased") ?
		e->events->on_pointer_left_button_released : r);
	r = (h == ft_strhash("onPointerRightButtonPressed") ?
		e->events->on_pointer_right_button_pressed : r);
	r = (h == ft_strhash("onPointerRightButtonHold") ?
		e->events->on_pointer_right_button_hold : r);
	r = (h == ft_strhash("onPointerRightButtonReleased") ?
		e->events->on_pointer_right_button_released : r);
	r = (h == ft_strhash("onScrollUp") ? e->events->on_scroll_up : r);
	r = (h == ft_strhash("onScrollDown") ? e->events->on_scroll_down : r);
	r = (h == ft_strhash("onRender") ? e->events->on_render : r);
	r = (h == ft_strhash("onResize") ? e->events->on_resize : r);
	return (r);
}

int			ui_el_from_json_event(t_ui_main *m, t_ui_el *e, t_jnode *n)
{
	char				*event_name;
	char				*f_n;
	t_ui_event			*ev;
	t_pred_ptr_event	f;
	t_jnode				*tmp;

	if (n->type != object ||
		!(tmp = jtoc_node_get_by_path(n, "event_name")) ||
		tmp->type != string || !(event_name = jtoc_get_string(tmp)) ||
		!(ev = ui_jtoc_el_from_json_get_event_by_name(e, event_name)) ||
		!(tmp = jtoc_node_get_by_path(n, "func_name")) || tmp->type != string ||
		!(f_n = jtoc_get_string(tmp)) ||
		(ft_strcmp(f_n, "clear") && !(f = ui_main_get_function_by_id(m, f_n))))
		return (ui_jtoc_sdl_log_error("NODE EL (EVENT)", e->id));
	if (!ft_strcmp(f_n, "clear"))
		ui_event_clear(ev);
	else
		ui_event_add_listener(ev, f);
	return (FUNCTION_SUCCESS);
}

int			ui_el_from_json_events(t_ui_main *m, t_ui_el *e, t_jnode *n)
{
	t_jnode	*tmp;

	if ((tmp = jtoc_node_get_by_path(n, "events")))
	{
		tmp = tmp->down;
		while (tmp)
		{
			if (tmp->type != object || ui_el_from_json_event(m, e, tmp))
				ui_sdl_deinit(228);
			tmp = tmp->right;
		}
	}
	return (ui_el_from_json_cursor(m, e, n));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_jtoc_efj_helper1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 07:23:48 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/15 15:14:23 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

int	ui_el_from_json_white_texture(t_ui_el *e, t_jnode *n)
{
	t_jnode	*t;
	int		w;
	int		h;
	char	*el_id;

	if (!(t = jtoc_node_get_by_path(n, "width")) || !ui_jtoc_isnum(t->type) ||
		(w = jtoc_get_int(t)) <= 0 ||
		!(t = jtoc_node_get_by_path(n, "height")) || !ui_jtoc_isnum(t->type) ||
		(h = jtoc_get_int(t)) <= 0 ||
		!(t = jtoc_node_get_by_path(n, "el_id")) || t->type != string ||
		!(el_id = jtoc_get_string(t)))
		return (ui_jtoc_sdl_log_error("NODE EL (WHITE TEXTURE)", e->id));
	ui_el_add_white_texture(e, w, h, el_id);
	return (FUNCTION_SUCCESS);
}

int	ui_el_from_json_empty_texture(t_ui_el *e, t_jnode *n)
{
	t_jnode	*t;
	int		w;
	int		h;
	char	*el_id;

	if (!(t = jtoc_node_get_by_path(n, "width")) || !ui_jtoc_isnum(t->type) ||
		(w = jtoc_get_int(t)) <= 0 ||
		!(t = jtoc_node_get_by_path(n, "height")) || !ui_jtoc_isnum(t->type) ||
		(h = jtoc_get_int(t)) <= 0 ||
		!(t = jtoc_node_get_by_path(n, "el_id")) || t->type != string ||
		!(el_id = jtoc_get_string(t)))
		return (ui_jtoc_sdl_log_error("NODE EL (EMPTY TEXTURE)", e->id));
	ui_el_add_empty_texture(e, w, h, el_id);
	return (FUNCTION_SUCCESS);
}

int	ui_el_from_json_color_texture(t_ui_el *e, t_jnode *n)
{
	t_jnode	*t;
	char	*color;
	char	*el_id;

	if (!(t = jtoc_node_get_by_path(n, "color")) || t->type != string ||
		!(color = jtoc_get_string(t)) ||
		!(t = jtoc_node_get_by_path(n, "el_id")) || t->type != string ||
		!(el_id = jtoc_get_string(t)))
		return (ui_jtoc_sdl_log_error("NODE EL (COLOR TEXTURE)", e->id));
	ui_el_add_color_texture(e, (t_vec2){e->rect.w, e->rect.h},
		ft_atoi_base(color, 16), el_id);
	return (FUNCTION_SUCCESS);
}

int	ui_el_from_json_gradient_texture(t_ui_el *e, t_jnode *n)
{
	t_jnode	*t;
	char	*color;
	char	*el_id;

	if (!(t = jtoc_node_get_by_path(n, "color")) || t->type != string ||
		!(color = jtoc_get_string(t)) ||
		!(t = jtoc_node_get_by_path(n, "el_id")) || t->type != string ||
		!(el_id = jtoc_get_string(t)))
		return (ui_jtoc_sdl_log_error("NODE EL (GRADIENT TEXTURE)", e->id));
	ui_el_add_gradient_texture(e, (t_vec2){e->rect.w, e->rect.h},
		ft_atoi_base(color, 16), el_id);
	return (FUNCTION_SUCCESS);
}

int	ui_el_from_json_cursor(t_ui_main *m, t_ui_el *e, t_jnode *n)
{
	t_jnode		*t;
	t_cursor	*c;

	if ((n = jtoc_node_get_by_path(n, "cursor")))
	{
		if (!(c = ui_cursor_init()))
			ui_sdl_deinit(228);
		if (!(t = jtoc_node_get_by_path(n, "texture_id")) ||
			t->type != string ||
			!(c->s = ui_main_get_surface_by_id(m, jtoc_get_string(t))) ||
				!(t = jtoc_node_get_by_path(n, "hot_x"))
				|| !ui_jtoc_isnum(t->type) || !(c->hot_x = jtoc_get_int(t)) ||
				!(t = jtoc_node_get_by_path(n, "hot_y")) ||
				!ui_jtoc_isnum(t->type) ||
				!(c->hot_y = jtoc_get_int(t)))
			ui_sdl_deinit(228);
		e->data = (void *)c;
		ui_event_add_listener(e->events->on_pointer_left_button_pressed,
			ui_cursor_from_el_data);
	}
	return (FUNCTION_SUCCESS);
}

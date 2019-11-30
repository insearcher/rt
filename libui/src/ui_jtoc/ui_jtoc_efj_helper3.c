/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_jtoc_efj_helper3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar  <sbednar @student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 07:28:15 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/15 08:07:30 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

int	ui_el_from_json_textures(t_ui_main *m, t_ui_el *e, t_jnode *n)
{
	t_jnode	*t;

	if ((t = jtoc_node_get_by_path(n, "textures")))
	{
		t = t->down;
		while (t)
		{
			if (t->type != object || ui_el_from_json_texture(m, e, t))
				ui_sdl_deinit(228);
			t = t->right;
		}
	}
	if ((t = jtoc_node_get_by_path(n, "current_texture")))
	{
		if (t->type != string)
			return (ui_jtoc_sdl_log_error("NODE EL (CURRENT TEXTURE)", e->id));
		ui_el_set_current_texture_by_id(e, jtoc_get_string(t));
	}
	return (ui_el_from_json_events(m, e, n));
}

int	ui_parse_canvas(t_ui_main *m, t_ui_el *e, t_jnode *n)
{
	if (ui_el_from_json_textures(m, e, n))
		ui_sdl_deinit(228);
	return (FUNCTION_SUCCESS);
}

int	ui_el_from_json_size(t_ui_main *m, t_ui_el *e, t_jnode *n)
{
	float	x;
	float	y;
	int		p;
	t_jnode	*t;

	if (!(t = jtoc_node_get_by_path(n, "size.x")) || !ui_jtoc_isnum(t->type))
		return (ui_jtoc_sdl_log_error("NODE EL (SIZE.X)", e->id));
	x = jtoc_get_float(t);
	if (!(t = jtoc_node_get_by_path(n, "size.y")) || !ui_jtoc_isnum(t->type))
		return (ui_jtoc_sdl_log_error("NODE EL (SIZE.Y)", e->id));
	y = jtoc_get_float(t);
	p = 0;
	if ((t = jtoc_node_get_by_path(n, "size.params")))
	{
		t = t->down;
		while (t)
		{
			if (t->type != string)
				return (ui_jtoc_sdl_log_error("NODE EL (SIZE.PARAMS)", e->id));
			p |= ui_jtoc_get_pos_size(jtoc_get_string(t));
			t = t->right;
		}
	}
	ui_el_set_size(e, p, (t_fvec2){x, y});
	return (ui_el_from_json_textures(m, e, n));
}

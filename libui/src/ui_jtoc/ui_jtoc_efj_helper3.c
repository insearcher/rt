/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_jtoc_efj_helper3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <edraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 07:28:15 by edraugr-          #+#    #+#             */
/*   Updated: 2019/07/15 08:07:30 by edraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

int	ui_el_from_json_textures(t_ui_main *m, t_ui_el *e, t_jnode *n)
{
	t_jnode	*tmp;

	if ((tmp = jtoc_node_get_by_path(n, "textures")))
	{
		tmp = tmp->down;
		while (tmp)
		{
			if (tmp->type != object || ui_el_from_json_texture(m, e, tmp))
				ui_sdl_deinit(228);
			tmp = tmp->right;
		}
	}
	if ((tmp = jtoc_node_get_by_path(n, "current_texture")))
	{
		if (tmp->type != string)
			return (ui_jtoc_sdl_log_error("NODE EL (CURRENT TEXTURE)", e->id));
		ui_el_set_current_texture_by_id(e, jtoc_get_string(tmp));
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
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "size.x")) || tmp->type != number)
		return (ui_jtoc_sdl_log_error("NODE EL (SIZE.X)", e->id));
	x = jtoc_get_float(tmp);
	if (!(tmp = jtoc_node_get_by_path(n, "size.y")) || tmp->type != number)
		return (ui_jtoc_sdl_log_error("NODE EL (SIZE.Y)", e->id));
	y = jtoc_get_float(tmp);
	p = 0;
	if ((tmp = jtoc_node_get_by_path(n, "size.params")))
	{
		tmp = tmp->down;
		while (tmp)
		{
			if (tmp->type != string)
				return (ui_jtoc_sdl_log_error("NODE EL (SIZE.PARAMS)", e->id));
			p |= ui_jtoc_get_pos_size(jtoc_get_string(tmp));
			tmp = tmp->right;
		}
	}
	ui_el_set_size(e, p, (t_fvec2){x, y});
	return (ui_el_from_json_textures(m, e, n));
}

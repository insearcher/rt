/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_jtoc_el_from_json.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <edraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 06:43:29 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/15 08:06:06 by edraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static int	ui_el_from_json_pos(t_ui_main *m, t_ui_el *e,
				t_jnode *n)
{
	float	x;
	float	y;
	int		p;
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "pos.x")) || tmp->type != number)
		return (ui_jtoc_sdl_log_error("NODE EL (POS.X)", e->id));
	x = jtoc_get_float(tmp);
	if (!(tmp = jtoc_node_get_by_path(n, "pos.y")) || tmp->type != number)
		return (ui_jtoc_sdl_log_error("NODE EL (POS.Y)", e->id));
	y = jtoc_get_float(tmp);
	p = 0;
	if ((tmp = jtoc_node_get_by_path(n, "pos.params")))
	{
		tmp = tmp->down;
		while (tmp)
		{
			if (tmp->type != string)
				return (ui_jtoc_sdl_log_error("NODE EL (POS.PARAMS)", e->id));
			p |= ui_jtoc_get_pos_size(jtoc_get_string(tmp));
			tmp = tmp->right;
		}
	}
	ui_el_set_pos(e, p, (t_fvec2){x, y});
	return (ui_el_from_json_size(m, e, n));
}

static int	ui_el_from_json_params(t_ui_main *m, t_ui_el *e,
				t_jnode *n)
{
	t_jnode	*tmp;

	e->params = 0;
	if ((tmp = jtoc_node_get_by_path(n, "params")))
	{
		tmp = tmp->down;
		while (tmp)
		{
			if (tmp->type != string)
				return (ui_jtoc_sdl_log_error("NODE EL (PARAMS)", e->id));
			e->params |= ui_jtoc_get_el_param_from_string(jtoc_get_string(tmp));
			tmp = tmp->right;
		}
	}
	if (ui_jtoc_el_setup_by_type(e, n))
		ui_sdl_deinit(228);
	if (ui_jtoc_el_pref_text(m, e, n))
		ui_sdl_deinit(228);
	if (ui_jtoc_el_pref_modal_win(m, e, n))
		ui_sdl_deinit(228);
	return (ui_el_from_json_pos(m, e, n));
}

int			ui_jtoc_el_from_json(t_ui_main *m, t_ui_win *w, t_jnode *n)
{
	t_ui_el	*p;
	t_ui_el	*e;
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "id")) || tmp->type != number)
		return (ui_jtoc_sdl_log_error("NODE EL (ID)", -1));
	if (jtoc_get_int(tmp) == 0)
		ui_parse_canvas(m, w->canvas, n);
	else
	{
		if (!(e = ui_el_init()) ||
			((e->id = jtoc_get_int(tmp)) == 0) ||
			!(tmp = jtoc_node_get_by_path(n, "parent")) ||
			tmp->type != number ||
			!(p = ui_win_find_el_by_id(w, jtoc_get_int(tmp))))
			return (ui_jtoc_sdl_log_error("NODE EL (INIT/NO PARENT)", e->id));
		ui_el_add_child(p, e);
		if (ui_el_from_json_params(m, e, n))
			ui_sdl_deinit(228);
	}
	return (FUNCTION_SUCCESS);
}

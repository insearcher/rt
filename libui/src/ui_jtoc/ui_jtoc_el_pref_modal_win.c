/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_jtoc_el_pref_modal_win.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 06:56:23 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/15 14:36:08 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static int	get_win_params(t_ui_win *w, t_jnode *n)
{
	int		type;
	t_jnode *tmp;

	if ((tmp = jtoc_node_get_by_path(n, "modal_win.type")) &&
			tmp->type == string)
	{
		type = ft_strcmp(jtoc_get_string(tmp), "OK") ? 0 : 1;
		type = ft_strcmp(jtoc_get_string(tmp), "OK_CANCEL") ? type : 2;
	}
	if ((tmp = jtoc_node_get_by_path(n, "modal_win.win_id"))
			&& tmp->type == number)
		w->id = jtoc_get_int(tmp);
	else
		return (0);
	if ((tmp = jtoc_node_get_by_path(n, "modal_win.title")) &&
			tmp->type == string)
		w->title = ft_strdup(jtoc_get_string(tmp));
	else
		return (0);
	w->pos.x = SDL_WINDOWPOS_CENTERED;
	w->pos.y = SDL_WINDOWPOS_CENTERED;
	return (type);
}

int			ui_jtoc_el_pref_modal_win(t_ui_main *m, t_ui_el *e, t_jnode *n)
{
	int			type;
	t_jnode		*tmp;
	t_ui_win	*w;
	t_ui_text	ui_text;

	(void)m;
	if ((tmp = jtoc_node_get_by_path(n, "modal_win")))
	{
		w = ui_win_init();
		if ((type = get_win_params(w, n)) == 0)
			return (FUNCTION_FAILURE);
		if (ui_jtoc_pref_text_modal_win(m, tmp, &ui_text) == FUNCTION_FAILURE)
			return (FUNCTION_FAILURE);
		if (type == 1)
			ui_jtoc_create_modal_ok(m, w, &ui_text);
		else if (type == 2)
			ui_jtoc_create_modal_ok_cancel(m, w, &ui_text);
		e->modal_win = w;
		ui_event_add_listener(e->events->on_pointer_left_button_pressed,
				ui_el_event_show_window);
	}
	return (FUNCTION_SUCCESS);
}

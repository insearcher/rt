/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_el_event_close_window.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 05:12:51 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/14 16:46:43 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

int	ui_el_event_close_window(t_ui_main *m, void *a)
{
	t_ui_el		*el;
	t_ui_win	*cur_w;
	t_list		*cur;
	t_list		*prev;

	el = (t_ui_el *)a;
	prev = NULL;
	cur = m->windows;
	while (cur)
	{
		cur_w = (t_ui_win *)(cur->content);
		if (el->modal_win == cur_w)
		{
			cur_w->params |= WIN_IS_HIDDEN;
			return (1);
		}
		prev = cur;
		cur = cur->next;
	}
	return (1);
}

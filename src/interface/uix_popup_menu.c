/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uix_popup_menu.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 17:15:32 by sbednar           #+#    #+#             */
/*   Updated: 2019/09/28 17:15:35 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

static int	rt_uix_hide_local_menu(t_ui_el *el)
{
	t_list	*tmp;
	Uint32	p_id;

	tmp = el->children;
	p_id = el->id;
	el->data = (void *)UNACTIVE_MENU;
	while (tmp)
	{
		el = (t_ui_el *)tmp->content;
		if (el->id != p_id * 10)
			el->params |= EL_IS_HIDDEN;
		tmp = tmp->next;
	}
	return (1);
}

static int	rt_uix_hide_menu(t_ui_el *el)
{
	t_list	*tmp;

	tmp = el->parent->children;
	while (tmp)
	{
		el = (t_ui_el *)tmp->content;
		rt_uix_hide_local_menu(el);
		tmp = tmp->next;
	}
	return (1);
}

int			rt_uix_show_menu(t_ui_main *main, void *el_v)
{
	t_ui_el	*el;
	t_list	*tmp;
	Uint32	p_id;

	(void)main;
	el = (t_ui_el *)el_v;
	tmp = el->children;
	p_id = el->id;
	if ((int)el->data == ACTIVE_MENU)
		return (1);
	rt_uix_hide_menu(el);
	el->data = (void *)ACTIVE_MENU;
	while (tmp)
	{
		el = (t_ui_el *)tmp->content;
		if (el->id != p_id * 10)
			el->params ^= EL_IS_HIDDEN;
		tmp = tmp->next;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_selector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar  <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:15:06 by sbednar           #+#    #+#             */
/*   Updated: 2019/09/26 14:15:43 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

int		rt_uix_on_button_enter(t_ui_main *main, void *el_v)
{
    t_ui_el	*el;

	(void)main;
    el = (t_ui_el *)el_v;
    if (el->current_texture != (size_t)ft_strhash(SELECTED_BUT_STATE))
    	ui_el_set_current_texture_by_id(el, HIGHLIGHTED_BUT_STATE);
    return (1);
}

int		rt_uix_on_button_exit(t_ui_main *main, void *el_v)
{
	t_ui_el	*el;

	(void)main;
	el = (t_ui_el *)el_v;
	if (el->current_texture == (size_t)ft_strhash(HIGHLIGHTED_BUT_STATE))
		ui_el_set_current_texture_by_id(el, DEFAULT_BUT_STATE);
	return (1);
}

int		rt_uix_button_choose(t_ui_main *main, void *el_v)
{
	t_ui_el	*el;
	t_ui_el	*tmp;
	t_list	*l;

	(void)main;
	el = (t_ui_el *)el_v;
	l = el->parent->children;
	if (el->current_texture == (size_t)ft_strhash(SELECTED_BUT_STATE))
		return (1);
	while (l)
	{
		tmp = (t_ui_el *)l->content;
		if (tmp != el)
			ui_el_set_current_texture_by_id(tmp, DEFAULT_BUT_STATE);
		else
			ui_el_set_current_texture_by_id(tmp, SELECTED_BUT_STATE);
		l = l->next;
	}
	return (1);
}

int		rt_uix_button_select(t_ui_main *main, void *el_v)
{
	t_ui_el	*el;

	(void)main;
	el = (t_ui_el *)el_v;
	if (el->current_texture == (size_t)ft_strhash(SELECTED_BUT_STATE))
		ui_el_set_current_texture_by_id(el, HIGHLIGHTED_BUT_STATE);
	else
		ui_el_set_current_texture_by_id(el, SELECTED_BUT_STATE);
	return (1);
}
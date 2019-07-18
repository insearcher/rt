/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_el_set_new_size.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 21:38:55 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/13 05:56:01 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_el_set_new_size_for_children(void *a1, void *a2)
{
	t_ui_el *el;

	el = (t_ui_el *)a1;
	(void)a2;
	el->rect.w = (int)((float)el->parent->rect.w * el->rrect.w);
	el->rect.h = (int)((float)el->parent->rect.h * el->rrect.h);
	el->crect.w = el->rect.w;
	el->crect.h = el->rect.h;
}

void	ui_el_set_new_size(t_ui_el *el, t_ui_el *canvas, int type, t_fvec2 v)
{
	if ((type & PIXEL))
	{
		el->rect.w = (int)roundf(v.x);
		el->rect.h = (int)roundf(v.y);
	}
	else if ((type & ABS))
	{
		el->rect.w = (int)roundf((float)canvas->rect.w * v.x);
		el->rect.h = (int)roundf((float)canvas->rect.h * v.y);
	}
	else
	{
		el->rect.w = (int)roundf((float)el->parent->rect.w * v.x);
		el->rect.h = (int)roundf((float)el->parent->rect.h * v.y);
	}
	el->rrect.w = (float)el->rect.w / (float)el->parent->rect.w;
	el->rrect.h = (float)el->rect.h / (float)el->parent->rect.h;
	el->crect.w = el->rect.w;
	el->crect.h = el->rect.h;
	bfs_iter(el->children, ui_el_set_new_size_for_children, 0);
}

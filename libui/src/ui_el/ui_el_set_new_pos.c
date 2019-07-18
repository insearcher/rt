/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_el_set_new_pos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <edraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 21:13:32 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/15 04:06:13 by edraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static void	set_rect(t_ui_el *el, int x, int y)
{
	el->rect.x = x;
	el->rect.y = y;
}

void		ui_el_set_new_pos_for_children(void *a1, void *a2)
{
	t_ui_el	*el;

	el = (t_ui_el *)a1;
	(void)a2;
	el->rect.x = (int)roundf((float)el->parent->rect.x
			+ (float)el->parent->rect.w * el->rrect.x);
	el->rect.y = (int)roundf((float)el->parent->rect.y
			+ (float)el->parent->rect.h * el->rrect.y);
	el->crect.x = el->rect.x;
	el->crect.y = el->rect.y;
}

void		ui_el_set_new_pos(t_ui_el *el, t_ui_el *canvas, int type, t_fvec2 v)
{
	if ((type & ABS) && (type & PIXEL))
		set_rect(el, (int)roundf(v.x), (int)roundf(v.y));
	else if ((type & ABS))
		set_rect(el, (int)roundf((float)canvas->rect.w * v.x),
				(int)roundf((float)canvas->rect.h * v.y));
	else if ((type & PIXEL))
		set_rect(el, (int)roundf((float)el->parent->rect.x + v.x),
				(int)roundf((float)el->parent->rect.y + v.y));
	else
		set_rect(el, (int)roundf((float)el->parent->rect.x +
		(float)el->parent->rect.w * v.x),
				(int)roundf((float)el->parent->rect.y +
				(float)el->parent->rect.h * v.y));
	el->rrect.x = (float)(el->rect.x - el->parent->rect.x) /
			(float)el->parent->rect.w;
	el->rrect.y = (float)(el->rect.y - el->parent->rect.y) /
			(float)el->parent->rect.h;
	el->crect.x = el->rect.x;
	el->crect.y = el->rect.y;
	bfs_iter(el->children, ui_el_set_new_pos_for_children, 0);
}

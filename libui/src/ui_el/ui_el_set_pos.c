/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_el_set_pos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <edraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:45:47 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/15 04:02:37 by edraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static void	set_rect(t_ui_el *el, int x, int y)
{
	el->rect.x = x;
	el->rect.y = y;
}

void		ui_el_set_pos(t_ui_el *el, int type, t_fvec2 v)
{
	t_ui_el	*p;

	p = el;
	while (p->parent)
		p = p->parent;
	if ((type & ABS) && (type & PIXEL))
		set_rect(el, (int)roundf(v.x), (int)roundf(v.y));
	else if ((type & ABS))
		set_rect(el, (int)roundf((float)p->rect.w * v.x),
				(int)roundf((float)p->rect.h * v.y));
	else if ((type & PIXEL))
		set_rect(el, (int)roundf((float)el->parent->rect.x + v.x),
				(int)roundf((float)el->parent->rect.y + v.y));
	else
		set_rect(el, (int)roundf((float)el->parent->rect.x +
		(float)el->parent->rect.w * v.x), (int)roundf((float)el->parent->rect.y
		+ (float)el->parent->rect.h * v.y));
	el->rrect.x = (float)(el->rect.x - el->parent->rect.x) /
			(float)el->parent->rect.w;
	el->rrect.y = (float)(el->rect.y - el->parent->rect.y) /
			(float)el->parent->rect.h;
	el->crect.x = el->rect.x;
	el->crect.y = el->rect.y;
}

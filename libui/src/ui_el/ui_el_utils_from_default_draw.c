/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_el_utils_from_default_draw.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 07:40:42 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/15 08:20:43 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_el_texture_x_w(t_ui_el *e, t_rect *srect, t_rect *tmp_rect, int w)
{
	if (e->rect.x < e->parent->crect.x && e->rect.x +
			e->rect.w > e->parent->crect.x + e->parent->crect.w)
	{
		srect->x = roundf((float)(e->parent->crect.x - e->rect.x)
				* ((float)w / e->rect.w));
		srect->w = roundf((float)e->parent->crect.w * ((float)w / e->rect.w));
		tmp_rect->x = e->parent->crect.x;
		tmp_rect->w = e->parent->crect.w;
	}
	else if (e->rect.x < e->parent->crect.x)
	{
		tmp_rect->x = e->parent->crect.x;
		tmp_rect->w = e->rect.w - (e->parent->crect.x - e->rect.x);
		srect->x = roundf((float)(e->parent->crect.x - e->rect.x) *
				((float)w / (float)e->rect.w));
		srect->w = roundf((float)tmp_rect->w * ((float)w / (float)e->rect.w));
	}
	else if (e->rect.x + e->rect.w > e->parent->crect.x + e->parent->crect.w)
	{
		srect->x = 0;
		tmp_rect->w = e->parent->crect.x + e->parent->crect.w - e->rect.x;
		srect->w = roundf((float)tmp_rect->w * ((float)w / (float)e->rect.w));
		tmp_rect->x = e->rect.x;
	}
}

void	ui_el_texture_y_h(t_ui_el *e, t_rect *srect, t_rect *tmp_rect, int h)
{
	if (e->rect.y < e->parent->crect.y &&
			e->rect.y + e->rect.h > e->parent->crect.y + e->parent->crect.h)
	{
		srect->y = roundf((float)(e->parent->crect.y - e->rect.y)
				* ((float)h / (float)e->rect.h));
		srect->h = roundf((float)e->parent->crect.h
				* ((float)h / (float)e->rect.h));
		tmp_rect->y = e->parent->crect.y;
		tmp_rect->h = e->parent->crect.h;
	}
	else if (e->rect.y < e->parent->crect.y)
	{
		tmp_rect->y = e->parent->crect.y;
		tmp_rect->h = e->rect.h - (e->parent->crect.y - e->rect.y);
		srect->y = roundf((float)(e->parent->crect.y - e->rect.y)
				* ((float)h / (float)e->rect.h));
		srect->h = roundf((float)tmp_rect->h * ((float)h / (float)e->rect.h));
	}
	else if (e->rect.y + e->rect.h > e->parent->crect.y + e->parent->crect.h)
	{
		srect->y = 0;
		tmp_rect->h = e->parent->crect.y + e->parent->crect.h - e->rect.y;
		srect->h = roundf((float)tmp_rect->h * ((float)h / (float)e->rect.h));
		tmp_rect->y = e->rect.y;
	}
}

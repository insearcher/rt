/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_el_event_default_draw.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 04:32:52 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/15 08:21:03 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static void	get_texture_params(SDL_Texture *texture, t_rect *srect,
		int *width, int *height)
{
	SDL_QueryTexture(texture, NULL, NULL, width, height);
	srect->x = 0;
	srect->y = 0;
	srect->w = *width;
	srect->h = *height;
}

static void	cutting_texture_and_draw(t_ui_el *el, SDL_Texture *texture)
{
	t_rect		tmp_rect;
	t_rect		srect;
	int			width;
	int			height;

	tmp_rect = el->rect;
	get_texture_params(texture, &srect, &width, &height);
	if ((el->params & EL_IS_TEXT) && (el->text_area->params & TEXT_IS_REGULAR))
		tmp_rect.w = roundf(((float)width * tmp_rect.h) / (float)height);
	else if ((el->params & EL_IS_TEXT) && width < tmp_rect.w)
	{
		if (el->text_area->params & TEXT_IS_CENTERED)
		{
			tmp_rect.x = tmp_rect.x + ((tmp_rect.w - width) + 0.5) / 2;
			tmp_rect.w = width;
		}
		else
			tmp_rect.w = width;
	}
	ui_el_texture_x_w(el, &srect, &tmp_rect, width);
	ui_el_texture_y_h(el, &srect, &tmp_rect, height);
	el->crect = tmp_rect;
	SDL_RenderCopy(el->sdl_renderer, texture, &srect, &tmp_rect);
}

int			ui_el_event_default_draw(t_ui_main *m, void *a2)
{
	t_ui_el		*el;
	SDL_Texture	*texture;

	(void)m;
	el = (t_ui_el *)a2;
	texture = ui_el_get_current_texture(el);
	if (el->params & EL_IS_DEPENDENT)
	{
		cutting_texture_and_draw(el, texture);
		return (1);
	}
	SDL_RenderCopy(el->sdl_renderer, texture, NULL, &el->rect);
	return (1);
}

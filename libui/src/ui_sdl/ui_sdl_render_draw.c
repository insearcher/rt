/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_sdl_render_draw.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 12:22:06 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/15 12:22:17 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_sdl_render_draw_line(SDL_Renderer *r, t_vec2 *v1, t_vec2 *v2)
{
	SDL_RenderDrawLine(r, v1->x, v1->y, v2->x, v2->y);
}

void	ui_sdl_render_fill_rect(SDL_Renderer *r, SDL_Rect *rect)
{
	SDL_RenderFillRect(r, rect);
}

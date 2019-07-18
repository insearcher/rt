/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_sdl_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 12:22:49 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/15 12:23:23 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_sdl_render_copy(SDL_Renderer *r, SDL_Texture *t, SDL_Rect *r1,
		SDL_Rect *r2)
{
	SDL_RenderCopy(r, t, r1, r2);
}

void	ui_sdl_render_clear(SDL_Renderer *r)
{
	SDL_RenderClear(r);
}

void	ui_sdl_renderer_read_pixels(SDL_Renderer *r, Uint32 f, void *p, int ph)
{
	SDL_RenderReadPixels(r, NULL, f, p, ph);
}

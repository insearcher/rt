/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_sdl_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 12:24:03 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/15 12:24:07 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void		ui_sdl_destroy_texture(SDL_Texture *t)
{
	SDL_DestroyTexture(t);
}

SDL_Texture	*ui_sdl_create_texture(SDL_Renderer *r, Uint32 f, int a, t_vec2 *s)
{
	return (SDL_CreateTexture(r, f, a, s->x, s->y));
}

SDL_Texture	*ui_sdl_create_texture_from_surface(SDL_Renderer *r, SDL_Surface *s)
{
	return (SDL_CreateTextureFromSurface(r, s));
}

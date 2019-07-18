/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_sdl_set_texture_mode.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 12:23:37 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/15 12:23:40 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_sdl_set_texture_color_mode(SDL_Texture *t, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetTextureColorMod(t, r, g, b);
}

void	ui_sdl_set_texture_alpha_mode(SDL_Texture *t, Uint8 a)
{
	SDL_SetTextureAlphaMod(t, a);
}

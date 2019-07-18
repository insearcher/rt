/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_util_get_sdl_color.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 10:06:21 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/15 10:08:42 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

SDL_Color	ui_util_get_sdl_color(int color)
{
	SDL_Color	sdl_color;

	sdl_color = (SDL_Color){(Uint8)((color & 0xFF0000) >> 16),
		(Uint8)((color & 0x00FF00) >> 8), (Uint8)(color & 0x0000FF), 255};
	return (sdl_color);
}

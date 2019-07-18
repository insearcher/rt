/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_sdl_win_position.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 12:23:53 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/15 12:23:55 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_sdl_set_window_position(SDL_Window *w, int x, int y)
{
	SDL_SetWindowPosition(w, x, y);
}

void	ui_sdl_get_window_position(SDL_Window *w, int *x, int *y)
{
	SDL_GetWindowPosition(w, x, y);
}

void	ui_sdl_raise_window(SDL_Window *w)
{
	SDL_RaiseWindow(w);
}

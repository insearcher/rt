/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_win_event_update_size.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 05:57:22 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/15 10:55:59 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

int	ui_win_event_update_size(t_ui_main *m, void *a)
{
	t_ui_win	*w;

	(void)m;
	w = (t_ui_win *)a;
	if (w != NULL)
	{
		SDL_GetRendererOutputSize(w->sdl_renderer, &(w->size.x), &(w->size.y));
		if (w->size.x < 800 || w->size.y < 376)
		{
			SDL_SetWindowSize(w->sdl_window, 800, 376);
			w->size.x = 800;
			w->size.y = 376;
		}
		else
		{
			w->size.y = (int)sqrt(w->size.x * w->size.y / 2.13f);
			w->size.x = 2.13f * w->size.y;
			SDL_SetWindowSize(w->sdl_window, w->size.x, w->size.y);
		}
		w->canvas->rect.w = w->size.x;
		w->canvas->rect.h = w->size.y;
		w->canvas->crect = w->canvas->rect;
		bfs_for_resize(w->canvas, m);
	}
	return (1);
}

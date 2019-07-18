/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_main_try_invoke_modal_windows.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 15:11:08 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/15 11:34:20 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static void	show_window(t_ui_main *m, t_ui_win *w)
{
	SDL_LockMutex(m->mutex);
	SDL_ShowWindow(w->sdl_window);
	SDL_RaiseWindow(w->sdl_window);
	w->params &= ~WIN_IS_SHOWN;
	SDL_UnlockMutex(m->mutex);
}

void		ui_main_try_invoke_modal_windows(t_ui_main *m)
{
	t_list		*node;
	t_ui_win	*w;

	node = m->windows;
	while (node)
	{
		w = (t_ui_win *)node->content;
		if (w->params & WIN_IS_SHOWN)
		{
			show_window(m, w);
			return ;
		}
		if (w->params & WIN_IS_HIDDEN)
		{
			SDL_LockMutex(m->mutex);
			SDL_HideWindow(w->sdl_window);
			SDL_UnlockMutex(m->mutex);
			w->params &= ~WIN_IS_HIDDEN;
			return ;
		}
		node = node->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_main_handle_event.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.fr.42>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 22:13:11 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/15 11:53:08 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_main_handle_event(t_ui_main *m)
{
	if (m->sdl_event->type == SDL_MOUSEMOTION ||
		m->sdl_event->type == SDL_MOUSEBUTTONDOWN ||
		m->sdl_event->type == SDL_MOUSEBUTTONUP ||
		m->sdl_event->type == SDL_MOUSEWHEEL)
		ui_main_handle_mouse_event(m);
	else if (m->sdl_event->type == SDL_KEYDOWN ||
			m->sdl_event->type == SDL_KEYUP)
		ui_main_handle_keyboard_event(m);
	else if (m->sdl_event->type == SDL_WINDOWEVENT)
		ui_main_handle_window_event(m);
}

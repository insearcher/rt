/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_el_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 21:14:50 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/14 09:36:42 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static void	ui_el_text_destroy(t_ui_text *t)
{
	free(t->text);
	free(t);
}

void		ui_el_destroy(t_ui_el *e)
{
	t_list	*tmp;

	if (e->sdl_surface)
		SDL_FreeSurface(e->sdl_surface);
	tmp = e->sdl_textures;
	while (e->sdl_textures)
	{
		SDL_DestroyTexture((SDL_Texture *)e->sdl_textures->content);
		e->sdl_textures = e->sdl_textures->next;
		free(tmp);
		tmp = e->sdl_textures;
	}
	ui_el_destroy_children(e->children);
	if (e->text_area)
		ui_el_text_destroy(e->text_area);
	ui_event_el_events_destroy(e->events);
	free(e);
}

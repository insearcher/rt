/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_el_remove_texture_by_id.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <edraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 05:38:20 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/15 01:17:03 by edraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_el_remove_texture_by_id(t_ui_el *el, const char *id)
{
	t_list	*p;
	t_list	*l;
	t_list	*t;

	l = el->sdl_textures;
	p = NULL;
	while (l)
	{
		if ((int)l->content_size == ft_strhash(id))
		{
			t = l;
			if (p)
				p->next = l->next;
			else
				el->sdl_textures = l->next;
			SDL_DestroyTexture((SDL_Texture *)t->content);
			free(t);
			return ;
		}
		p = l;
		l = l->next;
	}
}

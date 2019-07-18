/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_el_add_texture_from_file.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 07:05:59 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/15 07:13:24 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

int		ui_el_add_texture_from_file(t_ui_el *el, const char *path,
		const char *tid)
{
	t_list_texture	*tmp_lst;
	SDL_Texture		*tmp;
	int				hash;

	hash = ft_strhash(tid);
	tmp_lst = NULL;
	tmp = NULL;
	if (ctid(el->sdl_textures, hash) || !(tmp_lst = ft_lstnew(NULL, 0)))
		ui_sdl_deinit(228);
	if (ui_el_load_surface_from(el, path) == FUNCTION_FAILURE
			|| (tmp = ui_el_create_texture(el)) == NULL)
		ui_sdl_deinit(228);
	tmp_lst->content_size = hash;
	tmp_lst->content = (void *)tmp;
	ft_lstadd(&(el->sdl_textures), tmp_lst);
	return (FUNCTION_SUCCESS);
}

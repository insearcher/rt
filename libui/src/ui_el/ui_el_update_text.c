/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_el_update_text.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <edraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 05:38:20 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/15 08:16:24 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static int	get_surface_from_text(t_ui_el *el)
{
	if (el->sdl_surface != NULL)
	{
		SDL_FreeSurface(el->sdl_surface);
		el->sdl_surface = NULL;
	}
	if (el->text_area->render_param & TEXT_IS_SOLID)
	{
		if (!(el->sdl_surface = TTF_RenderText_Solid(el->text_area->font,
						el->text_area->text, el->text_area->text_color)))
			return (FUNCTION_FAILURE);
	}
	else if ((el->text_area->render_param & TEXT_IS_BLENDED)
		|| el->text_area->render_param == 0)
	{
		if (!(el->sdl_surface = TTF_RenderText_Blended(el->text_area->font,
						el->text_area->text, el->text_area->text_color)))
			return (FUNCTION_FAILURE);
	}
	else if (!(el->sdl_surface = TTF_RenderText_Shaded(el->text_area->font,
		el->text_area->text, el->text_area->text_color,
		el->text_area->bg_color)))
		return (FUNCTION_FAILURE);
	return (FUNCTION_SUCCESS);
}

static void	clear_el_text(t_ui_el *el)
{
	if (el->text_area->text != NULL)
		free(el->text_area->text);
	el->text_area->text = NULL;
}

static void	get_texture(t_ui_el *el)
{
	SDL_Rect	rect;
	t_list		*n;

	ui_el_remove_texture_by_id(el, "default");
	if (get_surface_from_text(el))
		ui_el_add_empty_texture(el, el->rect.w, el->rect.h, "default");
	else
	{
		SDL_GetClipRect(el->sdl_surface, &rect);
		if (rect.w > 16384 || rect.h > 4000)
			return ;
		if (!(n = ft_lstnew(NULL, 0)))
			ui_sdl_deinit(228);
		n->content = ui_el_create_texture(el);
		n->content_size = ft_strhash("default");
		ft_lstadd(&(el->sdl_textures), n);
	}
}

int			ui_el_update_text(t_ui_el *el, const char *text)
{
	size_t		len;

	if (text == NULL)
		return (FUNCTION_SUCCESS);
	len = ft_strlen(text);
	if (el->text_area->string_len == 0 || len <= el->text_area->string_len)
	{
		clear_el_text(el);
		el->text_area->text = ft_strdup(text);
	}
	else
	{
		if (el->text_area->text != NULL)
			return (FUNCTION_SUCCESS);
		else
		{
			clear_el_text(el);
			el->text_area->text = ft_strsub(text, 0, el->text_area->string_len);
		}
	}
	get_texture(el);
	return (FUNCTION_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_el_add_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <edraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 04:27:11 by edraugr-          #+#    #+#             */
/*   Updated: 2019/07/15 07:28:58 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

int			ui_el_add_empty_texture(t_ui_el *el, int w, int h, const char *tid)
{
	t_list_texture	*tmp_lst;
	SDL_Texture		*tmp;
	int				hash;

	hash = ft_strhash(tid);
	tmp_lst = NULL;
	tmp = NULL;
	if (ctid(el->sdl_textures, hash) || !(tmp_lst = ft_lstnew(NULL, 0)))
		ui_sdl_deinit(228);
	if ((tmp = SDL_CreateTexture(el->sdl_renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, w, h)) == NULL)
		ui_sdl_deinit(228);
	SDL_SetRenderTarget(el->sdl_renderer, tmp);
	SDL_SetRenderDrawBlendMode(el->sdl_renderer, SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(el->sdl_renderer, 255, 255, 255, 0);
	SDL_SetTextureBlendMode(tmp, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(el->sdl_renderer, NULL);
	SDL_SetRenderDrawBlendMode(el->sdl_renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(el->sdl_renderer, NULL);
	SDL_SetRenderDrawColor(el->sdl_renderer, 0, 0, 0, 255);
	tmp_lst->content_size = hash;
	tmp_lst->content = (void *)tmp;
	ft_lstadd(&(el->sdl_textures), tmp_lst);
	return (FUNCTION_SUCCESS);
}

int			ui_el_add_white_texture(t_ui_el *el, int w, int h, const char *tid)
{
	t_list_texture	*tmp_lst;
	SDL_Texture		*tmp;
	int				hash;

	hash = ft_strhash(tid);
	tmp_lst = NULL;
	tmp = NULL;
	if (ctid(el->sdl_textures, hash) || !(tmp_lst = ft_lstnew(NULL, 0)))
		ui_sdl_deinit(228);
	if ((tmp = SDL_CreateTexture(el->sdl_renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, w, h)) == NULL)
		ui_sdl_deinit(228);
	SDL_SetRenderTarget(el->sdl_renderer, tmp);
	SDL_SetRenderDrawBlendMode(el->sdl_renderer, SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(el->sdl_renderer, 255, 255, 255, 255);
	SDL_SetTextureBlendMode(tmp, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(el->sdl_renderer, NULL);
	SDL_SetRenderDrawBlendMode(el->sdl_renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(el->sdl_renderer, NULL);
	SDL_SetRenderDrawColor(el->sdl_renderer, 0, 0, 0, 255);
	tmp_lst->content_size = hash;
	tmp_lst->content = (void *)tmp;
	ft_lstadd(&(el->sdl_textures), tmp_lst);
	return (FUNCTION_SUCCESS);
}

static void	draw_line(t_vec2 wh, int color, t_ui_el *el)
{
	int	i;

	i = -1;
	while (++i < wh.x)
	{
		SDL_SetRenderDrawColor(el->sdl_renderer, ((color & 0xFF0000) >> 16)
			* ((float)i / (float)wh.x), ((color & 0x00FF00) >> 8) * ((float)i
			/ (float)wh.x), (color & 0x0000FF) * ((float)i / (float)wh.x), 255);
		SDL_RenderDrawLine(el->sdl_renderer, i, 0, i, wh.y);
	}
}

int			ui_el_add_gradient_texture(t_ui_el *el, t_vec2 wh, int color,
		const char *tid)
{
	t_list_texture	*tmp_lst;
	SDL_Texture		*tmp;
	int				hash;

	hash = ft_strhash(tid);
	tmp_lst = NULL;
	tmp = NULL;
	if (ctid(el->sdl_textures, hash) || !(tmp_lst = ft_lstnew(NULL, 0)) ||
		(tmp = SDL_CreateTexture(el->sdl_renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, wh.x, wh.y)) == NULL)
		ui_sdl_deinit(228);
	SDL_SetRenderTarget(el->sdl_renderer, tmp);
	draw_line(wh, color, el);
	SDL_SetRenderTarget(el->sdl_renderer, NULL);
	SDL_SetRenderDrawColor(el->sdl_renderer, 0, 0, 0, 255);
	tmp_lst->content_size = hash;
	tmp_lst->content = (void *)tmp;
	ft_lstadd(&(el->sdl_textures), tmp_lst);
	return (FUNCTION_SUCCESS);
}

int			ui_el_add_color_texture(t_ui_el *el, t_vec2 wh, int color,
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
	if ((tmp = SDL_CreateTexture(el->sdl_renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, wh.x, wh.y)) == NULL)
		ui_sdl_deinit(228);
	SDL_SetRenderTarget(el->sdl_renderer, tmp);
	SDL_SetRenderDrawColor(el->sdl_renderer, (Uint8)((color & 0xFF0000) >> 16),
		(Uint8)((color & 0x00FF00) >> 8), (Uint8)(color & 0x0000FF), 255);
	SDL_RenderFillRect(el->sdl_renderer, NULL);
	SDL_SetRenderTarget(el->sdl_renderer, NULL);
	tmp_lst->content_size = hash;
	tmp_lst->content = (void *)tmp;
	ft_lstadd(&(el->sdl_textures), tmp_lst);
	return (FUNCTION_SUCCESS);
}

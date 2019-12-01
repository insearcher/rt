/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 18:43:24 by sbednar           #+#    #+#             */
/*   Updated: 2019/12/01 18:44:17 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static int				sdl_log_error(const char *p, const int id)
{
	SDL_Log("%s ----> ERROR <---- %s", KRED, KNRM);
	SDL_Log("INCORRECT: %s%s%s%s%s",
			p,
			id < 0 ? "" : " IN ID = ",
			KGRN,
			id < 0 ? "" : ft_itoa(id),
			KNRM);
	return (FUNCTION_FAILURE);
}

void					find_textures_size(t_rt_main *rt,
		char **texture_file, int number_of_texture)
{
	unsigned char	*tex_data;
	int				bpp;
	int				texture_w;
	int				texture_h;
	int				i;

	i = -1;
	rt->texture->texture_size = 0;
	while (++i < number_of_texture)
	{
		if (!(tex_data = stbi_load(texture_file[i], &texture_w,
			&texture_h, &bpp, 4)))
		{
			sdl_log_error("TEXTURE ERROR OR TEXTURE PATH NOT FOUND", i);
			exit(-1);
		}
		rt->texture->texture_w[i] = texture_w;
		rt->texture->texture_h[i] = texture_h - 1;
		rt->texture->texture_size += (texture_w * texture_h);
		free(tex_data);
	}
}

static void				helper(int i)
{
	sdl_log_error("TEXTURE ERROR OR TEXTURE PATH NOT FOUND", i);
	exit(-1);
}

void					get_textures(t_rt_main *rt,
		char **texture_file, int number_of_texture)
{
	unsigned char	*tex_data;
	cl_int2			xy;
	int				tts;
	int				i;

	i = -1;
	tts = 0;
	rt->texture->prev_texture_size[0] = 0;
	while (++i < number_of_texture)
	{
		if (!(tex_data = stbi_load(texture_file[i], &rt->texture->w,
			&rt->texture->h, &rt->texture->bpp, 4)))
			helper(i);
		xy.y = -1;
		while (++xy.y < rt->texture->h)
		{
			xy.x = -1;
			while (++xy.x < rt->texture->w)
				rt->texture->texture[(xy.x + (xy.y * rt->texture->w)) + tts] =
						*((int *)tex_data + xy.x + xy.y * rt->texture->w);
		}
		rt->texture->prev_texture_size[i] = tts;
		tts += rt->texture->w * (rt->texture->h - 1);
		free(tex_data);
	}
}

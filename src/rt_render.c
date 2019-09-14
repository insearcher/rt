/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 17:50:06 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/23 17:50:07 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		rt_render(t_ui_main *ui, void *el_v)
{
	t_rt_main	*rt;
	t_ui_el		*el;
	void		*pixels;
	int			pitch;
	size_t		global_size;

	rt = ui->data;
	if (!((t_physics_system *)rt->systems[1])->change_indicator)
		return (1);

	el = (t_ui_el *)el_v;
	rt->screen_size.x = el->rect.w;
	rt->screen_size.y = el->rect.h;
	global_size = rt->screen_size.x * rt->screen_size.y;

	render_processing(rt, &global_size);
	post_processing(rt, &global_size);

	SDL_LockTexture(el->sdl_textures->content, NULL, &pixels, &pitch);
	clEnqueueReadBuffer(*rt->cl->queue, rt->gpu_mem->cl_image, CL_TRUE,
						0, el->rect.h * pitch, pixels, 0, NULL, NULL);
	SDL_UnlockTexture(el->sdl_textures->content);
	SDL_RenderCopy(el->sdl_renderer, el->sdl_textures->content, NULL, NULL);

	return (1);
}
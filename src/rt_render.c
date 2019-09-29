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
	static cl_int	path_trace_count;

	el = (t_ui_el *)el_v;
	SDL_Log("%d", path_trace_count);
	rt = ui->data;
	if (!(rt->scene->params & RT_PATH_TRACE))
	{
		if (!((t_physics_system *) rt->systems[1])->change_indicator && path_trace_count != 0)
			return (1);
		path_trace_count = 1;
	}
	else if (!((t_physics_system *) rt->systems[1])->change_indicator)
		path_trace_count++;
	else
		path_trace_count = 0;

	rt->screen_size.x = el->rect.w;
	rt->screen_size.y = el->rect.h;
	global_size = rt->screen_size.x * rt->screen_size.y;

	render_processing(rt, &global_size, path_trace_count);
	post_processing(rt, &global_size);

	SDL_LockTexture(el->sdl_textures->content, NULL, &pixels, &pitch);
	clEnqueueReadBuffer(*rt->cl->queue, rt->gpu_mem->cl_image, CL_TRUE,
						0, el->rect.h * pitch, pixels, 0, NULL, NULL);
	SDL_UnlockTexture(el->sdl_textures->content);
	SDL_RenderCopy(el->sdl_renderer, el->sdl_textures->content, NULL, NULL);

	path_trace_count++;

	return (1);
}
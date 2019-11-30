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
	size_t		global_size[2];
	static int	start_flag;
	static cl_int	path_trace_count = 1;

	el = (t_ui_el *)el_v;
	rt = ui->data;
	if (!(rt->scene->params & RT_PATH_TRACE));
	else if (!((t_physics_system *) rt->systems[1])->change_indicator && start_flag != 0)
		path_trace_count++;
	else
	{
		path_trace_count = 1;
	}
	start_flag = 1;

	rt->screen_size.x = el->rect.w;
	rt->screen_size.y = el->rect.h;
	global_size[0] = rt->screen_size.x;
	global_size[1] = rt->screen_size.y;

	render_processing(rt, global_size, path_trace_count);
	post_processing(rt);

	SDL_LockTexture(el->sdl_textures->content, NULL, &pixels, &pitch);
	if (rt->pp)
		clEnqueueReadBuffer(*rt->cl->queue,
			rt->pp->size % 2 ? rt->gpu_mem->cl_aux : rt->gpu_mem->cl_image,
			CL_TRUE, 0, el->rect.h * pitch, pixels, 0, NULL, NULL);
	else
		clEnqueueReadBuffer(*rt->cl->queue, rt->gpu_mem->cl_image, CL_TRUE, 0,
		el->rect.h * pitch, pixels, 0, NULL, NULL);
	SDL_UnlockTexture(el->sdl_textures->content);
	SDL_RenderCopy(el->sdl_renderer, el->sdl_textures->content, NULL, NULL);

	return (1);
}

int		rt_render_update(t_ui_main *ui, void *el_v)
{
	t_rt_main	*rt;
	t_ui_el		*el;
	void		*pixels;
	int			pitch;
	size_t		global_size[2];
	static int	start_flag;
	static cl_int	path_trace_count = 1;

	el = (t_ui_el *)el_v;
	rt = ui->data;
	if (!(rt->scene->params & RT_PATH_TRACE))
	{

	}
	else if (!((t_physics_system *) rt->systems[1])->change_indicator && start_flag != 0)
		path_trace_count++;
	else
	{
		path_trace_count = 1;
	}
	start_flag = 1;

	rt->screen_size.x = el->rect.w;
	rt->screen_size.y = el->rect.h;
	global_size[0] = rt->screen_size.x;
	global_size[1] = rt->screen_size.y;

	render_processing(rt, global_size, path_trace_count);
	post_processing(rt);

	SDL_LockTexture(el->sdl_textures->content, NULL, &pixels, &pitch);
	if (rt->pp)
		clEnqueueReadBuffer(*rt->cl->queue,
		rt->pp->size % 2 ? rt->gpu_mem->cl_aux : rt->gpu_mem->cl_image,
		CL_TRUE, 0, el->rect.h * pitch, pixels, 0, NULL, NULL);
	else
		clEnqueueReadBuffer(*rt->cl->queue, rt->gpu_mem->cl_image, CL_TRUE, 0,
		el->rect.h * pitch, pixels, 0, NULL, NULL);
	SDL_UnlockTexture(el->sdl_textures->content);
	SDL_RenderCopy(el->sdl_renderer, el->sdl_textures->content, NULL, NULL);

	return (1);
}

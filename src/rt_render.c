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
#include <time.h>

static void	process(t_rt_main *rt, t_ui_el *el, cl_mem *cl_image, cl_mem *cl_scene, cl_mem *cl_objects, cl_mem *cl_lights)
{
	size_t		global_size;
	cl_kernel	*kernel;

	kernel = cl_get_kernel_by_name(rt->cl, "render");
	clock_t start = clock();
	clSetKernelArg(*kernel, 0, sizeof(cl_mem), cl_image);
	clSetKernelArg(*kernel, 1, sizeof(cl_mem), cl_scene);
	clSetKernelArg(*kernel, 2, sizeof(cl_mem), cl_objects);
	clSetKernelArg(*kernel, 3, sizeof(cl_mem), cl_lights);
	global_size = el->rect.w * el->rect.h;
	clEnqueueNDRangeKernel(*rt->cl->queue, *kernel, 1, NULL, &global_size, NULL, 0, NULL, NULL);

/////////////////////////////TODO put texture in element or make it static, not create/del any draw.
	void	*pixels;
	int		pitch = 0;

	SDL_LockTexture(el->sdl_textures->content, NULL, &pixels, &pitch);
	clEnqueueReadBuffer(*rt->cl->queue, *cl_image, CL_TRUE, 0, pitch * el->rect.h, pixels, 0, NULL, NULL);
	SDL_UnlockTexture(el->sdl_textures->content);

	SDL_Log("%zu", clock() - start);

	SDL_RenderCopy(el->sdl_renderer, el->sdl_textures->content, NULL, NULL);
////////////////////////////////////////////////////////////////////////////////////////////////
}

void	create_buffers(t_rt_main *rt, cl_mem *cl_scene, cl_mem *cl_objects, cl_mem *cl_lights)
{
	*cl_scene = clCreateBuffer(*rt->cl->context, CL_MEM_READ_ONLY, sizeof(t_scene), NULL, NULL);
	clEnqueueWriteBuffer(*rt->cl->queue, *cl_scene, CL_TRUE, 0, sizeof(t_scene), &rt->scenes[0], 0, NULL, NULL);

	*cl_objects = clCreateBuffer(*rt->cl->context, CL_MEM_READ_ONLY, sizeof(t_object) * rt->scenes[0].objects_count, NULL, NULL);
	clEnqueueWriteBuffer(*rt->cl->queue, *cl_objects, CL_TRUE, 0, sizeof(t_object) * rt->scenes[0].objects_count, rt->scenes[0].objects, 0, NULL, NULL);

	*cl_lights = clCreateBuffer(*rt->cl->context, CL_MEM_READ_ONLY, sizeof(t_light) * rt->scenes[0].lights_count, NULL, NULL);
	clEnqueueWriteBuffer(*rt->cl->queue, *cl_lights, CL_TRUE, 0, sizeof(t_light) * rt->scenes[0].lights_count, rt->scenes[0].lights, 0, NULL, NULL);
}

int		rt_render(t_ui_main *ui, void *a)
{
	t_rt_main	*rt;
	t_ui_el		*el;
	cl_mem		cl_image;
	cl_mem		cl_scene;
	cl_mem		cl_objects;
	cl_mem		cl_lights;

	rt = ui->data;
	if (!((t_physics_system *)rt->systems[1])->change_indicator)
		return (1);
	el = a;
	cl_image = clCreateBuffer(*rt->cl->context, CL_MEM_READ_WRITE, sizeof(int) * el->rect.w * el->rect.h , NULL, NULL);
	create_buffers(rt, &cl_scene, &cl_objects, &cl_lights);
	process(rt, el, &cl_image, &cl_scene, &cl_objects, &cl_lights);
	clReleaseMemObject(cl_image);
	clReleaseMemObject(cl_objects);
	clReleaseMemObject(cl_lights);
	clReleaseMemObject(cl_scene);
	return (1);
}
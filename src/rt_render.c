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

void	create_render_buffers(t_rt_main *rt, cl_mem *cl_scene,
		cl_mem *cl_objects, cl_mem *cl_lights)
{
	*cl_scene = clCreateBuffer(*rt->cl->context, CL_MEM_READ_ONLY,
			sizeof(t_scene), NULL, NULL);
	*cl_objects = clCreateBuffer(*rt->cl->context, CL_MEM_READ_ONLY,
			sizeof(t_object) * rt->scenes[0].objects_count, NULL, NULL);
	*cl_lights = clCreateBuffer(*rt->cl->context, CL_MEM_READ_ONLY,
			sizeof(t_light) * rt->scenes[0].lights_count, NULL, NULL);
	clEnqueueWriteBuffer(*rt->cl->queue, *cl_scene, CL_TRUE, 0,
						 sizeof(t_scene), &rt->scenes[0], 0, NULL, NULL);
	clEnqueueWriteBuffer(*rt->cl->queue, *cl_objects, CL_TRUE, 0,
						 sizeof(t_object) * rt->scenes[0].objects_count,
						 rt->scenes[0].objects, 0, NULL, NULL);
	clEnqueueWriteBuffer(*rt->cl->queue, *cl_lights, CL_TRUE, 0,
			sizeof(t_light) * rt->scenes[0].lights_count,
			rt->scenes[0].lights, 0, NULL, NULL);
}

static void	ray_march_render(t_rt_main *rt, size_t *global_size, cl_mem *cl_scene, cl_mem *cl_objects, cl_mem *cl_lights)
{
	cl_kernel	*kernel;

	kernel = cl_get_kernel_by_name(rt->cl, "render");
	clSetKernelArg(*kernel, 0, sizeof(cl_mem), &rt->gpu_mem->cl_image);
	clSetKernelArg(*kernel, 1, sizeof(cl_mem), cl_scene);
	clSetKernelArg(*kernel, 2, sizeof(cl_mem), cl_objects);
	clSetKernelArg(*kernel, 3, sizeof(cl_mem), cl_lights);
	clEnqueueNDRangeKernel(*rt->cl->queue, *kernel, 1, NULL, global_size, NULL, 0, NULL, NULL);
}

static void	gauss_blur(t_rt_main *rt, size_t *global_size)
{
	cl_kernel *kernel_gbx;
	cl_kernel *kernel_gby;

	kernel_gbx = cl_get_kernel_by_name(rt->cl, "gauss_blur_x");
	clSetKernelArg(*kernel_gbx, 0, sizeof(cl_mem), &rt->gpu_mem->cl_image);
	clSetKernelArg(*kernel_gbx, 1, sizeof(cl_mem), &rt->gpu_mem->cl_aux);
	clSetKernelArg(*kernel_gbx, 2, sizeof(cl_int2), &rt->scenes[0].camera.screen);
	clEnqueueNDRangeKernel(*rt->cl->queue, *kernel_gbx, 2, NULL, global_size,
						   NULL, 0, NULL, NULL);

	kernel_gby = cl_get_kernel_by_name(rt->cl, "gauss_blur_y");
	clSetKernelArg(*kernel_gby, 0, sizeof(cl_mem), &rt->gpu_mem->cl_aux);
	clSetKernelArg(*kernel_gby, 1, sizeof(cl_mem), &rt->gpu_mem->cl_image);
	clSetKernelArg(*kernel_gby, 2, sizeof(cl_int2), &rt->scenes[0].camera.screen);
	clEnqueueNDRangeKernel(*rt->cl->queue, *kernel_gby, 2, NULL, global_size,
						   NULL, 0, NULL, NULL);
}

static void	render_and_post_processing(t_rt_main *rt, size_t *global_size)
{
	cl_mem		cl_scene;
	cl_mem		cl_objects;
	cl_mem		cl_lights;

	create_render_buffers(rt, &cl_scene, &cl_objects, &cl_lights);
	if (rt->params & RT_RENDER_1)
		;
	else if (rt->params & RT_RENDER_2)
		ray_march_render(rt, global_size, &cl_scene, &cl_objects, &cl_lights);
	clReleaseMemObject(cl_objects);
	clReleaseMemObject(cl_lights);
	clReleaseMemObject(cl_scene);
	if (rt->params & RT_GAUSS_BLUR)
	{
		SDL_Log("ASD");
		gauss_blur(rt, global_size);
	}
}

int		rt_render(t_ui_main *ui, void *a)
{
	t_rt_main	*rt;
	t_ui_el		*el;
	size_t		global_size;
	void		*pixels;
	int			pitch;

	rt = ui->data;
	if (!((t_physics_system *)rt->systems[1])->change_indicator)
		return (1);
	el = (t_ui_el *)a;
	global_size = el->rect.w * el->rect.h;
	render_and_post_processing(rt, &global_size);
	SDL_LockTexture(el->sdl_textures->content, NULL, &pixels, &pitch);
	clEnqueueReadBuffer(*rt->cl->queue, rt->gpu_mem->cl_image, CL_TRUE,
			0, el->rect.h * pitch, pixels, 0, NULL, NULL);
	SDL_UnlockTexture(el->sdl_textures->content);
	SDL_RenderCopy(el->sdl_renderer, el->sdl_textures->content, NULL, NULL);
	return (1);
}
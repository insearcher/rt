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

#include "config.h"

//TODO create fps checker

static void	run_render(t_rt_main *rt, t_ui_el *el, cl_mem *mem_img,
		cl_mem *mem_objects, cl_mem *mem_lights)
{
	int		err;
	size_t	global_size;
	cl_kernel *kernel;

	kernel = cl_get_kernel_by_name(rt->cl, "render");
	err = clSetKernelArg(*kernel, 0, sizeof(cl_mem), mem_img);
	err |= clSetKernelArg(*kernel, 1, sizeof(int), &el->rect.w);
	err |= clSetKernelArg(*kernel, 2, sizeof(int), &el->rect.h);
	err |= clSetKernelArg(*kernel, 3, sizeof(size_t), &rt->scenes[0].objects_count);
	err |= clSetKernelArg(*kernel, 4, sizeof(cl_mem), mem_objects);
	err |= clSetKernelArg(*kernel, 5, sizeof(size_t), &rt->scenes[0].lights_count);
	err |= clSetKernelArg(*kernel, 6, sizeof(cl_mem), mem_lights);
	err |= clSetKernelArg(*kernel, 7, sizeof(cl_float3), &rt->scenes[0].camera.transform.pos);
	err |= clSetKernelArg(*kernel, 8, sizeof(cl_float3), &rt->scenes[0].camera.transform.local.right);
	err |= clSetKernelArg(*kernel, 9, sizeof(cl_float3), &rt->scenes[0].camera.transform.local.up);
	err |= clSetKernelArg(*kernel, 10, sizeof(cl_float3), &rt->scenes[0].camera.transform.local.forward);
	err |= clSetKernelArg(*kernel, 11, sizeof(float), &rt->scenes[0].camera.clipping_planes.near);
	err |= clSetKernelArg(*kernel, 12, sizeof(float), &rt->scenes[0].camera.clipping_planes.far);
	err |= clSetKernelArg(*kernel, 13, sizeof(float), &rt->scenes[0].camera.fov);
	err |= clSetKernelArg(*kernel, 14, sizeof(float), &rt->scenes[0].camera.quality);
	err |= clSetKernelArg(*kernel, 15, sizeof(cl_float3), &rt->scenes[0].ambient);
	if (err != 0)
		SDL_Log("set kernel arg - error\n");
	global_size = el->rect.w * el->rect.h;
	err = clEnqueueNDRangeKernel(*rt->cl->queue, *kernel, 1, NULL,
			&global_size, NULL, 0, NULL, NULL);
	if (err != 0)
		SDL_Log("NDR - error\n");

/////////////////////////////TODO put texture in element or make it static, not create/del any draw.
	void	*pixels;
	int		pitch = 0;
	//TODO maybe del surf, and get w and h with in other ways.
	SDL_LockTexture(el->sdl_textures->content, NULL, &pixels, &pitch);
	err = clEnqueueReadBuffer(*rt->cl->queue, *mem_img, CL_TRUE, 0,
			pitch * el->rect.h, pixels, 0, NULL, NULL);
	if (err != 0)
		SDL_Log("read buffer - error\n");
	SDL_UnlockTexture(el->sdl_textures->content);
	SDL_RenderCopy(el->sdl_renderer, el->sdl_textures->content, 0, 0);
////////////////////////////////////////////////////////////////////////////////////////////////
}

void	get_mem_for_render(t_rt_main *rt, t_ui_el *el, cl_mem *mem_img,
		cl_mem *mem_objects, cl_mem *mem_lights)
{
	int	err;

	*mem_img = clCreateBuffer(*rt->cl->context, CL_MEM_READ_WRITE, sizeof(int) * el->rect.w * el->rect.h , NULL, &err);
	if (err != 0)
		SDL_Log("create buffer for image - error\n");
	*mem_objects = clCreateBuffer(*rt->cl->context, CL_MEM_READ_ONLY, sizeof(t_object) * rt->scenes[0].objects_count, NULL, &err);
	if (err != 0)
		SDL_Log("create buffer for objects - error\n");
	*mem_lights = clCreateBuffer(*rt->cl->context, CL_MEM_READ_ONLY, sizeof(t_light) * rt->scenes[0].lights_count, NULL, &err);
	if (err != 0)
		SDL_Log("create buffer for lights - error\n");
	err = clEnqueueWriteBuffer(*rt->cl->queue, *mem_objects, CL_TRUE, 0,
			sizeof(t_object) * rt->scenes[0].objects_count,
			rt->scenes[0].objects, 0, NULL, NULL);
	err = clEnqueueWriteBuffer(*rt->cl->queue, *mem_lights, CL_TRUE, 0,
			sizeof(t_light) * rt->scenes[0].lights_count,
			rt->scenes[0].lights, 0, NULL, NULL);
	if (err != 0)
		SDL_Log("create buffer - error\n");
}

int		rt_render(t_ui_main *ui, void *a)
{
	t_rt_main	*rt;
	t_ui_el		*el;

	rt = ui->data;
	el = a;
	cl_mem		mem_img;
	cl_mem		mem_objects;
	cl_mem		mem_lights;
	get_mem_for_render(rt, el, &mem_img, &mem_objects, &mem_lights);
	run_render(rt, el, &mem_img, &mem_objects, &mem_lights);
	clReleaseMemObject(mem_img);
	clReleaseMemObject(mem_objects);
	clReleaseMemObject(mem_lights);
	return (1);
}
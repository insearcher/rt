/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_marching_render.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 17:50:06 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/23 17:50:07 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

//TODO create fps checker

void	run_render(t_conf *conf, t_ui_el *el, cl_mem *mem_img,
		cl_mem *mem_objects)
{
	int		err;
	size_t	global_size;
	cl_kernel *kernel;

	kernel = cl_get_kernel_by_name(conf->cl, "render");
	err = clSetKernelArg(*kernel, 0, sizeof(cl_mem), mem_img);
	err |= clSetKernelArg(*kernel, 1, sizeof(int), &el->sdl_surface->w);
	err |= clSetKernelArg(*kernel, 2, sizeof(int), &el->sdl_surface->h);
	err |= clSetKernelArg(*kernel, 3, sizeof(int), &conf->objects_num);
	err |= clSetKernelArg(*kernel, 4, sizeof(t_camera), &conf->camera);
	err |= clSetKernelArg(*kernel, 5, sizeof(cl_mem), mem_objects);
	if (err != 0)
		SDL_Log("set kernel arg - error\n");
	global_size = el->sdl_surface->w * el->sdl_surface->h;
	err = clEnqueueNDRangeKernel(*conf->cl->queue, *kernel, 1, NULL,
			&global_size, NULL, 0, NULL, NULL);
	if (err != 0)
		SDL_Log("NDR - error\n");

/////////////////////////////TODO put texture in element or make it static, not create/del any draw.
	void	*pixels;
	int		pitch = 0;
	//TODO maybe del surf, and get w and h with in other ways.
	SDL_Texture *t = SDL_CreateTexture(el->sdl_renderer, SDL_PIXELFORMAT_RGB888,
			SDL_TEXTUREACCESS_STREAMING, el->sdl_surface->w, el->sdl_surface->h);
	SDL_LockTexture(t, NULL, &pixels, &pitch);
	err = clEnqueueReadBuffer(*conf->cl->queue, *mem_img, CL_TRUE, 0,
			pitch * el->sdl_surface->h, pixels, 0, NULL, NULL);
	if (err != 0)
		SDL_Log("read buffer - error\n");
	SDL_UnlockTexture(t);
	SDL_RenderCopy(el->sdl_renderer, t, 0, 0);
	SDL_DestroyTexture(t);
////////////////////////////////////////////////////////////////////////////////////////////////
}

void	get_mem_for_render(t_conf *conf, t_ui_el *el, cl_mem *mem_img,
		cl_mem *mem_objects)
{
	int	err;

	*mem_img = clCreateBuffer(*conf->cl->context, CL_MEM_READ_WRITE,
			el->sdl_surface->pitch * el->sdl_surface->h, NULL, &err);
	if (err != 0)
		SDL_Log("create buffer - error\n");
	*mem_objects = clCreateBuffer(*conf->cl->context, CL_MEM_READ_ONLY,
			sizeof(t_object3d) * conf->objects_num, NULL, &err);
	if (err != 0)
		SDL_Log("create buffer - error\n");
	err = clEnqueueWriteBuffer(*conf->cl->queue, *mem_objects, CL_TRUE, 0,
			sizeof(t_object3d) * conf->objects_num,
			conf->objects, 0, NULL, NULL);
	if (err != 0)
		SDL_Log("create buffer - error\n");
}

int		ray_marching_render(t_ui_main *m, void *a)
{
	t_conf	*conf;
	t_ui_el	*el;

	conf = m->data;
	el = a;
	cl_mem		mem_img;
	cl_mem		mem_objects;
	get_mem_for_render(conf, el, &mem_img, &mem_objects);
	run_render(conf, el, &mem_img, &mem_objects);
	clReleaseMemObject(mem_img);
	clReleaseMemObject(mem_objects);
	return (1);
}
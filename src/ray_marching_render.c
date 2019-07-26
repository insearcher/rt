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

void	run_render(t_conf *conf, t_ui_el *el, cl_mem *mem_img,
		cl_mem *mem_objects)
{
	int		err;
	size_t	global_size;

	err = clSetKernelArg(*cl_get_kernel_by_name(conf->cl, "render"), 0, sizeof(cl_mem), mem_img);
	err |= clSetKernelArg(*cl_get_kernel_by_name(conf->cl, "render"), 1, sizeof(int), &el->sdl_surface->w);
	err |= clSetKernelArg(*cl_get_kernel_by_name(conf->cl, "render"), 2, sizeof(int), &el->sdl_surface->h);
	err |= clSetKernelArg(*cl_get_kernel_by_name(conf->cl, "render"), 3, sizeof(int), &conf->objects_num);
	err |= clSetKernelArg(*cl_get_kernel_by_name(conf->cl, "render"), 4, sizeof(t_camera), &conf->camera);
	err |= clSetKernelArg(*cl_get_kernel_by_name(conf->cl, "render"), 5, sizeof(cl_mem), mem_objects);
	if (err != 0)
		SDL_Log("set kernel arg - error\n");
	global_size = el->sdl_surface->w * el->sdl_surface->h;
	err = clEnqueueNDRangeKernel(*conf->cl->queue, *cl_get_kernel_by_name(conf->cl, "render"), 1, NULL,
			&global_size, NULL, 0, NULL, NULL);
	if (err != 0)
		SDL_Log("NDR - error\n");
	SDL_LockSurface(el->sdl_surface);
	err = clEnqueueReadBuffer(*conf->cl->queue, *mem_img, CL_TRUE, 0,
			el->sdl_surface->pitch * el->sdl_surface->h,
			el->sdl_surface->pixels, 0, NULL, NULL);
	SDL_UnlockSurface(el->sdl_surface);
	if (err != 0)
		SDL_Log("read buffer - error\n");
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
	SDL_Texture *t =  ui_el_create_texture(el);
	SDL_RenderCopy(el->sdl_renderer, t, 0, 0);
	SDL_DestroyTexture(t);
	clReleaseMemObject(mem_img);
	clReleaseMemObject(mem_objects);
//	conf->camera.pos.x += 0.05f;
//	conf->camera.pos.y += .02f;
//	conf->camera.pos.z += sin(conf->camera.pos.x) * 0.2f;
	return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_setup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 05:13:21 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/03 20:16:18 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_jtoc.h"
#include "rt_pp.h"

static void	fill_helper(t_rt_main *rt)
{
	rt->gpu_mem->cl_texture_h = clCreateBuffer(*rt->cl->context,
		CL_MEM_READ_ONLY, sizeof(int) * 100, NULL, NULL);
	clEnqueueWriteBuffer(*rt->cl->queue, rt->gpu_mem->cl_texture_h, CL_TRUE, 0,
		sizeof(int) * 100, &rt->texture->texture_h, 0, NULL, NULL);
	rt->gpu_mem->cl_prev_texture_size = clCreateBuffer(*rt->cl->context,
		CL_MEM_READ_ONLY, sizeof(int) * 100, NULL, NULL);
	clEnqueueWriteBuffer(*rt->cl->queue, rt->gpu_mem->cl_prev_texture_size,
		1, 0, sizeof(int) * 100, &rt->texture->prev_texture_size, 0, 0, 0);
}

static void	fill_constant_screen_gpu_mem(t_rt_main *rt, cl_int2 screen_size)
{
	rt->gpu_mem = (t_s_gpu_mem *)ft_x_memalloc(sizeof(t_s_gpu_mem));
	rt->gpu_mem->cl_image = clCreateBuffer(*rt->cl->context,
		1, sizeof(int) * screen_size.x * screen_size.y, 0, 0);
	rt->gpu_mem->cl_aux = clCreateBuffer(*rt->cl->context,
		1, sizeof(int) * screen_size.x * screen_size.y, 0, 0);
	find_textures_size(rt, rt->texture->textures_path,
		rt->texture->textures_count);
	if (!(rt->texture->texture = (int *)ft_memalloc(sizeof(int)
		* rt->texture->texture_size)))
		return ;
	get_textures(rt, rt->texture->textures_path, rt->texture->textures_count);
	rt->gpu_mem->cl_texture = clCreateBuffer(*rt->cl->context,
		1, 4 * rt->texture->texture_size, 0, 0);
	rt->gpu_mem->cl_pt_color_buf = clCreateBuffer(*rt->cl->context,
		1, sizeof(cl_float3) * screen_size.x * screen_size.y, 0, 0);
	clEnqueueWriteBuffer(*rt->cl->queue, rt->gpu_mem->cl_texture, CL_TRUE, 0,
		4 * rt->texture->texture_size, rt->texture->texture, 0, 0, 0);
	rt->gpu_mem->cl_texture_w = clCreateBuffer(*rt->cl->context,
		1, sizeof(int) * 100, 0, 0);
	clEnqueueWriteBuffer(*rt->cl->queue, rt->gpu_mem->cl_texture_w, CL_TRUE, 0,
		sizeof(int) * 100, &rt->texture->texture_w, 0, NULL, NULL);
	fill_helper(rt);
}

t_rt_main	*rt_setup(cl_int2 screen_size,
		const char *textures_path,
		const char *scene_path)
{
	t_rt_main	*rt;

	rt = (t_rt_main *)ft_memalloc(sizeof(t_rt_main));
	rt->screen_size = screen_size;
	rt->cl = cl_setup((char *[]){
		"src/cl/render.cl", "src/cl/raymarch.cl", "src/cl/sdf.cl",
		"src/cl/get_lighting.cl", "src/cl/get_cam_ray_direction.cl",
		"src/cl/uv_mapping.cl", NULL},
		(char *[]){"ray_march_render", NULL}, NULL);
	cl_setup((char *[]){
		"src/cl/pp/pp_monochrome.cl", "src/cl/pp/pp_anaglyph.cl",
		"src/cl/pp/pp_utilities.cl", "src/cl/pp/pp_blur_x.cl",
		"src/cl/pp/pp_blur_y.cl", "src/cl/pp/pp_dithering.cl", NULL},
		(char *[]){ "pp_anaglyph", "pp_monochrome", "pp_dithering",
		"pp_blur_x", "pp_blur_y", NULL}, rt->cl);
	rt->pp = vec_init(10, sizeof(t_ppnode));
	rt_jtoc_textures_setup(rt, textures_path);
	rt_jtoc_scene_setup(rt, scene_path);
	fill_constant_screen_gpu_mem(rt, screen_size);
	return (rt);
}

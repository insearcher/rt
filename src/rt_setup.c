//
// Created by Slaughterfish Becker on 2019-09-14.
//

#include "rt.h"
#include "rt_jtoc.h"
#include "rt_pp.h"

static void	fill_constant_screen_gpu_mem(t_rt_main *rt, cl_int2 screen_size)
{
	rt->gpu_mem = (t_s_gpu_mem *)ft_x_memalloc(sizeof(t_s_gpu_mem));
	rt->gpu_mem->cl_image = clCreateBuffer(*rt->cl->context,
										   CL_MEM_READ_WRITE, sizeof(int) * screen_size.x * screen_size.y,
										   NULL, NULL);
	rt->gpu_mem->cl_aux = clCreateBuffer(*rt->cl->context,
										 CL_MEM_READ_WRITE, sizeof(int) * screen_size.x * screen_size.y,
										 NULL, NULL);
	find_textures_size(rt, rt->texture->textures_path, rt->texture->textures_count);
	if (!(rt->texture->texture = (int *)ft_memalloc(sizeof(int) * rt->texture->texture_size)))
		return ;
	get_textures(rt, rt->texture->textures_path, rt->texture->textures_count);
	rt->gpu_mem->cl_texture = clCreateBuffer(*rt->cl->context,
										 CL_MEM_READ_ONLY, 4 * rt->texture->texture_size,
										 NULL, NULL);
	clEnqueueWriteBuffer(*rt->cl->queue, rt->gpu_mem->cl_texture, CL_TRUE, 0,
			4 * rt->texture->texture_size,
			rt->texture->texture, 0, NULL, NULL);
	rt->gpu_mem->cl_texture_w = clCreateBuffer(*rt->cl->context,
												  CL_MEM_READ_ONLY, sizeof(int) * 100, NULL, NULL);
	clEnqueueWriteBuffer(*rt->cl->queue, rt->gpu_mem->cl_texture_w, CL_TRUE, 0,
						 sizeof(int) * 100, &rt->texture->texture_w, 0, NULL, NULL);
	rt->gpu_mem->cl_texture_h = clCreateBuffer(*rt->cl->context,
											   CL_MEM_READ_ONLY, sizeof(int) * 100, NULL, NULL);
	clEnqueueWriteBuffer(*rt->cl->queue, rt->gpu_mem->cl_texture_h, CL_TRUE, 0,
						 sizeof(int) * 100, &rt->texture->texture_h, 0, NULL, NULL);
	rt->gpu_mem->cl_prev_texture_size = clCreateBuffer(*rt->cl->context,
			CL_MEM_READ_ONLY, sizeof(int) * 100, NULL, NULL);
	clEnqueueWriteBuffer(*rt->cl->queue, rt->gpu_mem->cl_prev_texture_size, CL_TRUE, 0,
						 sizeof(int) * 100, &rt->texture->prev_texture_size, 0, NULL, NULL);
}

t_rt_main	*rt_setup(cl_int2 screen_size,
		const char *textures_path,
		const char *scene_path)
{
	t_rt_main	*rt;

	rt = (t_rt_main *)ft_memalloc(sizeof(t_rt_main));
	rt->screen_size = screen_size;
	rt->cl = cl_setup((char *[]){
							  "src/cl/render.c",
							  "src/cl/raymarch.c",
							  "src/cl/sdf.c",
							  "src/cl/get_lighting.c",
							  "src/cl/get_cam_ray_direction.c",
							  "src/cl/uv_mapping.cl",
							  "src/cl/choose_texture_for_object.cl",
							  "src/cl/pp/pp_utilities.c",
//							  "src/cl/gauss_blur.c",
							  NULL},
					  (char *[]){"ray_march_render", NULL}, NULL);
	cl_setup((char *[]){
			"src/cl/pp/pp_monochrome.c",
			"src/cl/pp/pp_anaglyph.c",
			"src/cl/pp/pp_utilities.c",
			"src/cl/pp/pp_dithering.c",
			NULL},
			(char *[]){
			"pp_anaglyph", "pp_monochrome", "pp_dithering",
			NULL}, rt->cl);
	cl_setup((char *[]){
					 "src/cl/pp/pp_blur_x.c",
					 "src/cl/pp/pp_blur_y.c",
					 "src/cl/pp/pp_utilities.c",
					 NULL},
			 (char *[]){
					 "pp_blur_x", "pp_blur_y",
					 NULL}, rt->cl);
	rt->pp = vec_init(5, sizeof(t_ppnode));
//	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_"));
//	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_monochrome"));
//	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_monochrome"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_dithering"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_anaglyph"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_blur_x"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_blur_y"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_anaglyph"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_blur_x"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_blur_y"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_anaglyph"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_blur_x"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_blur_y"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_blur_x"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_blur_y"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_blur_x"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_blur_y"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_blur_x"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_blur_y"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_blur_x"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_blur_y"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_blur_x"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_blur_y"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_blur_x"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_blur_y"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_blur_x"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_blur_y"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_blur_x"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_blur_y"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_blur_x"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_blur_y"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_blur_x"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_blur_y"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_blur_x"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_blur_y"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_blur_x"));
	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_blur_y"));
//	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_anaglyph"));
//	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_anaglyph"));
//	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_anaglyph"));
//	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_anaglyph"));
//	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_anaglyph"));
//	vec_push_back(rt->pp, cl_get_kernel_by_name(rt->cl, "pp_anaglyph"));
	rt_jtoc_textures_setup(rt, textures_path);
	rt_jtoc_scene_setup(rt, scene_path);
	fill_constant_screen_gpu_mem(rt, screen_size);
	return (rt);
}

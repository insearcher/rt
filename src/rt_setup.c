//
// Created by Slaughterfish Becker on 2019-09-14.
//

#include "rt.h"
#include "rt_jtoc.h"

static void	fill_constant_screen_gpu_mem(t_rt_main *rt, cl_int2 screen_size)
{
	rt->gpu_mem = (t_s_gpu_mem *)ft_x_memalloc(sizeof(t_s_gpu_mem));
	rt->gpu_mem->cl_image = clCreateBuffer(*rt->cl->context,
										   CL_MEM_READ_WRITE, sizeof(int) * screen_size.x * screen_size.y,
										   NULL, NULL);
	rt->gpu_mem->cl_aux = clCreateBuffer(*rt->cl->context,
										 CL_MEM_READ_WRITE, sizeof(int) * screen_size.x * screen_size.y,
										 NULL, NULL);
	rt->texture.texture = get_texture(rt);
	rt->gpu_mem->cl_texture = clCreateBuffer(*rt->cl->context,
										 CL_MEM_READ_ONLY, 4 * rt->texture.w * rt->texture.h,
										 NULL, NULL);
	clEnqueueWriteBuffer(*rt->cl->queue, rt->gpu_mem->cl_texture, CL_TRUE, 0,
			4 * rt->texture.h * rt->texture.w,
			rt->texture.texture, 0, NULL, NULL);
}

t_rt_main	*setup_rt(cl_int2 screen_size)
{
	t_rt_main	*rt;

	rt = (t_rt_main *)ft_memalloc(sizeof(t_rt_main));
	rt->screen_size = screen_size;
	rt->cl = cl_setup((char *[]){
							  "src/cl/render.c",
							  "src/cl/raymarch.c",
							  "src/cl/sdf.c",
							  "src/cl/ray.c",
							  NULL},
					  (char *[]){"render", NULL});
	rt->scenes = rt_jtoc_scenes_setup((char *[]){
			"json/scenes/scene_1.json",
			NULL});
	fill_constant_screen_gpu_mem(rt, screen_size);
	rt->params |= RT_RENDER_2;
	return (rt);
}

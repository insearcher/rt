#include "rt.h"
#include "time.h"

static void	create_buffers_for_render(t_rt_main *rt, cl_mem *cl_scene,
							  cl_mem *cl_objects, cl_mem *cl_lights)
{
	*cl_scene = clCreateBuffer(*rt->cl->context, CL_MEM_READ_ONLY,
							   sizeof(t_scene), NULL, NULL);
	*cl_objects = clCreateBuffer(*rt->cl->context, CL_MEM_READ_ONLY,
								 sizeof(t_object) * rt->scene[0].objects->size, NULL, NULL);
	*cl_lights = clCreateBuffer(*rt->cl->context, CL_MEM_READ_ONLY,
								sizeof(t_light) * rt->scene[0].lights->size, NULL, NULL);
	clEnqueueWriteBuffer(*rt->cl->queue, *cl_scene, CL_TRUE, 0,
						 sizeof(t_scene), &rt->scene[0], 0, NULL, NULL);
	clEnqueueWriteBuffer(*rt->cl->queue, *cl_objects, CL_TRUE, 0,
						 sizeof(t_object) * rt->scene[0].objects->size,
						 rt->scene[0].objects->storage, 0, NULL, NULL);
	clEnqueueWriteBuffer(*rt->cl->queue, *cl_lights, CL_TRUE, 0,
						 sizeof(t_light) * rt->scene[0].lights->size,
						 rt->scene[0].lights->storage, 0, NULL, NULL);
}

int time1;
int time2;

void	render_processing(t_rt_main *rt, size_t *global_size, cl_int path_trace_count)
{
	cl_kernel		*kernel;
	cl_mem			cl_scene;
	cl_mem			cl_objects;
	cl_mem			cl_lights;

	time2 = SDL_GetTicks();
	SDL_Log("TICK: %d", time2 - time1);
	time1 = time2;

	create_buffers_for_render(rt, &cl_scene, &cl_objects, &cl_lights);

//	rt->scenes[0].objects[0].params.mandelbulb.power = 10 + 10 * (sin(clock() / (CLOCKS_PER_SEC * 10.0f)) + 1); //для изменения фрактала со временем
//	rt->scene[0].objects[0].params.mandelbox.scale = -3.73 + 1.3 * (sin(clock() / (CLOCKS_PER_SEC * 3.0f)) + 1); //для изменения фрактала со временем
	kernel = cl_get_kernel_by_name(rt->cl, "ray_march_render");

	cl_int2	rands;
	rands.x = rand();
	rands.y = rand();

	clSetKernelArg(*kernel, 0, sizeof(cl_mem), &rt->gpu_mem->cl_image);
	clSetKernelArg(*kernel, 1, sizeof(cl_mem), &cl_scene);
	clSetKernelArg(*kernel, 2, sizeof(cl_mem), &cl_objects);
	clSetKernelArg(*kernel, 3, sizeof(cl_int), &rt->scene->objects->size);
	clSetKernelArg(*kernel, 4, sizeof(cl_mem), &cl_lights);
	clSetKernelArg(*kernel, 5, sizeof(cl_mem),  &rt->scene->lights->size);
	clSetKernelArg(*kernel, 6, sizeof(cl_int2), &rt->screen_size);
	clSetKernelArg(*kernel, 7, sizeof(cl_mem), &rt->gpu_mem->cl_texture);
	clSetKernelArg(*kernel, 8, sizeof(cl_mem), &rt->gpu_mem->cl_texture_w);
	clSetKernelArg(*kernel, 9, sizeof(cl_mem), &rt->gpu_mem->cl_texture_h);
	clSetKernelArg(*kernel, 10, sizeof(cl_mem), &rt->gpu_mem->cl_prev_texture_size);
	clSetKernelArg(*kernel, 11, sizeof(cl_int), &path_trace_count);
	clSetKernelArg(*kernel, 12, sizeof(cl_mem), &rt->gpu_mem->cl_pt_color_buf);
	clSetKernelArg(*kernel, 13, sizeof(cl_int2), &rands);

	clEnqueueNDRangeKernel(*rt->cl->queue, *kernel, 1, NULL, global_size, NULL, 0, NULL, NULL);

	clReleaseMemObject(cl_objects);
	clReleaseMemObject(cl_lights);
	clReleaseMemObject(cl_scene);
}

#include "rt.h"
#include "time.h"

static void	create_buffers_for_render(t_rt_main *rt, cl_mem *cl_scene,
							  cl_mem *cl_objects, cl_mem *cl_lights)
{
	*cl_scene = clCreateBuffer(*rt->cl->context, CL_MEM_READ_ONLY,
							   sizeof(t_scene), NULL, NULL);
	*cl_objects = clCreateBuffer(*rt->cl->context, CL_MEM_READ_ONLY,
								 sizeof(t_object) * rt->scene[0].objects_count, NULL, NULL);
	*cl_lights = clCreateBuffer(*rt->cl->context, CL_MEM_READ_ONLY,
								sizeof(t_light) * rt->scene[0].lights_count, NULL, NULL);
	clEnqueueWriteBuffer(*rt->cl->queue, *cl_scene, CL_TRUE, 0,
						 sizeof(t_scene), &rt->scene[0], 0, NULL, NULL);
	clEnqueueWriteBuffer(*rt->cl->queue, *cl_objects, CL_TRUE, 0,
						 sizeof(t_object) * rt->scene[0].objects_count,
						 rt->scene[0].objects, 0, NULL, NULL);
	clEnqueueWriteBuffer(*rt->cl->queue, *cl_lights, CL_TRUE, 0,
						 sizeof(t_light) * rt->scene[0].lights_count,
						 rt->scene[0].lights, 0, NULL, NULL);
}

void	render_processing(t_rt_main *rt, size_t *global_size)
{
	cl_kernel	*kernel;
	cl_mem		cl_scene;
	cl_mem		cl_objects;
	cl_mem		cl_lights;

	create_buffers_for_render(rt, &cl_scene, &cl_objects, &cl_lights);

//	rt->scenes[0].objects[0].params.mandelbulb.power = 10 + 10 * (sin(clock() / (CLOCKS_PER_SEC * 10.0f)) + 1); //для изменения фрактала со временем
	kernel = cl_get_kernel_by_name(rt->cl, "ray_march_render");

	cl_int2	rands;
	rands.x = rand();
	rands.y = rand();

	clSetKernelArg(*kernel, 0, sizeof(cl_mem), &rt->gpu_mem->cl_image);
	clSetKernelArg(*kernel, 1, sizeof(t_scene), rt->scene);
	clSetKernelArg(*kernel, 2, sizeof(cl_mem), &cl_objects);
	clSetKernelArg(*kernel, 3, sizeof(cl_mem), &cl_lights);
	clSetKernelArg(*kernel, 4, sizeof(cl_int2), &rt->screen_size);
	clSetKernelArg(*kernel, 5, sizeof(cl_mem), &rt->gpu_mem->cl_texture);
	clSetKernelArg(*kernel, 6, sizeof(cl_mem), &rt->gpu_mem->cl_texture_w);
	clSetKernelArg(*kernel, 7, sizeof(cl_mem), &rt->gpu_mem->cl_texture_h);
	clSetKernelArg(*kernel, 8, sizeof(cl_mem), &rt->gpu_mem->cl_prev_texture_size);
	clSetKernelArg(*kernel, 9, sizeof(cl_int2), &rands);

	clEnqueueNDRangeKernel(*rt->cl->queue, *kernel, 1, NULL, global_size, NULL, 0, NULL, NULL);

	clReleaseMemObject(cl_objects);
	clReleaseMemObject(cl_lights);
	clReleaseMemObject(cl_scene);
}

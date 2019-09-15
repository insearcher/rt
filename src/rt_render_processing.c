#include "rt.h"

static void	create_buffers_for_render(t_rt_main *rt, cl_mem *cl_scene,
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

void	render_processing(t_rt_main *rt, size_t *global_size)
{
	cl_kernel	*kernel;
	cl_mem		cl_scene;
	cl_mem		cl_objects;
	cl_mem		cl_lights;

	create_buffers_for_render(rt, &cl_scene, &cl_objects, &cl_lights);

	kernel = NULL;
	if (rt->params & RT_RENDER_1)
		;
	else if (rt->params & RT_RENDER_2)
		kernel = cl_get_kernel_by_name(rt->cl, "render");

	clSetKernelArg(*kernel, 0, sizeof(cl_mem), &rt->gpu_mem->cl_image);
	clSetKernelArg(*kernel, 1, sizeof(cl_mem), &cl_scene);
	clSetKernelArg(*kernel, 2, sizeof(cl_mem), &cl_objects);
	clSetKernelArg(*kernel, 3, sizeof(cl_mem), &cl_lights);
	clSetKernelArg(*kernel, 4, sizeof(cl_int2), &rt->screen_size);
	clSetKernelArg(*kernel, 5, sizeof(cl_mem), &rt->gpu_mem->cl_texture);

	clEnqueueNDRangeKernel(*rt->cl->queue, *kernel, 1, NULL, global_size, NULL, 0, NULL, NULL);

	clReleaseMemObject(cl_objects);
	clReleaseMemObject(cl_lights);
	clReleaseMemObject(cl_scene);
}
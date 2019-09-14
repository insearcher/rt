#include "rt.h"

static void	gauss_blur(t_rt_main *rt, size_t *global_size)
{
	cl_kernel *kernel_gbx;
	cl_kernel *kernel_gby;

	kernel_gbx = cl_get_kernel_by_name(rt->cl, "gauss_blur_x");
	clSetKernelArg(*kernel_gbx, 0, sizeof(cl_mem), &rt->gpu_mem->cl_image);
	clSetKernelArg(*kernel_gbx, 1, sizeof(cl_mem), &rt->gpu_mem->cl_aux);
	clSetKernelArg(*kernel_gbx, 2, sizeof(cl_int2), &rt->screen_size);
	clEnqueueNDRangeKernel(*rt->cl->queue, *kernel_gbx, 2, NULL, global_size,
						   NULL, 0, NULL, NULL);

	kernel_gby = cl_get_kernel_by_name(rt->cl, "gauss_blur_y");
	clSetKernelArg(*kernel_gby, 0, sizeof(cl_mem), &rt->gpu_mem->cl_aux);
	clSetKernelArg(*kernel_gby, 1, sizeof(cl_mem), &rt->gpu_mem->cl_image);
	clSetKernelArg(*kernel_gby, 2, sizeof(cl_int2), &rt->screen_size);
	clEnqueueNDRangeKernel(*rt->cl->queue, *kernel_gby, 2, NULL, global_size,
						   NULL, 0, NULL, NULL);
}

void	post_processing(t_rt_main *rt, size_t *global_size)
{
	if (rt->params & RT_GAUSS_BLUR)
	{
		SDL_Log("ASD");
		gauss_blur(rt, global_size);
	}
}

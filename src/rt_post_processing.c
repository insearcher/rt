#include "rt.h"

//static void	gauss_blur(t_rt_main *rt, size_t *global_size)
//{
//	cl_kernel *kernel_gbx;
//	cl_kernel *kernel_gby;
//
//	size_t arr[2] = {rt->screen_size.x, rt->screen_size.y};
//	(void)global_size;
//	kernel_gbx = cl_get_kernel_by_name(rt->cl, "gauss_blur_x");
//	clSetKernelArg(*kernel_gbx, 0, sizeof(cl_mem), &rt->gpu_mem->cl_image);
//	clSetKernelArg(*kernel_gbx, 1, sizeof(cl_mem), &rt->gpu_mem->cl_aux);
//	clSetKernelArg(*kernel_gbx, 2, sizeof(cl_int2), &rt->screen_size);
//	clEnqueueNDRangeKernel(*rt->cl->queue, *kernel_gbx, 2, NULL, arr,
//						   NULL, 0, NULL, NULL);
//
//	kernel_gby = cl_get_kernel_by_name(rt->cl, "gauss_blur_y");
//	clSetKernelArg(*kernel_gby, 0, sizeof(cl_mem), &rt->gpu_mem->cl_aux);
//	clSetKernelArg(*kernel_gby, 1, sizeof(cl_mem), &rt->gpu_mem->cl_image);
//	clSetKernelArg(*kernel_gby, 2, sizeof(cl_int2), &rt->screen_size);
//	clEnqueueNDRangeKernel(*rt->cl->queue, *kernel_gby, 2, NULL, arr,
//						   NULL, 0, NULL, NULL);
//}

static void	pp_process(t_rt_main *rt, int i)
{
	cl_kernel	*k;

	k = (cl_kernel *)vec_at(rt->pp, i);
	size_t arr[2] = {rt->screen_size.x, rt->screen_size.y};
	clSetKernelArg(*k, 0, sizeof(cl_mem),
		i % 2 ? &rt->gpu_mem->cl_aux : &rt->gpu_mem->cl_image);
	clSetKernelArg(*k, 1, sizeof(cl_mem),
				   i % 2 ? &rt->gpu_mem->cl_image : &rt->gpu_mem->cl_aux);
	clSetKernelArg(*k, 2, sizeof(cl_int2), &rt->screen_size);
	clEnqueueNDRangeKernel(*rt->cl->queue, *k, 2, NULL, arr,
						   NULL, 0, NULL, NULL);

//	kernel_gby = cl_get_kernel_by_name(rt->cl, "gauss_blur_y");
//	clSetKernelArg(*kernel_gby, 0, sizeof(cl_mem), &rt->gpu_mem->cl_aux);
//	clSetKernelArg(*kernel_gby, 1, sizeof(cl_mem), &rt->gpu_mem->cl_image);
//	clSetKernelArg(*kernel_gby, 2, sizeof(cl_int2), &rt->screen_size);
//	clEnqueueNDRangeKernel(*rt->cl->queue, *kernel_gby, 2, NULL, arr,
//						   NULL, 0, NULL, NULL);
}

void	post_processing(t_rt_main *rt)
{
	size_t	i;
	size_t	cur;

	if (!rt->pp)
		return;
	i = -1;
	cur = 0;
	while (++i < rt->pp->size)
	{
		pp_process(rt, i);
//		if (cur == 0)
//		{
//
//		}
	}
//	if (rt->params & RT_GAUSS_BLUR)
//	{
////		SDL_Log("ASD");
//		gauss_blur(rt, global_size);
//	}
}

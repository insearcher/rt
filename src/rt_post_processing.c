#include "rt.h"

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
	}
}

#include "rt_cl.h"

__kernel void	pp_blur_x(
		const __global int	*input_data,
		__global int		*output_data,
		int2				screen)
{
	int tx = get_global_id(0);
	int ty = get_global_id(1);
	int index = ty * screen.x + tx;

	float3	color;
	int		a = 3 * 2;
	float	sum = 0;
	int		coef;

	color = (float3) 0;
	for (int i = -a; i <= a; i++)
	{
		if (tx + i >= 0 && tx + i < screen.x)
		{
			coef = gauss_coeff_x(i, 2);
			color += int_color(input_data[screen.x * ty + (tx + i)]) * coef;
			sum += coef;
		}
	}
	output_data[index] = get_color(color / sum);
}

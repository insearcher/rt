#include "rt_cl.h"

__kernel void	pp_blur_y(
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
	for (int j = -a; j <= a; j++)
	{
		if (ty + j >= 0 && ty + j < screen.y)
		{
			coef = gauss_coeff_x(j, 2);
			color += int_color(input_data[screen.x * (ty + j) + tx]) * coef;
			sum += coef;
		}
	}
	output_data[index] = get_color(color / sum);
}

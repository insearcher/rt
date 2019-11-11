#include "rt_cl.h"

__kernel void	pp_anaglyph(
		const __global int	*input_data,
		__global int		*output_data,
		int2				screen)
{
	int tx = get_global_id(0);
	int ty = get_global_id(1);
	int index = ty * screen.x + tx;

	float3	l_color;
	float3	r_color;
	float3	anaglyph_color;
	int		sdvig = 8;

	if (tx < sdvig || tx > screen.x - sdvig - 1)
	{
		output_data[index] = 0;
		return ;
	}
	int i1 = ty * screen.x + (tx - sdvig);
	int i2 = ty * screen.x + (tx + sdvig);
	l_color = int_color(input_data[i1]);
	r_color = int_color(input_data[i2]);
	anaglyph_color.x = l_color.x;
	anaglyph_color.y = r_color.y;
	anaglyph_color.z = r_color.z;
	output_data[index] = get_color(anaglyph_color);
}

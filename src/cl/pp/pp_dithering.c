#include "rt_cl.h"

__kernel void	pp_dithering(
		const __global int	*input_data,
		__global int		*output_data,
		int2				screen)
{
	int tx = get_global_id(0);
	int ty = get_global_id(1);
	int index = ty * screen.x + tx;

	float16 bayer = {0, 8, 2, 10, 12, 4, 14, 6, 3, 11, 1, 9, 15, 7, 13, 5};
	bayer *= 0.0625f; // 1 / 16
	int col = (int)(bayer[((tx % 4) * 4 + ty % 4)] * 255);

	int red = (input_data[index] >> 16) & 0xFF;
	int green = (input_data[index] >> 8) & 0xFF;
	int blue = input_data[index] & 0xFF;

	red = col > red ? 0 : 255;
	green = col > green ? 0 : 255;
	blue = col > blue ? 0 : 255;

	output_data[index] = ((red << 16) | (green << 8) | blue);
}

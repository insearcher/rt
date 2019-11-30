#include "rt_cl.h"

__kernel void	pp_monochrome(
		const __global int	*input_data,
		__global int		*output_data,
		int2 				screen)
{
	int tx = get_global_id(0);
	int ty = get_global_id(1);
	int index = ty * screen.x + tx;

	int red = (input_data[index] >> 16) & 0xFF;
	int green = (input_data[index] >> 8) & 0xFF;
	int blue = input_data[index] & 0xFF;
	float3 v = (float3)(red, green, blue) / 255.0f;
	float3	c_linear;
	float	y_linear;

	c_linear.x = v.x > 0.04045f ? pow((v.x + 0.055f) / 1.055f, 2.4f) : v.x / 12.92f;
	c_linear.y = v.y > 0.04045f ? pow((v.y + 0.055f) / 1.055f, 2.4f) : v.y / 12.92f;
	c_linear.z = v.z > 0.04045f ? pow((v.z + 0.055f) / 1.055f, 2.4f) : v.z / 12.92f;

	y_linear = 0.2126f * c_linear.x + 0.7152f * c_linear.y + 0.0722f * c_linear.z;
	v.x = y_linear > 0.0031308f ? 1.055f * pow(y_linear, 1.f / 2.4f) - 0.055f  : 12.92f * y_linear;
	v.y = v.x;
	v.z = v.x;
	output_data[index] = get_color(v);
}

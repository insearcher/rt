#include "rt_cl.h"

float	gauss_coeff_x(int x, float sigma)
{
	return(1000.f / (sqrt(2 * M_PI_F) * sigma) * exp(-(float)(x * x) / (2 * sigma * sigma)));
}

float	reverse(int n)
{
	if (n != 0)
		return (1.0f / n);
	return (0);
}

float3	int_color(int col)
{
	float3	v;

	v.x = (float)((col >> 16) & 0xFF) / 255;
	v.y = (float)((col >> 8) & 0xFF) / 255;
	v.z = (float)((col) & 0xFF) / 255;
	return (v);
}

int		get_light(int start, int end, float percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int		get_color(float3 v)
{
	int     red;
	int     green;
	int     blue;
	int 	start;
	int		end;

	start = 0;
	end = 0xFFFFFF;
	red = get_light((start >> 16) & 0xFF, (end >> 16) & 0xFF, v.x);
	green = get_light((start >> 8) & 0xFF, (end >> 8) & 0xFF, v.y);
	blue = get_light(start & 0xFF, end & 0xFF, v.z);
	return ((red << 16) | (green << 8) | blue);
}

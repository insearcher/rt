#define	SIGMA		15

static int	get_light(int start, int end, float percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

static float3	int_color(int col)
{
	float3	v;

	v.x = (float)((col >> 16) & 0xFF) / 255;
	v.y = (float)((col >> 8) & 0xFF) / 255;
	v.z = (float)((col) & 0xFF) / 255;
	return (v);
}

static int		get_color(float3 v)
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

static float	gauss_coeff_x(int x, float sigma)
{
	return(1000.f / (sqrt(2 * M_PI_F) * sigma) * exp(-(float)(x * x) / (2 * sigma * sigma)));
}

__kernel void	gauss_blur_y(const __global int	*input_data,
					 __global int *output_data, int2 screen)
{
	int tx = get_global_id(0);
	int ty = get_global_id(1);
	int index = ty * screen.x + tx;

	float3	color;
	int		a = 3 * (int)SIGMA;
	float	sum = 0;
	int		coef;

	color = (float3) 0;
	for (int j = -a; j <= a; j++)
	{
		if (ty + j >= 0 && ty + j < screen.y)
		{
			coef = gauss_coeff_x(j, SIGMA);
			color += int_color(input_data[screen.x * (ty + j) + tx]) * coef;
			sum += coef;
		}
	}
	output_data[index] = get_color(color / sum);
}

__kernel void	gauss_blur_x(
		const __global int *input_data,
		__global int *output_data, int2 screen)
{
	int tx = get_global_id(0);
	int ty = get_global_id(1);
	int index = ty * screen.x + tx;

	float3	color;
	int		a = 3 * (int)SIGMA;
	float	sum = 0;
	int		coef;

	color = (float3) 0;
	for (int i = -a; i <= a; i++)
	{
		if (tx + i >= 0 && tx + i < screen.x)
		{
			coef = gauss_coeff_x(i, SIGMA);
			color += int_color(input_data[screen.x * ty + (tx + i)]) * coef;
			sum += coef;
		}
	}
	output_data[index] = get_color(color / sum);
}

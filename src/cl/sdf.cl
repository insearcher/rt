#include "config_cl.h"

static float ft_mod2(float a, float b)
{
	if (b == 0)
		b = 0.001;
	return (a - ((int)(a / b)) * b);
}

static float3 ft_mod(float3 a, float3 b)
{
	return ((float3){ft_mod2(a.x, b.x), ft_mod2(a.y, b.y), ft_mod2(a.z, b.z)});
}

//TODO try to make a restriction on repeat, or del rx/ry/rz
float3	repeatSDF(float3 pos, float3 c, float rx, float ry, float rz)
{
	(void)rx;
	(void)ry;
	(void)rz;
//	float3 in;
//	float3 dv = c + (float3){rx, ry, rz};
//	in = ft_mod(pos, dv);
//	in -= dv * 0.5f;
//	return (in);
	return (ft_mod(pos, c) - c * 0.5f);
}

static float	max_in_vec(float3 vec)
{
	return (fmax(vec.x, fmax(vec.y, vec.z)));
}

//static float	min_in_vec(float3 vec)
//{
//	return (fmin(vec.x, fmax(vec.y, vec.z)));
//}









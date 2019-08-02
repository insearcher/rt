#include "config_cl.h"

float3

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

float	sphereSDF(float3 posc, float radius)
{
	return (length(posc) - radius);
}

float	max_in_vec(float3 vec)
{
	return (fmax(vec.x, fmax(vec.y, vec.z)));
}

float	boxSDF(float3 posc, float radius)
{
	//TODO b - is outside figure.
	float3 b = (float3){0.5f, 0.5f, 0.5f};
	float3 di = fabs(posc) - b;
	float mc = max_in_vec(di);
	return (fmin(mc, length(fmax(di, 0.0f))));
}

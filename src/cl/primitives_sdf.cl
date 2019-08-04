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

float	sphereSDF(float3 posc, float radius)
{
//	float3 z = posc;
//	float dr = 1.0;
//	float r = 0.0;
//	for (int i = 0; i < 128 ; i++) {
//		r = length(z);
//		if (r > 4) break;
//
//		// convert to polar coordinates
//		float theta = acos(z.z/r);
//		float phi = atan(z.y / z.x);
//		dr =  pow( r, 2)*2*dr + 1.0;
//
//		// scale and rotate the point
//		float zr = pow( r,2);
//		theta = theta*2;
//		phi = phi*2;
//
//		// convert back to cartesian coordinates
//		z = zr*(float3){sin(theta)*cos(phi), sin(phi)*sin(theta), cos(theta)};
//		z+=posc;
//	}
//	return 0.5*log(r)*r/dr;
	return (length(posc) - radius);
}

static float	max_in_vec(float3 vec)
{
	return (fmax(vec.x, fmax(vec.y, vec.z)));
}

//static float	min_in_vec(float3 vec)
//{
//	return (fmin(vec.x, fmax(vec.y, vec.z)));
//}

float	boxSDF(float3 posc, float3 bounds)
{
	//TODO b - is outside figure.
	float3 b = bounds;
	float3 di = fabs(posc) - b;
	float mc = max_in_vec(di);
	return (fmin(mc, length(fmax(di, 0.0f))));
}

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
	return (ft_mod(pos, c) - c * 0.5f);
}

float	sdf_box(float3 pos, float3 bounds)
{
	float3 d = fabs(pos) - bounds;
	return length(fmax(d, float3(0))) + fmin(fmax(d.x, fmax(d.y, d.z)), 0);
}

float	sdf_cylinder(float3 pos, float3 c)
{
	return length(pos.xz - c.xy) - c.z;
}

float	sdf_round_box(float3 pos, float4 bounds)
{
	float3 d = fabs(pos) - bounds.xyz;
	return length(fmax(d, float3(0))) - bounds.w + fmin(fmax(d.x, fmax(d.y, d.z)), 0);
}

float	sdf_sphere(float3 pos, float radius)
{
	return (length(pos) - radius);
}

float	sdf_torus(float3 pos, float2 t)
{
	float2 q = float2(length(pos.xz) - t.x, pos.y);
	return length(q) - t.y;
}

#include "rt_cl.h"

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

float	sdf_sphere(float3 pos, float radius)
{
	return (length(pos) - radius);
}

float	sdf_box(float3 pos, float3 bounds)
{
	float3 d = fabs(pos) - bounds;
	return length(fmax(d, 0.f)) + fmin(fmax(d.x, fmax(d.y, d.z)), 0);
}

float	sdf_round_box(float3 pos, float3 bounds, float r)
{
	float3 d = fabs(pos) - bounds;
	return length(fmax(d, 0.f)) - r + fmin(fmax(d.x, fmax(d.y, d.z)), 0);
}

float	sdf_torus(float3 pos, float2 t)
{
	float2 q = (float2)(length(pos.xz) - t.x, pos.y);
	return length(q) - t.y;
}

float	sdf_capped_torus(float3 pos, float2 sc, float ra, float rb)
{
	pos.x = fabs(pos.x);
	float k = (sc.y * pos.x > sc.x * pos.y) ? dot(pos.xy, sc) : length(pos.xy);
	return sqrt(dot(pos, pos) + ra * ra - 2.0f * ra * k) - rb;
}

float	sdf_link(float3 pos, float le, float r1, float r2)
{
	float3 q = (float3)(pos.x, fmax(fabs(pos.y) - le, 0.0f), pos.z);
	return length((float2)(length(q.xy) - r1, q.z)) - r2;
}

float	sdf_cylinder(float3 pos, float3 c)
{
	return length(pos.xz - c.xy) - c.z;
}

float	sdf_cone(float3 pos, float2 c)
{
	float q = length(pos.xy);
	return dot(normalize(c), (float2)(q, pos.z));
}

float	sdf_plane(float3 pos, float3 n, float d)
{
	return dot(pos, n) + d;
}



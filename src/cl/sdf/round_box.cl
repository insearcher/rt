#include "config_cl.h"

float	sdf_round_box(float3 pos, float4 bounds)
{
	float3 d = fabs(pos) - bounds.xyz;
	return length(fmax(d, float3(0))) - bounds.w + fmin(fmax(d.x, fmax(d.y, d.z)), 0);
}

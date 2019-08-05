#include "config_cl.h"

float	sdf_torus(float3 pos, float2 t)
{
	float2 q = float2(length(pos.xz) - t.x, pos.y);
	return length(q) - t.y;
}

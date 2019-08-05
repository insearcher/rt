#include "config_cl.h"

float	sdf_box(float3 pos, float3 bounds)
{
	float3 d = fabs(pos) - bounds;
	return length(fmax(d, float3(0))) + fmin(fmax(d.x, fmax(d.y, d.z)), 0);
}

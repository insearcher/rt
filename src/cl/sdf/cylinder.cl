#include "config_cl.h"

float	sdf_cylinder(float3 pos, float3 c)
{
	return length(pos.xz - c.xy) - c.z;
}

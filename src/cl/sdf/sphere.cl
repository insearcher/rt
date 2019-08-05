#include "config_cl.h"

float	sdf_sphere(float3 pos, float radius)
{
	return (length(pos) - radius);
}

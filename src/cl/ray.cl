#include "rt_cl.h"

float3	screen_to_world(int2 coord, int2 screen, float fov)
{
	float3	k;

	coord.x -= screen.x / 2;
	coord.y -= screen.y / 2;
	k.z = sqrt((float)screen.x * screen.x + screen.y * screen.y) / 2.0f / tan(fov * 3.1416f / 180 / 2);
	float fovx = atan(screen.x / 2.0f / k.z);
	float fovy = atan(screen.y / 2.0f / k.z);
	float maxx = tan(fovx) * k.z;
	float maxy = tan(fovy) * k.z;
	k.x = coord.x * (maxx * 2.0f / screen.x);
	k.y = coord.y * (maxy * 2.0f / screen.y);
	return (k);
}

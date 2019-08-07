#include "config_cl.h"

//float3  get_cam_ray(int x, int y, int width, int height, float3 camera_pos, float3 camera_local_x, float3 camera_local_y, float3 camera_local_z, float camera_min_distance, float camera_max_distance, float fov, float3 *k)
//{
//	x -= width / 2;
//    y -= height / 2;
//
//    k->z = sqrt((float)width * width + height * height) / 2 / tan(fov * 3.1416f / 180 / 2);
//    float fovx = atan(width / 2.0f / k->z);
//	float fovy = atan(height / 2.0f / k->z);
//	float maxx = tan(fovx) * k->z;
//	float maxy = tan(fovy) * k->z;
//	k->x = x * (maxx * 2 / width);
//	k->y = y * (maxy * 2 / height);
//	return camera_local_z * k->z + camera_local_x * k->x + camera_local_y * k->y;
//}

float3	screen_to_world(int x, int y, int2 screen, float fov)
{
	float3	k;

	x -= screen.x / 2;
	y -= screen.y / 2;
	k.z = sqrt((float)screen.x * screen.x + screen.y * screen.y) / 2.0f / tan(fov * 3.1416f / 180 / 2);
	float fovx = atan(screen.x / 2.0f / k.z);
	float fovy = atan(screen.y / 2.0f / k.z);
	float maxx = tan(fovx) * k.z;
	float maxy = tan(fovy) * k.z;
	k.x = x * (maxx * 2.0f / screen.x);
	k.y = y * (maxy * 2.0f / screen.y);
	return (k);
}
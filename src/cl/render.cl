
#include "config_cl.h"

void        put_pixel(int x, int y, int color, __global char* img, int width, int height)
{
    int a;

    y = height - y;
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        a = x * 4 + y * width * 4;
        img[a] = RED(color);
        img[a + 1] = GREEN(color);
        img[a + 2] = BLUE(color);
        img[a + 3] = 0;
    }
}

__kernel void render(__global char* img, int width, int height, int objects_num,
		__global t_object* objects, float3 camera_pos, float3 camera_local_x, float3 camera_local_y, float3 camera_local_z, float camera_min_distance, float camera_max_distance, float fov, int quality)
{
	int			gid;
	t_scene1	scene;
	float3		color;
	float3		direction;

	gid = get_global_id(0);
	int x = gid % width;
	int y = gid / width;
	if (x % quality != 0 || y % quality != 0)
		return ;
	scene.objects_num = objects_num;
	scene.objects = objects;
	scene.min_distance = camera_min_distance;
	scene.max_distance = camera_max_distance;
	float mult;
	direction = get_cam_ray(gid % width, gid / width, width, height, camera_pos, camera_local_x, camera_local_y, camera_local_z, camera_min_distance, camera_max_distance, fov, &mult);
	color = ray_marching(camera_pos, direction, &scene, mult) * 255.0f;
//	put_pixel(gid % width, gid / width + 1, COLOR(color.x, color.y, color.z), img, width, height);
	for (int i = 0; i < quality; ++i)
	{
		for (int j = 0; j < quality; ++j)
		{
			put_pixel(x + i, y + j + 1, COLOR(color.x, color.y, color.z), img, width, height);
		}
	}
}

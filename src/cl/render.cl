#include "config_cl.h"

void        put_pixel(int x, int y, t_color color, __global char* img, int width, int height)
{
    int a;

    y = height - y;
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        a = x * 4 + y * width * 4;
        img[a] = color.b;
        img[a + 1] = color.g;
        img[a + 2] = color.r;
        img[a + 3] = 0;
    }
}

__kernel void render(__global char* img, int width, int height, int objects_num,
		__global t_object3d* objects, float3 camera_pos, float3 camera_local_x, float3 camera_local_y, float3 camera_local_z, float camera_min_distance, float camera_max_distance, float fov)
{
	int			gid;
	t_scene		scene;
	float3	color;
	float3	cam_ray;

	gid = get_global_id(0);
	scene.objects_num = objects_num;
	scene.objects = objects;
	scene.min_distance = camera_min_distance;
	scene.max_distance = camera_max_distance;
	cam_ray = get_cam_ray(gid % width, gid / width, width, height, camera_pos, camera_local_x, camera_local_y, camera_local_z, camera_min_distance, camera_max_distance, fov);
	color = ray_marching(camera_pos, cam_ray, &scene);
	put_pixel(gid % width, gid / width + 1, (t_color){color.x * 255, color.y * 255, color.z * 255}, img, width, height);
}

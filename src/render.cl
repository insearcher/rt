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
		t_camera camera, __global t_object3d* objects)
{
	int			gid;
	t_scene		scene;
	float3	color;
	float3	cam_ray;

	gid = get_global_id(0);
	scene.objects_num = objects_num;
	scene.objects = objects;
	scene.min_distance = camera.min_distance;
	scene.max_distance = camera.max_distance;
	cam_ray = get_cam_ray(gid % width, gid / width, camera, width, height);
	color = ray_marching(camera.pos, cam_ray, &scene);
	put_pixel(gid % width, gid / width + 1, (t_color){color.x * 255, color.y * 255, color.z * 255}, img, width, height);
}

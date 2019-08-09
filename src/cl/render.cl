#include "rt_cl.h"

void			put_pixel(int2 pixel, int color, __global char* img, int2 screen)
{
    int a;

    pixel.y = screen.y - pixel.y - 1;
    if (pixel.x >= 0 && pixel.x < screen.x && pixel.y >= 0 && pixel.y < screen.y)
    {
        a = pixel.x * 4 + pixel.y * screen.x * 4;
        img[a] = RED(color);
        img[a + 1] = GREEN(color);
        img[a + 2] = BLUE(color);
        img[a + 3] = 0;
    }
}

__kernel void	render(__global char *image, __global t_scene *scene, __global t_object *objects, __global t_light *lights)
{
	int		gid = get_global_id(0);

	int2	screen = scene->camera.screen;
	int2	pixel = (int2)(gid % screen.x, gid / screen.x);
	float3	color;

	scene->objects = objects;
	scene->lights = lights;

	if (pixel.x % scene->camera.quality || pixel.y % scene->camera.quality)
		return ;

	float3 k = screen_to_world(pixel, screen, scene->camera.fov);
	t_transform t = scene->camera.transform;
	float3 direction = normalize(t.right * k.x + t.up * k.y + t.forward * k.z);

	t_raycast_hit rh;
	if (raymarch(scene->camera.transform.pos, direction, scene, &rh))
	{
		color = rh.hit->material.color.xyz;
//		if (color.y * 255 - 0x8C > 0)
//			printf("%d %d\n", pixel.x, pixel.y);
		float3	diffuse = color * scene->ambient;
		for (size_t i = 0; i < scene->lights_count; ++i)
		{
			float3 interpoint = scene->camera.transform.pos + direction * rh.distance;
			float NoL, a, mult;
			float3 LDirectional;
			switch (scene->lights[i].type)
			{
				case directional:
					NoL = max(dot(rh.normal, normalize(interpoint - scene->lights[i].transform.pos)), 0.0f);
					a = scene->lights[i].params.directional.color.w;
					LDirectional = scene->lights[i].params.directional.color.xyz * a * NoL;
					diffuse += color * LDirectional;
					break;
				case point:
					a = length(interpoint - scene->lights[i].transform.pos);
					if (a < scene->lights[i].params.point.distance)
					{
						// -(dist / light.distance)^2 + 1
						mult = -pow(a / scene->lights[i].params.point.distance, 2) + 1;
						diffuse += color * scene->lights[i].params.point.color.xyz * scene->lights[i].params.point.color.w * mult;
					}
					break;
			}
		}
		color = pow(diffuse, float3(0.4545));
	}
	else
		color = min(1, max(0, (float3){0.6 - direction.y * 0.7, 0.36 - direction.y * 0.7, 0.3 - direction.y * 0.7}));
	color = color * 255;
//	put_pixel(gid % scene->camera.screen.x, gid / scene->camera.screen.x + 1, COLOR(color.x, color.y, color.z), image, scene->camera.screen.x, scene->camera.screen.y);
	for (int i = 0; i < (int)scene->camera.quality; ++i)
	{
		for (int j = 0; j < (int)scene->camera.quality; ++j)
		{
			put_pixel((int2)(pixel.x + i, pixel.y + j), COLOR(color.x, color.y, color.z), image, screen);
		}
	}
}

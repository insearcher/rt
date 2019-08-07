#include "config_cl.h"

void			put_pixel(int x, int y, int color, __global char* img, int width, int height)
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

__kernel void	render(__global char *image, __global t_scene *scene, __global t_object *objects, __global t_light *lights)
{
	int			gid;
	float3		color;

	scene->objects = objects;
	scene->lights = lights;

	gid = get_global_id(0);
	int x, y;
	x = gid % scene->camera.screen.x;
	y = gid / scene->camera.screen.x;
	if (x % scene->camera.quality || y % scene->camera.quality)
		return ;

	float3 k = screen_to_world(x, y, scene->camera.screen, scene->camera.fov);
	t_transform t = scene->camera.transform;
	float3 direction = normalize(t.right * k.x + t.up * k.y + t.forward * k.z);

	t_raycast_hit rh;
	if (raymarch(scene->camera.transform.pos, direction, scene, &rh))
	{
		color = rh.hit->material.color.xyz;
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
		color = (float3){0.6 - direction.y * 0.7, 0.36 - direction.y * 0.7, 0.3 - direction.y * 0.7};
	color = color * 255;
//	put_pixel(gid % scene->camera.screen.x, gid / scene->camera.screen.x + 1, COLOR(color.x, color.y, color.z), image, scene->camera.screen.x, scene->camera.screen.y);
	for (int i = 0; i < (int)scene->camera.quality; ++i)
	{
		for (int j = 0; j < (int)scene->camera.quality; ++j)
		{
			put_pixel(x + i, y + j + 1, COLOR(color.x, color.y, color.z), image, scene->camera.screen.x, scene->camera.screen.y);
		}
	}
}

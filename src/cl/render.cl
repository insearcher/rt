#include "rt_cl.h"

void			put_pixel(__global char *image, int2 pixel, int2 screen, float3 color)
{
    int a;

    pixel.y = screen.y - pixel.y - 1;
    if (pixel.x >= 0 && pixel.x < screen.x && pixel.y >= 0 && pixel.y < screen.y)
    {
        a = pixel.x * 4 + pixel.y * screen.x * 4;
        image[a] = color.x * 255;
        image[a + 1] = color.y * 255;
        image[a + 2] = color.z * 255;
        image[a + 3] = 0;
    }
}

void			fill_camera_pixel(__global char *image, int2 pixel, int2 screen, float3 color, int quality)
{
	int2 cur_pixel;

	for (int i = 0; i < quality; ++i)
	{
		for (int j = 0; j < quality; ++j)
		{
			cur_pixel = (int2)(pixel.x + i, pixel.y + j);
			put_pixel(image, cur_pixel, screen, color);
		}
	}
}

float3			get_skybox_color(float3 direction)
{
	return (min(1, max(0, (float3){0.6f - direction.y * 0.7f, 0.36f - direction.y * 0.7f, 0.3f - direction.y * 0.7f})));
}

__kernel void	render(__global char *image, __global t_scene *scene, __global t_object *objects, __global t_light *lights)
{
	int		gid = get_global_id(0);

	int2	screen = scene->camera.screen;
	int2	pixel = (int2)(gid % screen.x, gid / screen.x);

	if (pixel.x % scene->camera.quality || pixel.y % scene->camera.quality)
		return;

	scene->objects = objects;
	scene->lights = lights;

	t_camera cached_camera = scene->camera;

	float3 k = screen_to_world(pixel, screen, cached_camera.fov);

	t_transform t = cached_camera.transform;
	float3 direction = normalize(mad(t.right, k.x, mad(t.up, k.y, t.forward * k.z)));

	float3	color;
	t_raycast_hit rh;
	if (raymarch(cached_camera.transform.pos, direction, scene, &rh))
	{
		color = rh.hit->material.color.xyz;

		// TODO refactor
		// Light processing.
		float3 diffuse = color * scene->ambient;
		for (size_t i = 0; i < scene->lights_count; ++i)
		{
			float3 interpoint = mad(direction, rh.distance, cached_camera.transform.pos);
			float NoL, a, mult;
			float3 LDirectional;
			switch (scene->lights[i].type)
			{
				case directional:
					NoL = max(dot(rh.normal, normalize(interpoint - scene->lights[i].transform.pos)), 0.0f);
					a = scene->lights[i].params.directional.color.w;
					LDirectional = scene->lights[i].params.directional.color.xyz * a * NoL;
					diffuse = mad(color, LDirectional, diffuse);
					break;
				case point:
					a = length(interpoint - scene->lights[i].transform.pos);
					if (a < scene->lights[i].params.point.distance)
					{
						mult = -pow(a / scene->lights[i].params.point.distance, 2) + 1;
						diffuse += color * scene->lights[i].params.point.color.xyz * scene->lights[i].params.point.color.w * mult;
					}
					break;
			}
		}

		// Gamma correction.
		color = pow(diffuse, float3(0.4545f));
	}
	else
		color = get_skybox_color(direction);
	fill_camera_pixel(image, pixel, screen, color, cached_camera.quality);
}

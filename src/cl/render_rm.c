#include "rt_cl.h"

void			put_pixel(__global char *image, int2 pixel, int2 screen, float3 color)
{
    int a;

    pixel.y = screen.y - pixel.y - 1;
    if (pixel.x >= 0 && pixel.x < screen.x && pixel.y >= 0 && pixel.y < screen.y)
    {
        a = 4 * (pixel.y * screen.x + pixel.x);
        color *= 255;
        image[a] = color.x;
        image[a + 1] = color.y;
        image[a + 2] = color.z;
        image[a + 3] = 0;
    }
}

void			fill_camera_pixel_with_lowering_quality(__global char *image, int2 pixel, int2 screen,
		float3 color, int quality)
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
	return (min(1, max(0, (float3){
		mad(direction.y, -0.7f, 0.6f),
		mad(direction.y, -0.7f, 0.36f),
		mad(direction.y, -0.7f, 0.3f)
	})));
}

static float3	render_color(t_scene *scene, int2 pixel, int2 screen, __global int *texture)
{
	float3			ray_direction;
	t_raycast_hit	ray_hit;
	float3			color;

	get_ray_direction_and_clip_ratio(&ray_direction, &ray_hit.clip_ratio, pixel, screen,
									 scene->camera.fov, scene->camera.transform);
	if (!raymarch(scene->camera.transform.pos, ray_direction, 0, scene, &ray_hit))
	{
		color = get_skybox_color(ray_direction);
		return (color);
//		fill_camera_pixel(image, pixel, screen, color, scene->quality);
	}
	if (choose_texture_for_object(ray_hit, texture, &color))
		color = ray_hit.hit->material.color.xyz;
	color = get_lighting(scene, color, ray_hit);
	return (color);
}

static float	reverse(int n)
{
	if (n != 0)
		return (1.0f / n);
	return (0);
}

__kernel void	ray_march_render(__global char *image, t_scene scene, __global t_object *objects,
		__global t_light *lights, int2 screen, __global int *texture)
{
	int			gid;
	int2		pixel;
	float3		color;
	int			fsaa;
	float2		fsaa_pixel;

	gid = get_global_id(0);
	pixel = (int2)(gid % screen.x, gid / screen.x);
	scene.objects = objects;
	scene.lights = lights;
	if (scene.quality == 100)
	{
		color = render_color(&scene, pixel, screen, texture);
		put_pixel(image, pixel, screen, color);
	}
	else if (scene.quality < 100)
	{
		scene.quality = 31 - (int)(scene.quality / 3.3);
		if (pixel.x % scene.quality || pixel.y % scene.quality)
			return;
		color = render_color(&scene, pixel, screen, texture);
		fill_camera_pixel_with_lowering_quality(image, pixel, screen, color, scene.quality);
	}
	else
	{
//		fsaa = scene.quality - 30;
		for (int i = -fsaa / 2; i <= fsaa / 2; i++)
		{
			for (int j = -fsaa / 2; j <= fsaa / 2; j++)
			{
/*				fsaa_pixel.x = (float)pixel.x + i * reverse(fsaa) - 0.5;
				fsaa_pixel.y = (float)pixel.y + j * reverse(fsaa) - 0.5;
				color = render_color(&scene, fsaa_pixel, screen, texture);*/
			}
		}
//		color = color / ((fsaa + 1) * (fsaa + 1));
		put_pixel(image, pixel, screen, color);
	}
	//color = pow(color, 0.4545f);
}
/*for (int i = -fsaa / 2; i <= fsaa / 2; i++)
{
for (int j = -fsaa / 2; j <= fsaa / 2; j++)
color += render_color(&scene, pixel, screen, texture);
}*/

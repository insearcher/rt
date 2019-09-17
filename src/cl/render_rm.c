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
	return (min(1, max(0, (float3){
		mad(direction.y, -0.7f, 0.6f),
		mad(direction.y, -0.7f, 0.36f),
		mad(direction.y, -0.7f, 0.3f)
	})));
}

__kernel void	render(__global char *image, t_scene scene, __global t_object *objects,
		__global t_light *lights, int2 screen, __global int *texture)
{
	int			gid;
	int2		pixel;
	float3		color;
	float3		ray_direction;
	t_raycast_hit	ray_hit;

	gid = get_global_id(0);
	pixel = (int2)(gid % screen.x, gid / screen.x);
	if (scene.camera.quality != 1)
		if (pixel.x % scene.camera.quality || pixel.y % scene.camera.quality)
			return ;
	scene.objects = objects;
	scene.lights = lights;

	get_ray_direction_and_clip_ratio(&ray_direction, &ray_hit.clip_ratio, pixel, screen,
			scene.camera.fov, scene.camera.transform);

	if (!raymarch(scene.camera.transform.pos, ray_direction, 0, &scene, &ray_hit))
	{
		color = get_skybox_color(ray_direction);
		fill_camera_pixel(image, pixel, screen, color, scene.camera.quality);
		return ;
	}
	if (choose_texture_for_object(ray_hit, texture, &color))
		color = ray_hit.hit->material.color.xyz;

	color = get_lighting(&scene, color, ray_hit);
	//color = pow(color, 0.4545f);
	fill_camera_pixel(image, pixel, screen, color, scene.camera.quality);
}

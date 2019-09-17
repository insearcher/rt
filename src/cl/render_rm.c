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

__kernel void	render(__global char *image, t_scene scene, __global t_object *objects, __global t_light *lights, int2 screen, __global int *texture)
{
	int			gid;
	int2		pixel;

	gid = get_global_id(0);
	pixel = (int2)(gid % screen.x, gid / screen.x);
	if (pixel.x % scene.camera.quality || pixel.y % scene.camera.quality)
		return;

	scene.objects = objects;
	scene.lights = lights;

	float3 k = screen_to_world(pixel, screen, scene.camera.fov);

	t_transform t = scene.camera.transform;
	float3 direction = normalize(mad(scene.camera.transform.right, k.x, mad(t.up, k.y, t.forward * k.z)));

	float3	color;
	t_raycast_hit rh;
	rh.clip_ratio = length(k) / k.z;
	if (!raymarch(scene.camera.transform.pos, direction, 0, &scene, &rh))
	{
		color = get_skybox_color(direction);
		fill_camera_pixel(image, pixel, screen, color, scene.camera.quality);
		return;
	}
	if (choose_texture_for_object(rh, texture, &color))
		color = rh.hit->material.color.xyz;

	// TODO refactor
	// Light processing.
	float3 diffuse = color * scene.ambient;
	diffuse = clamp(diffuse, (float3){0, 0, 0}, (float3){1, 1, 1});
	for (uint i = 0; i < scene.lights_count; ++i)
	{
		t = scene.lights[i].transform;

		float NoL, a, mult;
		float3 LDirectional, dir, ndir;
		t_raycast_hit rhl;
		rhl.clip_ratio = length(k) / k.z;

		switch (scene.lights[i].type)
		{
			case directional:
				dir = -t.forward;
				ndir = normalize(dir);
				if (raymarch(rh.point + rh.normal * F_EPS, ndir, length(dir), &scene, &rhl))
					continue;

				NoL = max(dot(rh.normal, ndir), 0.0f);
				LDirectional = scene.lights[i].params.directional.color * NoL;
				diffuse += color * LDirectional;
				diffuse = clamp(diffuse, (float3){0, 0, 0}, (float3){1, 1, 1});
			case point:
				dir = t.pos - rh.point;
				ndir = normalize(dir);
				if (raymarch(rh.point + rh.normal * F_EPS, ndir, length(dir), &scene, &rhl))
					continue;

				a = length(dir);
				if (a < scene.lights[i].params.point.distance)
				{
					NoL = max(dot(rh.normal, ndir), 0.0f);
					mult = -pow(min(a / scene.lights[i].params.point.distance, 1.0f), 2) + 1.0f;
					diffuse += color * scene.lights[i].params.point.color * NoL * mult;
					diffuse = clamp(diffuse, (float3){0, 0, 0}, (float3){1, 1, 1});
				}
		}
	}

	// Gamma correction.
	//TODO COLOR IS BAD
	//if (diffuse.x > 255)
	//	diffuse.x = 255;
	//if (diffuse.y > 255)
	//	diffuse.y = 255;
	//if (diffuse.z > 255)
	//	diffuse.z = 255;
	//color = diffuse;
	//color = pow(diffuse, 0.4545f);
	color = diffuse;
	fill_camera_pixel(image, pixel, screen, color, scene.camera.quality);
}

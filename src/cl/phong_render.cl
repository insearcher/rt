#include "rt_cl.h"

static float	reverse(int n)
{
	if (n != 0)
		return (1.0f / n);
	return (0);
}
static void		put_pixel(//__global char *image, int2 pixel, int2 screen, float3 color, int count,
		// __global float3 *color_buf, int params)
{
	int a;
	int b;

	pixel.y = screen.y - pixel.y - 1;
	if (pixel.x >= 0 && pixel.x < screen.x && pixel.y >= 0 && pixel.y < screen.y)
	{
		color *= float3(255.f);
		b = pixel.y * screen.x + pixel.x;
		a = 4 * b;
		if (params & RT_PATH_TRACE)
		{
			if (count == 1)
			{
				color_buf[b] = float3(0.f);
			}
			else
			{
				color_buf[b] += color;
				color = color_buf[b] / (count - 1);
			}
		}
		image[a] = int(color.x);
		image[a + 1] = int(color.y);
		image[a + 2] = int(color.z);
		image[a + 3] = 0;
	}
}

static void		put_pixel_with_lowering_quality(//__global char *image, int2 pixel, int2 screen,
		// float3 color, int quality, int count, __global float3 *color_buf, int params)
{
	int2 cur_pixel;

	for (int i = 0; i < quality; ++i)
	{
		for (int j = 0; j < quality; ++j)
		{
			cur_pixel = (int2)(pixel.x + i, pixel.y + j);
			put_pixel(image, cur_pixel, screen, color, count, color_buf, params);
		}
	}
}

static float3	get_skybox_texture(float3 direction, __global int *texture, __global int *texture_w,
									__global int *texture_h, __global int *prev_texture_size)
{
	int coord;
	int coord_x;
	int coord_y;
	float tmp_division;
	float2 uv;
	float3 color;
	float3 vec;

	vec = normalize(direction);
	uv.x = 0.5f + (atan2(vec.z, vec.x) / TWO_PI);
	uv.y = 0.5f - (asin(vec.y) / PI);
	coord_x = int((uv.x) * texture_w[4]);
	coord_y = int((uv.y) * texture_h[4]);
	coord_y *= (texture_w[4]);
	coord = coord_x + coord_y;
	coord += prev_texture_size[4];

	color.x = (RED(texture[coord]));
	color.y = (GREEN(texture[coord]));
	color.z = (BLUE(texture[coord]));
	tmp_division = 0.00392156862; // 1/255
	color.x *= tmp_division;
	color.y *= tmp_division;
	color.z *= tmp_division;
	return (color);
}

static float3	get_skybox_color(float3 direction)
{

	return (min(1, max(0, (float3){
			mad(direction.y, -0.7f, 0.6f),
			mad(direction.y, -0.7f, 0.36f),
			mad(direction.y, -0.7f, 0.3f)
	})));
}

static float3	render_color_by_fong(//__global t_scene *scene, int2 pixel, int2 screen, __global int *texture,
//		__global int *texture_w, __global int *texture_h, __global int *prev_texture_size,
		float3 ray_direction)
{
	float3			color;
	t_raycast_hit	ray_hit;

	if (!raymarch(scene->camera.transform.pos, ray_direction, 0, scene, &ray_hit))
	{
//		color = get_skybox_color(ray_direction);
		color = get_skybox_texture(ray_direction, texture, texture_w, texture_h, prev_texture_size);
		return (color);
	}
	if(choose_texture_for_object(ray_hit, texture, &color, texture_w, texture_h, prev_texture_size))
		color = ray_hit.hit->material.color.xyz;
	color = get_lighting(scene, color, ray_hit);
	return (color);
}

static float3	get_pixel_color(//__global t_scene *scene, int2 pixel, int2 screen, int2 rands, __global int *texture,
//		__global int *texture_w, __global int *texture_h, __global int *prev_texture_size)
{
	int				fsaa = scene->fsaa;
	float3			ray_direction;
	float3			color = float3(0.f);
	unsigned int	seed0, seed1;
	t_camera		camera = scene->camera;


	get_cam_ray_direction(&ray_direction, pixel, screen,
						  camera.fov, camera.transform);

	#pragma unroll 9
	for (int i = -fsaa / 2; i <= fsaa / 2; i++)
	{
		for (int j = -fsaa / 2; j <= fsaa / 2; j++)
		{
			float3 ray_dir_aa = fast_normalize(ray_direction +
											   (float)j * reverse(fsaa) / screen.y * camera.transform.up +
											   (float)i * reverse(fsaa) / screen.x * camera.transform.right);
			color += render_color_by_fong(scene, pixel, screen, texture, texture_w,
										  texture_h, prev_texture_size, ray_dir_aa);
		}
	}
	color = color / (float)((fsaa + 1) * (fsaa + 1));
	return (color);
}

__kernel void	ray_march_render(//__global char *image, __global t_scene *scene,
//__global t_object *objects, int objects_count,
//		__global t_light *lights, int lights_count,
//		int2 screen, __global int *texture, __global int *texture_w,
//		__global int *texture_h, __global int *prev_texture_size,
//int path_trace_count, __global float3 *color_buf, int2 rands)
{
	int2			pixel;
	float3			color;

	pixel = (int2)(get_global_id(0), get_global_id(1));
	scene->objects = objects;
	scene->objects_count = objects_count;
	scene->lights = lights;
	scene->lights_count = lights_count;
	if (scene->quality == 100)
	{
		color = get_pixel_color(scene, pixel, screen, rands, texture, texture_w, texture_h, prev_texture_size);
		put_pixel(image, pixel, screen, color, path_trace_count, color_buf, scene->params);
	}
	else //quality processed in jtoc, therefore quality always <= 100
	{
		scene->quality = 31 - (int)(scene->quality / 3.3);
		if (pixel.x % scene->quality || pixel.y % scene->quality)
			return;
		color = get_pixel_color(scene, pixel, screen, rands, texture, texture_w, texture_h, prev_texture_size);
		put_pixel_with_lowering_quality(image, pixel, screen, color, scene->quality, path_trace_count, color_buf, scene->params);
	}
}

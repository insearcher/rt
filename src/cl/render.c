#include "rt_cl.h"

static void		put_pixel(__global char *image, int2 pixel, int2 screen, float3 color)
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

static void		put_pixel_with_lowering_quality(__global char *image, int2 pixel, int2 screen,
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

static float3	get_skybox_color(float3 direction)
{
	return (min(1, max(0, (float3){
			mad(direction.y, -0.7f, 0.6f),
			mad(direction.y, -0.7f, 0.36f),
			mad(direction.y, -0.7f, 0.3f)
	})));
}

static float get_random(unsigned int *seed0, unsigned int *seed1)
{
	/* hash the seeds using bitwise AND operations and bitshifts */
	*seed0 = 36969 * ((*seed0) & 65535) + ((*seed0) >> 16);
	*seed1 = 18000 * ((*seed1) & 65535) + ((*seed1) >> 16);

	unsigned int ires = ((*seed0) << 16) + (*seed1);

	/* use union struct to convert int to float */
	union {
		float f;
		unsigned int ui;
	} res;

	res.ui = (ires & 0x007fffff) | 0x40000000;  /* bitwise AND, bitwise OR */
	return (res.f - 2.0f) / 2.0f;
}

static float3 reflect(float3 i, float3 n)
{
	return (i - 2.0f * dot(i, n) * n);
}

static float3 refract(const float3 I, const float3 N, const float refractive_index)
{
	const float n = 1. / refractive_index;
	const float cosI = -(dot(N, I));
	const float sinT2 = n * n * (1.f - cosI * cosI);
	//if (sinT2 > 1.f)
	//	return N;
	const float cosT = sqrt(1.f - sinT2);
	return  (n * I + (n * cosI - cosT) * N);
}

static float3	render_color(__global t_scene *scene, int2 pixel, int2 screen, __global int *texture,
		__global int *texture_w, __global int *texture_h, __global int *prev_texture_size,
		float3 ray_direction)
{
	float3			color;
	t_raycast_hit	ray_hit;

	if (!raymarch(scene->camera.transform.pos, ray_direction, 0, scene, &ray_hit))
	{
		color = get_skybox_color(ray_direction);
		return (color);
	}
	if(choose_texture_for_object(ray_hit, texture, &color, texture_w, texture_h, prev_texture_size))
		color = ray_hit.hit->material.color.xyz;
	return (color);
}

static float3	render_color_by_fong(__global t_scene *scene, int2 pixel, int2 screen, __global int *texture,
							  __global int *texture_w, __global int *texture_h, __global int *prev_texture_size,
							  float3 ray_direction)
{
	float3			color;
	t_raycast_hit	ray_hit;

	if (!raymarch(scene->camera.transform.pos, ray_direction, 0, scene, &ray_hit))
	{
		color = get_skybox_color(ray_direction);
		return (color);
	}
	if(choose_texture_for_object(ray_hit, texture, &color, texture_w, texture_h, prev_texture_size))
		color = ray_hit.hit->material.color.xyz;
	color = get_lighting(scene, color, ray_hit);
	return (color);
}

static float3	render_color_by_path_trace(__global t_scene *scene, int2 pixel, int2 screen, __global int *texture,
					  __global int *texture_w, __global int *texture_h, __global int *prev_texture_size,
					  float3 ray_direction, unsigned int* seed0, unsigned int* seed1)
{
	t_raycast_hit	ray_hit;
	float3 path_color = (float3)(0.0f, 0.0f, 0.0f);
	float3 mask = (float3)(1.0f, 1.0f, 1.0f);
	float3 path_orig = scene->camera.transform.pos;
	int mirr = 0;

	for (int bounces = 0; bounces < 8; bounces++)
	{
		if (!raymarch(path_orig, ray_direction, 0, scene, &ray_hit))
		{
			path_color += mask * get_skybox_color(ray_direction);
			break;
		}
		float rand1 = get_random(seed0, seed1) * 2.0f * M_PI_F;
		float rand2 = get_random(seed1, seed0);
		float rand2s = half_sqrt(rand2);
		ray_hit.normal = dot(ray_hit.normal, ray_direction) < 0.0f ? ray_hit.normal : ray_hit.normal * (-1.0f);
		float3 w = ray_hit.normal;
		float3 axis = fabs(w.x) > 0.1f ? (float3)(0.0f, 1.0f, 0.0f) : (float3)(1.0f, 0.0f, 0.0f);
		float3 u = fast_normalize(cross(axis, w));
		float3 v = cross(w, u);
		float3 newdir = fast_normalize(u * half_cos(rand1) * rand2s + v * half_sin(rand1) * rand2s + w * half_sqrt(1.0f - rand2));
		//TODO PATH TRACE FLAG
		path_orig = ray_hit.point + ray_hit.normal * F_EPS; //TODO MUST WORK WITH - EPS instead ray_hit.clip_ratio

		float part = pow((8.f - bounces + mirr) / 8, 5);        // вклад следующего меньше, кроме зеркала и линзы
		path_color += mask * ray_hit.hit->material.luminosity * part;

		//TODO IN CL THERE ARE FAST_NORMALIZE AND FAST_LENGTH
		if (ray_hit.hit->transform.id == 2)							// ЗЕРКАЛО
		{
			mirr += 1;
			float	a = 1.0f;									// параметр. на сколько мутное стекло. диапазон 0.9f - 1.0f
			newdir = fast_normalize(a * fast_normalize(reflect(ray_direction, ray_hit.normal)) + (1.f - a) * newdir);
			path_orig += ray_hit.normal * F_EPS;
			float	cos_n = fabs(dot(ray_direction, ray_hit.normal));
			mask *= pow(cos_n, 0.01f);							// затемнеяет зеркало. чем больше угол между нормалью зеркала и dir и больше параметр, тем темнее
			mask *= 0.9f;										// затемняет зеркало
		}
		else if (ray_hit.hit->transform.id == 3)						// ЛИНЗА
		{
			newdir = fast_normalize(refract(ray_direction, ray_hit.normal, 1.05f));
			path_orig = ray_hit.point - ray_hit.normal * 0.001f;
			mirr += 1;
			float	cos_n = fabs(dot(ray_direction, ray_hit.normal));
			mask *= pow(cos_n, 0.3f);							// аналогично, как и у зеркала
			mask *= 0.9f;										// аналогично, как и у зеркала
		}
		else
			mask *= dot(newdir, ray_hit.normal);

		ray_direction = newdir;
		if(ray_hit.hit->transform.id != 3 && choose_texture_for_object(ray_hit, texture, &mask, texture_w, texture_h, prev_texture_size))
			mask *= (float3)(ray_hit.hit->material.color.xyz);
	}
	return (path_color);
}

static float	reverse(int n)
{
	if (n != 0)
		return (1.0f / n);
	return (0);
}

//TODO fsaa and N

static float3	get_pixel_color(__global t_scene *scene, int2 pixel, int2 screen, int2 rands, __global int *texture,
		__global int *texture_w, __global int *texture_h, __global int *prev_texture_size)
{
	int				fsaa = 0; //TODO IN JSON
	float3			ray_direction;
	float3			color = float3(0.f);
	unsigned int	seed0, seed1;
	t_camera		camera = scene->camera;

	get_cam_ray_direction(&ray_direction, pixel, screen,
			camera.fov, camera.transform);
	if (scene->params & RT_PATH_TRACE)
	{
		#pragma unroll
		for (int i = -fsaa / 2; i <= fsaa / 2; i++)
		{
			for (int j = -fsaa / 2; j <= fsaa / 2; j++)
			{
				float3 ray_dir_aa = fast_normalize(ray_direction +
						(float) j * reverse(fsaa) / screen.y * camera.transform.up +
						(float) i * reverse(fsaa) / screen.x * camera.transform.right);
				seed0 = pixel.x % screen.x + (rands.x * screen.x / 10);
				seed1 = pixel.y % screen.y + (rands.y * screen.y / 10);
				int N = 2; //TODO IN JSON
				for (int k = 0; k < N; k++)
				{
					get_random(&seed0, &seed1);
					get_random(&seed1, &seed0);
					color += render_color_by_path_trace(scene, pixel, screen, texture, texture_w, texture_h, prev_texture_size,
							ray_dir_aa, &seed0, &seed1) / N;
				}
			}
		}
	}
	else if (scene->params & RT_PHONG)
	{
		#pragma unroll
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
	}
	else
	{
		#pragma unroll
		for (int i = -fsaa / 2; i <= fsaa / 2; i++)
		{
			for (int j = -fsaa / 2; j <= fsaa / 2; j++)
			{
				float3 ray_dir_aa = fast_normalize(ray_direction +
						(float)j * reverse(fsaa) / screen.y * camera.transform.up +
						(float)i * reverse(fsaa) / screen.x * camera.transform.right);
				color += render_color(scene, pixel, screen, texture, texture_w,
						texture_h, prev_texture_size, ray_dir_aa);
			}
		}
	}
	color = color / (float)((fsaa + 1) * (fsaa + 1));
//	color = pow(color, 0.4545f);
	return (color);
}

__kernel void	ray_march_render(__global char *image, __global t_scene *scene,
		__global t_object *objects, int objects_count,
		__global t_light *lights, int lights_count,
		int2 screen, __global int *texture, __global int *texture_w,
		__global int *texture_h, __global int *prev_texture_size, int2 rands)
{
	int				gid;
	int2			pixel;
	float3			color;

	gid = get_global_id(0);
	pixel = (int2)(gid % screen.x, gid / screen.x);
	scene->objects = objects;
	scene->objects_count = objects_count;
	scene->lights = lights;
	scene->lights_count = lights_count;
	if (scene->quality == 100)
	{
		color = get_pixel_color(scene, pixel, screen, rands, texture, texture_w, texture_h, prev_texture_size);
		put_pixel(image, pixel, screen, color);
	}
	else //quality processed in jtoc, therefore quality always <= 100
	{
		scene->quality = 31 - (int)(scene->quality / 3.3);
		if (pixel.x % scene->quality || pixel.y % scene->quality)
			return;
		color = get_pixel_color(scene, pixel, screen, rands, texture, texture_w, texture_h, prev_texture_size);
		put_pixel_with_lowering_quality(image, pixel, screen, color, scene->quality);
	}
}

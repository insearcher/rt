__kernel void	ray_trace_render(__global int *data, t_scene scene, const __global t_object *objects,
		const __global t_light *lights, int2 screen, const __global int *texture)
{
/*	int			tx = get_global_id(0);
	int			ty = get_global_id(1);
	float3		rat_direction;
	float3		color;
	int			fsaa = screen->fsaa_n;

	color = (float3) 0;
	for (int i = -fsaa / 2; i <= fsaa / 2; i++)
	{
		for (int j = -fsaa / 2; j <= fsaa / 2; j++)
		{
			dir = (*screen).v1 * ((float) (tx + i * reverse(fsaa)) / WIDTH - 0.5f) - (*screen).v2 * ((float)(ty + j * reverse(fsaa)) / WIDTH - 0.5f);
			dir = dir - (*screen).center;
			dir = fast_normalize(dir);

			t_lighting	lighting;
			lighting.n = (float3) 0;
			lighting.hit = (float3) 0;

		if (scene_intersect(camera.transorm.pos, dir, obj, &lighting, counter->all_obj))
			color += light_shadow(dir, obj, l, &lighting, counter);
		else
			color += (float3)(1);
		}
	}

	color = color / ((fsaa + 1) * (fsaa + 1));

	data[ty * screen.x + tx] = get_color(color, screen->effects);*/
}

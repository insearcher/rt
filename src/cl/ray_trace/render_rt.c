__kernel void	render_rt(__global int *data, __global t_scene *scene,
		const __global t_cam *cam,
		const __global t_screen *screen, const __global t_counter *counter,
		const __global t_light *l, const __global t_object *obj)
{
	int			tx = get_global_id(0);
	int			ty = get_global_id(1);
	int			index = ty * WIDTH + tx;
	t_camera	*camera;
	float3		dir;
	float3		color;
	int			fsaa = screen->fsaa_n;

	camera = scene->camera;
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

	data[index] = get_color(color, screen->effects);
}

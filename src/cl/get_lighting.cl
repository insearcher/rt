float3	get_lighting(__global t_scene *scene, float3 color, t_raycast_hit ray_hit)
{
	float3			diffuse;
	t_transform		tmp_transform;
	t_raycast_hit	ray_hit_light;

	diffuse = color * scene->ambient;
	diffuse = clamp(diffuse, (float3){0, 0, 0}, (float3){1, 1, 1});
	for (uint i = 0; i < scene->lights_count; ++i)
	{
		tmp_transform = scene->lights[i].transform;

		float NoL, a, mult;
		float3 LDirectional, dir, ndir;

		switch (scene->lights[i].type)
		{
			case directional:
				dir = -tmp_transform.forward;
				ndir = normalize(dir);
				if (raymarch(ray_hit.point + ray_hit.normal * F_EPS, ndir, length(dir), scene, &ray_hit_light))
					continue;

				NoL = max(dot(ray_hit.normal, ndir), 0.0f);
				LDirectional = scene->lights[i].params.directional.color * NoL;
				diffuse += color * LDirectional;
				diffuse = clamp(diffuse, (float3){0, 0, 0}, (float3){1, 1, 1});
			case point:
				dir = tmp_transform.pos - ray_hit.point;
				ndir = normalize(dir);
				if (raymarch(ray_hit.point + ray_hit.normal * F_EPS, ndir, length(dir), scene, &ray_hit_light))
					continue;

				a = length(dir);
				if (a < scene->lights[i].params.point.distance)
				{
					NoL = fmax(dot(ray_hit.normal, ndir), 0.0f);
					mult = -powf(min(a / scene->lights[i].params.point.distance, 1.0f), 2) + 1.0f;
					diffuse += color * scene->lights[i].params.point.color * NoL * mult;
					diffuse = clamp(diffuse, (float3){0, 0, 0}, (float3){1, 1, 1});
				}
		}
	}
	return (diffuse);
}

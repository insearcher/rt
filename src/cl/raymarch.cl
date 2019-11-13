#include "rt_cl.h"

static inline float		opsubtraction(float d1, float d2)
{
	return (max(-d1, d2));
}

static inline float		opunion( float d1, float d2)
{
	return (min(d1, d2));
}

static float	sceneSDF(float3 origin, float3 direction, __global t_scene *scene, t_raycast_hit *rh)
{
	float		dist_to_obj = 1000000.f;
	float		tmp_dist_to_obj;
	bool		cond;
	float3		lp;

	for (uint i = 0; i < scene->objects_count; i++)
	{
		if (scene->objects[i].sub_mult_flag == 0)
		{
			tmp_dist_to_obj = sdf(origin, direction, &scene->objects[i], &lp, scene->params);
			cond = tmp_dist_to_obj < dist_to_obj && tmp_dist_to_obj > -F_EPS;
			if (cond)
			{
				dist_to_obj = tmp_dist_to_obj;
				rh->hit = &scene->objects[i];
				rh->local_point = lp;
			}
		}
		else if (scene->objects[i].sub_mult_flag == 1)
		{
			tmp_dist_to_obj = opsubtraction(sdf(origin, direction, &scene->objects[scene->objects[i].obj_with_oper_id], &lp, scene->params),
											sdf(origin, direction, &scene->objects[i], &lp, scene->params));
			cond = tmp_dist_to_obj < dist_to_obj && tmp_dist_to_obj > -F_EPS;
			if (cond)
			{
				dist_to_obj = tmp_dist_to_obj;
				rh->hit = &scene->objects[i];
				rh->local_point = lp;
			}
		}
		else if (scene->objects[i].sub_mult_flag == 2)
		{
			tmp_dist_to_obj = opunion(sdf(origin, direction, &scene->objects[scene->objects[i].obj_with_oper_id], &lp, scene->params),
									  sdf(origin, direction, &scene->objects[i], &lp, scene->params));
			cond = tmp_dist_to_obj < dist_to_obj && tmp_dist_to_obj > -F_EPS;
			if (cond)
			{
				dist_to_obj = tmp_dist_to_obj;
				rh->hit = &scene->objects[i];
				rh->local_point = lp;
			}
		}
		else if (scene->objects[i].sub_mult_flag == 3)
			continue ;
	}
	return (dist_to_obj);
}

static void	get_normal_for_sub_mult_obj(float3 pos, float3 direction, float basic_dist, __global t_scene *scene, t_raycast_hit *rh, int params)
{
	if (rh->hit->sub_mult_flag == 1)
	{
		rh->normal = normalize((float3) {opsubtraction(sdf((float3) {pos.x + F_EPS, pos.y, pos
				.z}, direction, &scene->objects[rh->hit->obj_with_oper_id], 0, params), sdf((float3) {pos.x + F_EPS, pos.y, pos
				.z}, direction, rh->hit, 0, params)),
										 opsubtraction(sdf((float3) {pos.x, pos.y + F_EPS,
																	 pos.z},
														   direction, &scene->objects[rh->hit->obj_with_oper_id], 0, params),
													   sdf((float3) {pos.x, pos.y + F_EPS,
																	 pos.z},
														   direction, rh->hit, 0, params)),
										 opsubtraction(sdf((float3) {pos.x, pos.y,
																	 pos.z + F_EPS},
														   direction, &scene->objects[rh->hit->obj_with_oper_id], 0, params),
													   sdf((float3) {pos.x, pos.y,
																	 pos.z + F_EPS},
														   direction, rh->hit, 0, params))} -
							   (float3) {basic_dist, basic_dist, basic_dist});
	}
	else if (rh->hit->sub_mult_flag == 2)
	{
		rh->normal = normalize((float3) {opunion(sdf((float3) {pos.x + F_EPS, pos.y, pos
				.z}, direction, &scene->objects[rh->hit->obj_with_oper_id], 0, params), sdf((float3) {pos.x + F_EPS, pos.y, pos
				.z}, direction, rh->hit, 0, params)),
										 opunion(sdf((float3) {pos.x, pos.y + F_EPS,
															   pos.z},
													 direction, &scene->objects[rh->hit->obj_with_oper_id], 0, params),
												 sdf((float3) {pos.x, pos.y + F_EPS,
															   pos.z},
													 direction, rh->hit, 0, params)),
										 opunion(sdf((float3) {pos.x, pos.y,
															   pos.z + F_EPS},
													 direction, &scene->objects[rh->hit->obj_with_oper_id], 0, params),
												 sdf((float3) {pos.x, pos.y,
															   pos.z + F_EPS},
													 direction, rh->hit, 0, params))} -
							   (float3) {basic_dist, basic_dist, basic_dist});
	}
}

static void	get_normal(float3 pos, float3 direction, float basic_dist,
						  t_raycast_hit *rh, int params)
{
	rh->normal = normalize((float3){sdf((float3){pos.x + F_EPS, pos.y, pos
			.z}, direction, rh->hit, 0, params),
									sdf((float3){pos.x, pos.y + F_EPS, pos.z},
										direction, rh->hit, 0, params),
									sdf((float3){pos.x, pos.y, pos.z + F_EPS},
										direction, rh->hit, 0, params)} -
						   (float3){basic_dist, basic_dist, basic_dist});
}

int			raymarch(float3 origin, float3 direction, float distance, __global t_scene *scene, t_raycast_hit *rh)
{
	float	intersect_dist = F_EPS;
	float	dist_to_obj;
	int		max_steps = 500;
	float3	cur_ray_point;
	bool	cond;

	distance = select(distance, MAXFLOAT, distance < F_EPS);

#pragma unroll 16
	for (int i = 0; i < max_steps; i++)
	{
		cur_ray_point = mad(direction, intersect_dist, origin);
		dist_to_obj = sceneSDF(cur_ray_point, direction, scene, rh);
		if (dist_to_obj < -F_EPS)
		{
			rh->point = cur_ray_point;
			rh->distance = intersect_dist;
			return (1);
		}
		if (dist_to_obj < F_EPS)
		{
			rh->point = cur_ray_point;
			rh->distance = intersect_dist;
			if (rh->hit->sub_mult_flag == 0)
				get_normal(cur_ray_point, direction, dist_to_obj, rh, scene->params);
			else if (rh->hit->sub_mult_flag >= 1 && rh->hit->sub_mult_flag < 3)
				get_normal_for_sub_mult_obj(cur_ray_point, direction, dist_to_obj, scene, rh, scene->params);
			else
				continue ;
			return (1);
		}
		intersect_dist += dist_to_obj;
		cond = intersect_dist > scene->camera.clipping_planes.far || intersect_dist > distance;
		if (cond)
			return (0);
	}
	return (0);
}

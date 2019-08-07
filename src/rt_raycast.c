/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 17:50:06 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/23 17:50:07 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_raycast.h"

static void getk(cl_int2 s, cl_float2 c, cl_float3 *k, float fov)
{
	k->z = sqrt((float)s.x * s.x + s.y * s.y) / 2 / tan(fov * 3.1416f / 180 / 2);
	float fovx = atan(s.x / 2.0f / k->z);
	float fovy = atan(s.y / 2.0f / k->z);
	float maxx = tan(fovx) * k->z;
	float maxy = tan(fovy) * k->z;
	k->x = c.x * (maxx * 2 / s.x);
	k->y = c.y * (maxy * 2 / s.y);
}

t_raycast_hit	*rt_raycast(t_scene *scene, int x, int y)
{
	cl_float3	k;

	getk(scene->camera.screen, (cl_float2){{x, y}}, &k, scene->camera.fov);
	t_transform *t = &scene->camera.transform;
	cl_float3 origin;
	origin.v4 = t->pos.v4 + t->forward.v4 * k.z + t->right.v4 * k.x + t->up.v4 * k.y;
	return (NULL);
}
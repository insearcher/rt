#include "rt_cl.h"

void	get_ray_direction_and_clip_ratio(float3 *ray_direction, float *clip_ratio, int2 coord, int2 screen, float fov, t_transform transform)
{
	float3	local_cam_ray;

	coord.x -= screen.x / 2;
	coord.y -= screen.y / 2;
	local_cam_ray.z = half_sqrt((float)screen.x * screen.x + screen.y * screen.y)
			/ 2.0f / half_tan(fov * 0.00872663f); // was early 3.1416f / 180.f / 2.f
	float fovx = atan(screen.x / 2.0f / local_cam_ray.z);
	float fovy = atan(screen.y / 2.0f / local_cam_ray.z);
	float maxx = half_tan(fovx) * local_cam_ray.z;
	float maxy = half_tan(fovy) * local_cam_ray.z;
	local_cam_ray.x = coord.x * (maxx * 2.0f / screen.x);
	local_cam_ray.y = coord.y * (maxy * 2.0f / screen.y);

	*ray_direction = fast_normalize(mad(transform.right, local_cam_ray.x,
			mad(transform.up, local_cam_ray.y, transform.forward * local_cam_ray.z)));

	*clip_ratio = fast_length(local_cam_ray) / local_cam_ray.z;
}

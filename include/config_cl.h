#ifndef CONFIG_CL_H
# define CONFIG_CL_H

# define CL_SILENCE_DEPRECATION

# include "rt.h"
# include "color.h"

typedef struct	__cl_rm_info
{
	t_object	hit;
	float3		normal;
	float3		point;
	float		distance;
}				cl_rm_info;

float3	get_cam_ray(int x, int y, int width, int height, float3 camera_pos, float3 camera_local_x, float3 camera_local_y, float3 camera_local_z, float camera_min_distance, float camera_max_distance, float fov, float *mult);
void		put_pixel(int x, int y, int color, __global char* img, int width, int height);
float3	ray_marching(float3 origin, float3 direction, t_scene *scene, float mult, float3 *normal, float *intersect_dist, t_object *intersected);
float3 repeatSDF(float3 pos, float3 cen, float rx, float ry, float rz);
float sphereSDF(float3 posc, float radius);

float	sdf_sphere(float3 pos, float radius);
float	sdf_box(float3 pos, float3 bounds);
float	sdf_round_box(float3 pos, float4 bounds);
float	sdf_torus(float3 pos, float2 t);
float	sdf_cylinder(float3 pos, float3 c);

char	raymarch(float3 origin, float3 direction, t_scene *scene, cl_rm_info *rm_info, float mult);

#endif

#ifndef CONFIG_CL_H
# define CONFIG_CL_H

# define CL_SILENCE_DEPRECATION

# define F_EPS	0.001f

# include "rt.h"
# include "raycast_hit.h"
# include "color.h"

void  get_cam_ray(int x, int y, int width, int height, float fov, float3 *k);
void		put_pixel(int2 pixel, int color, __global char* img, int2 screen);
float3	ray_marching(float3 origin, float3 direction, t_scene *scene, float mult, float3 *normal, float *intersect_dist, t_object *intersected);
float3 repeatSDF(float3 pos, float3 cen, float rx, float ry, float rz);
float sphereSDF(float3 posc, float radius);

float	sdf_sphere(float3 pos, float radius);
float	sdf_box(float3 pos, float3 bounds);
float	sdf_round_box(float3 pos, float4 bounds);
float	sdf_torus(float3 pos, float2 t);
float	sdf_cylinder(float3 pos, float3 c);

float3	screen_to_world(int2 coord, int2 screen, float fov);
char	raymarch(float3 origin, float3 direction, __global t_scene *scene, t_raycast_hit *rh);

#endif

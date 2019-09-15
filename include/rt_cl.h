#ifndef CONFIG_CL_H
# define CONFIG_CL_H

# define CL_SILENCE_DEPRECATION

# define F_EPS	0.001f
# define PI		3.14159265f
# include "rt.h"
# include "color.h"

//void  get_cam_ray(int x, int y, int width, int height, float fov, float3 *k);
//float3	ray_marching(float3 origin, float3 direction, t_scene *scene, float mult, float3 *normal, float *intersect_dist, t_object *intersected);

float	sdf_sphere(float3 pos, float radius);
float	sdf_box(float3 pos, float3 bounds);
float	sdf_round_box(float3 pos, float3 bounds, float r);
float	sdf_torus(float3 pos, float radius, float inner_radius);
float	sdf_capped_torus(float3 pos, float2 sc, float ra, float rb);
float	sdf_link(float3 pos, float le, float r1, float r2);
float	sdf_cylinder(float3 pos, float3 c);
float	sdf_cone(float3 pos, float2 c);
float	sdf_plane(float3 pos, float3 n, float d);

void	put_pixel(__global char *image, int2 pixel, int2 screen, float3 color);
void	fill_camera_pixel(__global char *image, int2 pixel, int2 screen, float3 color, int quality);
float2	uv_mapping_for_sphere(t_raycast_hit rh);

float3	screen_to_world(int2 coord, int2 screen, float fov);

float3	get_skybox_color(float3 direction);

float3 repeatSDF(float3 pos, float3 cen, float rx, float ry, float rz);
float sphereSDF(float3 posc, float radius);


char	raymarch(float3 origin, float3 direction, float distance, __global t_scene *scene, t_raycast_hit *rh);

#endif

#ifndef CONFIG_CL_H
# define CONFIG_CL_H

# define CL_SILENCE_DEPRECATION

# define F_EPS	0.001f
# define PI		3.14159265f
# define TWO_PI	6.28318530f
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
float	sdf_mandelbulb(float3 pos, float power, int iter, int breakout);
float	sdf_mandelbox(float3 pos, float scale, float fixedradius,
					   float minradius, float3 cube_size, int iter);
float 	sdf_octahedron(float3 pos, float s);
float	sdf_menger_sponge(float3 pos, float3 offset, float scale, int iteration);
float	sdf_cross_box(float3 pos, float3 b);

float3	repeatSDF(float3 pos, float3 cen, float rx, float ry, float rz);

void	normalize_coord_for_texture(t_raycast_hit rh, float2 uv, float3 *color,
			__global int *texture, __global int *texture_w, __global int *texture_h,
			__global int *prev_texture_size);
int		choose_texture_for_object(t_raycast_hit rh, __global int *texture,
			float3 *color, __global int *texture_w, __global int *texture_h,
			__global int *prev_texture_size);
float2	uv_mapping_for_sphere(t_raycast_hit rh);
float2	uv_mapping_for_cylinder(t_raycast_hit rh);
float2	uv_mapping_for_plane(t_raycast_hit rh);
float2	uv_mapping_for_torus(t_raycast_hit rh);
float2	uv_mapping_for_cube(t_raycast_hit rh);

int		raymarch(float3 origin, float3 direction, float distance, __global t_scene *scene, t_raycast_hit *rh);
void	get_cam_ray_direction(float3 *ray_direction, int2 coord, int2 screen, float fov, t_transform transform);
float3	get_lighting(__global t_scene *scene, float3 color, t_raycast_hit ray_hit);

#endif

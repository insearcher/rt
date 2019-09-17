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

void	put_pixel(__global char *image, int2 pixel, int2 screen, float3 color);
void	fill_camera_pixel_with_lowering_quality(__global char *image, int2 pixel, int2 screen,
		float3 color, int quality);

float3	get_skybox_color(float3 direction);

float3	repeatSDF(float3 pos, float3 cen, float rx, float ry, float rz);
float	sphereSDF(float3 posc, float radius);

void	normalize_coord_for_texture(float2 uv, float3 *color,  __global int *texture);
int		choose_texture_for_object(t_raycast_hit rh,  __global int *texture, float3 *color);
float2	uv_mapping_for_sphere(t_raycast_hit rh);
float2	uv_mapping_for_cylinder(t_raycast_hit rh);
float2	uv_mapping_for_plane(t_raycast_hit rh);
float2	uv_mapping_for_torus(t_raycast_hit rh);
float2	uv_mapping_for_cube(t_raycast_hit rh);

char	raymarch(float3 origin, float3 direction, float distance, t_scene *scene, t_raycast_hit *rh);
void	get_ray_direction_and_clip_ratio(float3 *ray_direction, float *clip_ratio, int2 coord, int2 screen, float fov, t_transform transform);
float3	get_lighting(t_scene *scene, float3 color, t_raycast_hit ray_hit);

#endif

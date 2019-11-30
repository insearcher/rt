#ifndef CONFIG_CL_H
# define CONFIG_CL_H

# define CL_SILENCE_DEPRECATION

# define F_EPS	0.001f
# define PI		3.14159265f
# define TWO_PI	6.28318530f
# include "rt.h"

# define COLOR(r, g, b)	((((int)r & 0xFF) << 16) | (((int)g & 0xFF) << 8) | ((int)b & 0xFF))

# define RED(c)			(((int)c >> 16) & 0xFF)
# define GREEN(c)		(((int)c >> 8) & 0xFF)
# define BLUE(c)		((int)c & 0xFF)

float	sdf(float3 origin, float3 direction, __global t_object *obj, float3 *lp, int scene_params);

void	normalize_coord_for_texture(t_raycast_hit rh, float2 uv, float3 *color,
			__global int *texture, __global int *texture_w, __global int *texture_h,
			__global int *prev_texture_size);
int		choose_texture_for_object(t_raycast_hit rh, __global int *texture,
			float3 *color, __global int *texture_w, __global int *texture_h,
			__global int *prev_texture_size);

int		raymarch(float3 origin, float3 direction, float distance, __global t_scene *scene, t_raycast_hit *rh);
void	get_cam_ray_direction(float3 *ray_direction, int2 coord, int2 screen, float fov, t_transform transform);
float3	get_lighting(__global t_scene *scene, float3 color, t_raycast_hit ray_hit);

float	gauss_coeff_x(int x, float sigma);
float3	int_color(int col);
int		get_light(int start, int end, float percentage);
int		get_color(float3 v);

#endif

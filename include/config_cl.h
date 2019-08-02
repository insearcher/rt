#ifndef CONFIG_CL_H
# define CONFIG_CL_H

# define CL_SILENCE_DEPRECATION

# include "../include/math_vec.h"
# include "utilits.h"
# include "rt.h"

typedef struct	s_scene
{
	int						objects_num;
	float					min_distance;
	float					max_distance;
	__global t_object3d*	objects;
}				t_scene;

float3	get_cam_ray(int x, int y, int width, int height, float3 camera_pos, float3 camera_local_x, float3 camera_local_y, float3 camera_local_z, float camera_min_distance, float camera_max_distance);
void		put_pixel(int x, int y, t_color color, __global char* img, int width, int height);
float3	ray_marching(float3 start_ray, float3 dir_ray, t_scene *scene);
float3 repeatSDF(float3 pos, float3 cen, float rx, float ry, float rz);
float sphereSDF(float3 posc, float radius);
float boxSDF(float3 posc, float radius);
#endif

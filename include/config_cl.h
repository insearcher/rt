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

t_vector3d	get_cam_ray(int x, int y, t_camera camera, int width, int height);
void		put_pixel(int x, int y, t_color color, __global char* img, int width, int height);
t_vector3d	ray_marching(t_vector3d start_ray, t_vector3d dir_ray, t_scene *scene);

#endif

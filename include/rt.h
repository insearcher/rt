#ifndef RT_H
# define RT_H

#include "math_vec.h"

typedef struct			s_object3d
{
	int					type;
	t_vector3d			center;
	float				radius;
}						t_object3d;

typedef struct          s_camera
{
	/// Rendering
	float 				aspect_ratio;
	float				min_distance;
	float				max_distance;
	/// Physics
	float				acc_time;
	float				speed;
	t_vector3d			pos;
	t_vector3d			local_x;
	t_vector3d			local_y;
	t_vector3d			local_z;
	t_vector3d			velocity;
}						t_camera;

/*typedef struct			s_camera
{
	float
};*/

#endif

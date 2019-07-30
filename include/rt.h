#ifndef RT_H
# define RT_H

# include "math_vec.h"
# ifndef OPENCL___
# include <OpenCL/opencl.h>
# endif

typedef struct			s_object3d
{
	int					type;
# ifndef OPENCL___

	cl_float3			center;
# else

	float3			center;

# endif
	float				radius;
}						t_object3d;

typedef struct          s_camera
{
	/// Rendering
	float 				aspect_ratio;
	float				min_distance;
	float				max_distance;
	/// Physics
	float				pos_acc;
	float				speed;
	float				rot_speed;
	float				rot_acc;

# ifndef OPENCL___

	cl_float3			pos;
	cl_float3			velocity;
	cl_float3			rot_velocity;
	cl_float3			local_x;
	cl_float3			local_y;
	cl_float3			local_z;

# else

	float3			pos;
	float3			velocity;
	float3			rot_velocity;
	float3			local_x;
	float3			local_y;
	float3			local_z;

# endif

	/// Temp
	int					mx;
	int					my;
}						t_camera;

#endif

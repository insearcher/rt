#ifndef RT_H
# define RT_H

# include "math_vec.h"
# ifndef OPENCL___
# include <OpenCL/opencl.h>
# endif

typedef struct			s_object3d
{
# ifndef OPENCL___

	cl_int					type;
	cl_float3			center;
	cl_float				radius;
# else

	int					type;
	float3			center;
	float				radius;

# endif
}						t_object3d;

typedef struct          s_camera
{

# ifndef OPENCL___

	/// Rendering
	cl_float 				aspect_ratio;
	cl_float				min_distance;
	cl_float				max_distance;
	/// Physics
	cl_float				pos_acc;
	cl_float				speed;
	cl_float				rot_speed;
	cl_float				rot_acc;
	cl_float3			pos;
	cl_float3			velocity;
	cl_float3			rot_velocity;
	cl_float3			local_x;
	cl_float3			local_y;
	cl_float3			local_z;
	/// Temp
	cl_int					mx;
	cl_int					my;

# else

	/// Rendering
	float 				aspect_ratio;
	float				min_distance;
	float				max_distance;
	/// Physics
	float				pos_acc;
	float				speed;
	float				rot_speed;
	float				rot_acc;
	float3			pos;
	float3			velocity;
	float3			rot_velocity;
	float3			local_x;
	float3			local_y;
	float3			local_z;
	/// Temp
	int					mx;
	int					my;

# endif

}						t_camera;

#endif

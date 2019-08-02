#ifndef RT_H
# define RT_H

# ifndef OPENCL___
#  include <OpenCL/opencl.h>
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

#endif

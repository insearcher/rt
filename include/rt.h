#ifndef RT_H
# define RT_H

# define CL_SILENCE_DEPRECATION

# define INPUT_SYSTEM_INDEX	0

# ifndef OPENCL___
#  include <OpenCL/opencl.h>
#  include "rt_camera.h"
#  include "libcl.h"
# endif

# include "rt_light.h"
# include "rt_object.h"
# include "rt_camera.h"
# include "rt_raycast_hit.h"
# include "transform.h"

typedef struct			s_scene
{
	t_camera			camera;
# ifndef OPENCL___
	cl_float3			ambient;
	cl_uint				objects_count;
	cl_uint				lights_count;
	t_object			*objects;
	t_light				*lights;
# else
	float3				ambient;
	uint				objects_count;
	uint				lights_count;
	__global t_object	*objects;
	__global t_light	*lights;
# endif
}						t_scene;

# ifndef OPENCL___
typedef struct			s_rt_main
{
	t_cl				*cl;
	t_scene				*scenes;
	size_t				systems_count;
	t_system			**systems;
}						t_rt_main;

void					create_buffers(t_rt_main *rt, cl_mem *cl_scene, cl_mem *cl_objects, cl_mem *cl_lights);

int						rt_render(t_ui_main *ui, void *a);
# endif

#endif

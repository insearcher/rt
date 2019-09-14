#ifndef RT_H
# define RT_H

# define CL_SILENCE_DEPRECATION

# define INPUT_SYSTEM_INDEX	0

# ifndef OPENCL___
# include "libjtoc.h"
# include "rt_camera.h"
# include "libcl.h"
# endif

# include "rt_numerics.h"
# include "rt_light.h"
# include "rt_object.h"
# include "rt_camera.h"
# include "rt_raycast_hit.h"
# include "transform.h"

#define RT_RENDER_1		(1 << 0)
#define RT_RENDER_2		(1 << 1)
#define RT_GAUSS_BLUR	(1 << 2)

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
typedef struct			s_static_gpu_mem
{
	cl_mem 				cl_image;
	cl_mem 				cl_aux;
}						t_s_gpu_mem;

typedef struct			s_rt_main
{
	t_cl				*cl;
	t_scene				*scenes; //TODO remake to vec
	size_t				systems_count;
	void				**systems;
	t_s_gpu_mem			*gpu_mem;
	int					params;
	cl_int2				screen_size;
}						t_rt_main;

t_rt_main				*setup_rt(cl_int2 screen_size);
int						rt_render(t_ui_main *ui, void *a);
void					render_processing(t_rt_main *rt, size_t *global_size);
void					post_processing(t_rt_main *rt, size_t *global_size);
# endif

#endif

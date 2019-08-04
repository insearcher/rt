#ifndef RT_H
# define RT_H

# ifndef OPENCL___
#  include <OpenCL/opencl.h>
#  include "rt_camera.h"
#  include "libcl.h"
# endif

# include "rt_camera.h"
# include "transform.h"

typedef struct			s_object
{
	t_transform			transform;

# ifndef OPENCL___
	cl_int				type;
	t_rb				rb;
# else
	int					type;
	char				trash[112];
# endif
}						t_object;

typedef struct			s_scene
{
	size_t				objects_count;
	t_camera			camera;
	t_object			*objects;
}						t_scene;

# ifndef OPENCL___
typedef struct			s_rt_main
{
	t_cl				*cl;
	t_scene				*scenes;
}						t_rt_main;

int						rt_render(t_ui_main *ui, void *a);
# endif

#endif

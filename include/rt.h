#ifndef RT_H
# define RT_H

# define CL_SILENCE_DEPRECATION

# define INPUT_SYSTEM_INDEX	0

# ifndef OPENCL___
# include "libjtoc.h"
# include "rt_camera.h"
# include "libcl.h"
# include "rt_utilities.h"
# endif

# include "rt_numerics.h"
# include "rt_light.h"
# include "rt_object.h"
# include "rt_camera.h"
# include "rt_raycast_hit.h"
# include "transform.h"

#define RT_PATH_TRACE	(1 << 0)
#define RT_PHONG		(1 << 1)
#define RT_REPETITION	(1 << 2)

typedef struct			s_scene
{
	t_camera			camera;
# ifndef OPENCL___

	t_vec				*objects;
	t_vec				*lights;
	cl_float3			ambient;
	cl_int				quality;
	cl_int				fsaa;
	cl_int				path_trace_number;
	cl_int				path_trace_bounces;
	cl_int				params;
# else

	__global t_object	*objects;
	uint				objects_count;
	__global t_light	*lights;
	uint				lights_count;
	float3				ambient;
	int					quality;
	int					fsaa;
	int					path_trace_number;
	int					path_trace_bounces;
	int					params;
# endif

}						t_scene;

# ifndef OPENCL___

typedef struct			s_static_gpu_mem
{
	cl_mem 				cl_image;
	cl_mem 				cl_aux;
	cl_mem 				cl_pt_color_buf;
	cl_mem 				cl_texture;
	cl_mem				cl_texture_w;
	cl_mem				cl_texture_h;
	cl_mem				cl_prev_texture_size;
}						t_s_gpu_mem;

typedef struct 			s_obj_texture
{
	char				**textures_path;
	unsigned int		textures_count;
	int 				w;
	int 				h;
	int 				*texture;
	int 				bpp;
	int					texture_w[100];
	int					texture_h[100];
	int					prev_texture_size[100];
	size_t				texture_size;
}						t_obj_texture;

typedef struct			s_rt_main
{
	t_obj_texture		*texture;
	t_cl				*cl;
	t_vec				*pp;
	t_scene				*scene;
	size_t				systems_count;
	void				**systems;
	t_s_gpu_mem			*gpu_mem;
	int					params;
	cl_int2				screen_size;
}						t_rt_main;

t_rt_main				*rt_setup(cl_int2 screen_size,
							const char *textures_path,
							const char *scene_path);

int						rt_render(t_ui_main *ui, void *a);
void					render_processing(t_rt_main *rt, size_t *global_size,
		cl_int path_trace_count);
int						rt_render_update(t_ui_main *ui, void *el_v);
void					post_processing(t_rt_main *rt);
int						*get_texture(t_rt_main *rt);

t_transform				*rt_find_transform_by_id(t_scene *scene, cl_uint id);
t_object				*rt_find_object_by_id(t_vec *objects, cl_uint id);
t_light					*rt_find_light_by_id(t_vec *lights, cl_uint id);
int						rt_find_object_by_id_in_array(t_vec *objects,
		cl_uint id);

void					get_textures(t_rt_main *rt,
		char **texture_file, int number_of_texture);
void					find_textures_size(t_rt_main *rt,
		char **texture_file, int number_of_texture);

# endif

#endif

#ifndef RT_JTOC_H
# define RT_JTOC_H


int				rt_jtoc_get_float3(cl_float3 *vec, t_jnode *n);
int				rt_jtoc_sdl_log_error(const char *p, const int id);
int				rt_jtoc_get_camera(t_camera *camera, t_jnode *n);
int				rt_jtoc_get_transform(t_transform *transform, t_jnode *n);
t_scene			*rt_jtoc_scenes_setup(char **jsons);

# endif

#ifndef RT_JTOC_H
# define RT_JTOC_H

t_scene			*rt_jtoc_scenes_setup(char **jsons);
int				rt_jtoc_get_float2(cl_float2 *vec, t_jnode *n);
int				rt_jtoc_get_float3(cl_float3 *vec, t_jnode *n);
int				rt_jtoc_get_float4(cl_float4 *vec, t_jnode *n);
int				rt_jtoc_sdl_log_error(const char *p, const int id);
int				rt_jtoc_get_camera(t_camera *camera, t_jnode *n);
int				rt_jtoc_get_transform(t_transform *transform, t_jnode *n);
int				rt_jtoc_get_objects_num_in_arr(unsigned int *objects_num, t_jnode *n);
int				rt_jtoc_get_lights(t_scene *scene, t_jnode *n);
int				rt_jtoc_get_objects(t_scene *scene, t_jnode *n);
int				rt_jtoc_get_sphere(t_object *obj, t_jnode *n);
int				rt_jtoc_get_box(t_object *obj, t_jnode *n);
int				rt_jtoc_get_round_box(t_object *obj, t_jnode *n);
int				rt_jtoc_get_torus(t_object *obj, t_jnode *n);
int				rt_jtoc_get_plane(t_object *obj, t_jnode *n);

# endif

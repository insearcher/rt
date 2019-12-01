/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_jtoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 05:13:21 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/03 20:16:18 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_JTOC_H
# define RT_JTOC_H

# include "rt.h"

int				rt_jtoc_textures_setup(t_rt_main *rt, const char *json);
int				rt_jtoc_scene_setup(t_rt_main *rt, const char *json);
int				rt_jtoc_ps_setup(t_scene *scene, t_physics_system *ps,
		const char *path);

int				rt_jtoc_get_float2(cl_float2 *vec, t_jnode *n);
int				rt_jtoc_get_float3(cl_float3 *vec, t_jnode *n);
int				rt_jtoc_get_float4(cl_float4 *vec, t_jnode *n);
int				rt_jtoc_ispos_float2(cl_float2 *vec);
int				rt_jtoc_ispos_float3(cl_float3 *vec);
int				rt_jtoc_ispos_float4(cl_float4 *vec);
int				rt_jtoc_sdl_log_error(const char *p, const int id);
int				rt_jtoc_get_camera(t_camera *camera, t_jnode *n);
int				rt_jtoc_get_transform(t_transform *transform, t_jnode *n);
int				rt_jtoc_get_objects_num_in_arr(unsigned int *on,
		t_jnode *n);
int				rt_jtoc_get_lights(t_scene *scene, t_jnode *n);
int				rt_jtoc_get_objects(t_scene *scene, t_jnode *n,
				t_obj_texture *texture);
int				rt_jtoc_get_sphere(t_object *obj, t_jnode *n);
int				rt_jtoc_get_box(t_object *obj, t_jnode *n);
int				rt_jtoc_get_round_box(t_object *obj, t_jnode *n);
int				rt_jtoc_get_torus(t_object *obj, t_jnode *n);
int				rt_jtoc_get_plane(t_object *obj, t_jnode *n);
int				rt_jtoc_get_cone(t_object *obj, t_jnode *n);
int				rt_jtoc_get_cylinder(t_object *obj, t_jnode *n);
int				rt_jtoc_get_link(t_object *obj, t_jnode *n);
int				rt_jtoc_get_octahedron(t_object *obj, t_jnode *n);
int				rt_jtoc_get_mandelbulb(t_object *obj, t_jnode *n);
int				rt_jtoc_get_mandelbox(t_object *obj, t_jnode *n);
int				rt_jtoc_get_menger_sponge(t_object *obj, t_jnode *n);
int				rt_jtoc_is01_float3(cl_float3 *vec);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_jtoc_get_object.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 15:16:35 by sbednar           #+#    #+#             */
/*   Updated: 2019/12/01 15:30:46 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_jtoc.h"

static int	rt_jtoc_check_and_get_id(t_scene *s, t_jnode *n, t_object *object)
{
	t_jnode		*tmp;
	cl_uint		id;

	if (!(tmp = jtoc_node_get_by_path(n, "id")) || tmp->type != integer)
		return (rt_jtoc_sdl_log_error("ID ERROR", -1));
	id = jtoc_get_int(tmp);
	if (id <= 0)
		return (FUNCTION_FAILURE);
	if (s->camera.transform.id == (cl_uint)id)
		return (rt_jtoc_sdl_log_error("THAT ID ALREADY EXISTS IN CAMERA", id));
	if (rt_find_light_by_id(s->lights, id))
		return (rt_jtoc_sdl_log_error("THAT ID ALREADY EXISTS IN LIGHTS", id));
	if (rt_find_object_by_id(s->objects, id))
		return (rt_jtoc_sdl_log_error("THAT ID ALREADY EXISTS IN OBJECTS", id));
	object->transform.id = id;
	return (FUNCTION_SUCCESS);
}

static int	helper(t_object *obj, t_jnode *n)
{
	int	er;

	er = 0;
	er = obj->type == o_sphere ? rt_jtoc_get_sphere(obj, n) : er;
	er = obj->type == o_box ? rt_jtoc_get_box(obj, n) : er;
	er = obj->type == o_round_box ? rt_jtoc_get_round_box(obj, n) : er;
	er = obj->type == o_torus ? rt_jtoc_get_torus(obj, n) : er;
	er = obj->type == o_plane ? rt_jtoc_get_plane(obj, n) : er;
	er = obj->type == o_cone ? rt_jtoc_get_cone(obj, n) : er;
	er = obj->type == o_cylinder ? rt_jtoc_get_cylinder(obj, n) : er;
	er = obj->type == o_link ? rt_jtoc_get_link(obj, n) : er;
	er = obj->type == o_octahedron ? rt_jtoc_get_octahedron(obj, n) : er;
	er = obj->type == o_mandelbulb ? rt_jtoc_get_mandelbulb(obj, n) : er;
	er = obj->type == o_mandelbox ? rt_jtoc_get_mandelbox(obj, n) : er;
	er = obj->type == o_menger_sponge ? rt_jtoc_get_menger_sponge(obj, n) : er;
	if (er != 0)
		return (FUNCTION_FAILURE);
	return (FUNCTION_SUCCESS);
}

int			rt_jtoc_get_object(t_object *obj, t_jnode *n,
		t_scene *s, t_obj_texture *t)
{
	t_jnode	*tmp;

	ft_bzero(obj, sizeof(t_object));
	if (rt_jtoc_get_object_type(obj, n))
		return (rt_jtoc_sdl_log_error("NOT VALID TYPE", -1));
	if (rt_jtoc_get_object_layer(obj, n))
		return (rt_jtoc_sdl_log_error("NOT VALID LAYER", -1));
	if (rt_jtoc_get_object_texture(obj, t, n))
		return (rt_jtoc_sdl_log_error("NOT VALID TEXTURE", -1));
	if (rt_jtoc_get_transform(&obj->transform, n))
		return (rt_jtoc_sdl_log_error("TRANSFORM ERROR", -1));
	if (!(tmp = jtoc_node_get_by_path(n, "color")) || tmp->type != object)
		return (rt_jtoc_sdl_log_error("COLOR ERROR", -1));
	if (rt_jtoc_get_float4(&obj->material.color, tmp))
		return (rt_jtoc_sdl_log_error("COLOR ERROR", -1));
	if (rt_jtoc_check_and_get_id(s, n, obj))
		return (rt_jtoc_sdl_log_error("ID ERROR", -1));
	rt_jtoc_get_object_name(obj, n);
	obj->sub_mult_flag = 0;
	obj->obj_with_oper_id = 0;
	return (helper(obj, n));
}

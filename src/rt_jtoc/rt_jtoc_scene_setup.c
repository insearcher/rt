/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_jtoc_scene_setup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 05:13:21 by sbecker           #+#    #+#             */
/*   Updated: 2019/12/01 20:22:28 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_jtoc.h"

static int	helper(t_object *obj, t_jnode *ton)
{
	char	*str;

	if (!(ton = jtoc_node_get_by_path(ton, "operation_name")) ||
		ton->type != string)
		return (rt_jtoc_sdl_log_error("THERE IS NO SUCH OPERATION NAME!", -1));
	if (!(str = (char *)ft_x_memalloc(sizeof(char) * 16)))
		return (FUNCTION_FAILURE);
	ft_strncpy(str, jtoc_get_string(ton), 15);
	if (!(ft_strcmp(str, "none")))
	{
		free(str);
		return (FUNCTION_SUCCESS);
	}
	else if (!(ft_strcmp(str, "sub")))
		obj->sub_mult_flag = 1;
	else if (!(ft_strcmp(str, "plus")))
		obj->sub_mult_flag = 2;
	else
	{
		free(str);
		return (rt_jtoc_sdl_log_error("OPERATION NAME ERROR", -1));
	}
	return (FUNCTION_SUCCESS);
}

int			rt_jtoc_get_oper_id(t_jnode *n, t_object *obj,
		t_vec **objects, int id)
{
	t_jnode		*tmp_obj_id;
	t_jnode		*tmp_oper_name;
	t_object	*objct;
	int			object_id;

	if (obj->sub_mult_flag == 3)
		return (FUNCTION_SUCCESS);
	if ((tmp_obj_id = jtoc_node_get_by_path(n, "operation"))
		&& tmp_obj_id->type == object)
	{
		tmp_oper_name = tmp_obj_id;
		if (!(tmp_obj_id = jtoc_node_get_by_path(tmp_obj_id, "object_id")) ||
			tmp_obj_id->type != integer)
			return (rt_jtoc_sdl_log_error("OBJECT ID ERROR OR MISSING", -1));
		object_id = jtoc_get_int(tmp_obj_id);
		id = rt_find_object_by_id_in_array(*objects, object_id);
		if (!(rt_find_object_by_id(*objects, object_id)))
			return (rt_jtoc_sdl_log_error("THERE IS NO SUCH OBJECT!", -1));
		obj->obj_with_oper_id = id;
		objct = (t_object *)vec_at(*objects, id);
		objct->sub_mult_flag = 3;
		if (helper(obj, tmp_oper_name))
			return (FUNCTION_FAILURE);
	}
	return (FUNCTION_SUCCESS);
}

int			rt_jtoc_get_objects_operation(t_scene *scene, t_jnode *n)
{
	t_jnode		*tmp;
	int			i;

	tmp = n->down;
	i = 0;
	while (tmp)
	{
		if (rt_jtoc_get_oper_id(tmp, (t_object *)vec_at(scene->objects, i),
				&scene->objects, i))
			return (rt_jtoc_sdl_log_error("OPER ID ERROR", i));
		tmp = tmp->right;
	}
	return (FUNCTION_SUCCESS);
}

int			rt_jtoc_scene_setup(t_rt_main *rt, const char *json)
{
	int		i;
	t_scene	*scene;

	scene = (t_scene *)ft_x_memalloc(sizeof(t_scene));
	i = -1;
	if (rt_jtoc_get_scene(json, scene, rt->texture))
	{
		rt_jtoc_sdl_log_error("SCENE ERROR", i);
		exit(-1);
	}
	rt->scene = scene;
	return (FUNCTION_SUCCESS);
}

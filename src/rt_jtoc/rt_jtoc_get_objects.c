/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_jtoc_get_objects.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 05:13:21 by sbecker           #+#    #+#             */
/*   Updated: 2019/12/01 15:27:20 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_jtoc.h"

int	rt_jtoc_get_objects(t_scene *scene, t_jnode *n, t_obj_texture *texture)
{
	t_jnode		*tmp;
	t_object	obj;
	uint		c;
	int			i;

	c = 0;
	if (rt_jtoc_get_objects_num_in_arr(&c, n) ||
		!(scene->objects = vec_init(c, sizeof(t_object))))
		return (FUNCTION_FAILURE);
	if (c >= 100)
		return (rt_jtoc_sdl_log_error("OBJECT OVER 100", -1));
	tmp = n->down;
	i = 0;
	while (tmp)
	{
		if (tmp->type != object)
			return (rt_jtoc_sdl_log_error("OBJECT TYPE ERROR", i));
		if (rt_jtoc_get_object(&obj, tmp, scene, texture))
			return (rt_jtoc_sdl_log_error("OBJECT DATA ERROR", i));
		vec_push_back(scene->objects, &obj);
		i++;
		tmp = tmp->right;
	}
	return (FUNCTION_SUCCESS);
}

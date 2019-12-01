/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_jtoc_get_object_texture.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 15:26:59 by sbednar           #+#    #+#             */
/*   Updated: 2019/12/01 15:28:01 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_jtoc.h"

int		rt_jtoc_compare_str_with_texture_name(t_obj_texture *t, char *str)
{
	int	i;
	int	cache_counter;

	i = -1;
	cache_counter = t->textures_count;
	while (++i < cache_counter)
		if ((ft_strstr(t->textures_path[i], str)))
			return (i);
	return (-2);
}

int		rt_jtoc_get_object_texture(t_object *obj,
		t_obj_texture *texture, t_jnode *n)
{
	t_jnode	*tmp;
	int		id;
	char	*str;

	if (!(tmp = jtoc_node_get_by_path(n, "texture"))
		|| tmp->type != string)
		return (rt_jtoc_sdl_log_error("TEXTURE ERROR", -1));
	str = jtoc_get_string(tmp);
	if (!(ft_strcmp(str, "none")))
		id = -1;
	else
		id = rt_jtoc_compare_str_with_texture_name(texture, str);
	if (id == -2)
		return (rt_jtoc_sdl_log_error("TEXTURE NAME ERROR", -1));
	obj->material.texture_id = id;
	return (FUNCTION_SUCCESS);
}

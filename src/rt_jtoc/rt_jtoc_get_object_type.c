/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_jtoc_get_object_type.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 15:25:53 by sbednar           #+#    #+#             */
/*   Updated: 2019/12/01 15:26:56 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_jtoc.h"

int	rt_jtoc_get_object_type(t_object *obj, t_jnode *n)
{
	char	*str;
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "type")) || tmp->type != string)
		return (rt_jtoc_sdl_log_error("TYPE ERROR OR TYPE IS MISSING", -1));
	str = jtoc_get_string(tmp);
	obj->type = 0;
	obj->type = ft_strcmp(str, "sphere") ? obj->type : o_sphere;
	obj->type = ft_strcmp(str, "box") ? obj->type : o_box;
	obj->type = ft_strcmp(str, "round_box") ? obj->type : o_round_box;
	obj->type = ft_strcmp(str, "torus") ? obj->type : o_torus;
	obj->type = ft_strcmp(str, "capped_torus") ? obj->type : o_capped_torus;
	obj->type = ft_strcmp(str, "link") ? obj->type : o_link;
	obj->type = ft_strcmp(str, "cylinder") ? obj->type : o_cylinder;
	obj->type = ft_strcmp(str, "cone") ? obj->type : o_cone;
	obj->type = ft_strcmp(str, "plane") ? obj->type : o_plane;
	obj->type = ft_strcmp(str, "octahedron") ? obj->type : o_octahedron;
	obj->type = ft_strcmp(str, "mandelbulb") ? obj->type : o_mandelbulb;
	obj->type = ft_strcmp(str, "mandelbox") ? obj->type : o_mandelbox;
	obj->type = ft_strcmp(str, "menger_sponge") ? obj->type : o_menger_sponge;
	if (obj->type == 0)
		return (FUNCTION_FAILURE);
	return (FUNCTION_SUCCESS);
}

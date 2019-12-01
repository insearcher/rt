/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_jtoc_get_object_name.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 15:19:42 by sbednar           #+#    #+#             */
/*   Updated: 2019/12/01 15:30:46 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	rt_jtoc_get_type_name2(int type, char *str, char *tmp_id)
{
	if (type == o_cylinder)
		ft_strcat(ft_strcat(str, "Cylinder"), tmp_id);
	else if (type == o_cone)
		ft_strcat(ft_strcat(str, "Cone"), tmp_id);
	else if (type == o_plane)
		ft_strcat(ft_strcat(str, "Plane"), tmp_id);
	else if (type == o_octahedron)
		ft_strcat(ft_strcat(str, "Octahedron"), tmp_id);
	else if (type == o_mandelbulb)
		ft_strcat(ft_strcat(str, "Mandelbulb"), tmp_id);
	else if (type == o_mandelbox)
		ft_strcat(ft_strcat(str, "Mandelbox"), tmp_id);
	else if (type == o_menger_sponge)
		ft_strcat(ft_strcat(str, "Menger Sponge"), tmp_id);
}

static int	rt_jtoc_get_type_name(int type, int id, char *str)
{
	char	*tmp_id;
	char	tmp_str[15];

	ft_bzero(tmp_str, 15);
	tmp_id = ft_itoa(id);
	if (type == o_sphere)
		ft_strcat(ft_strcat(str, "Sphere"), tmp_id);
	else if (type == o_box)
		ft_strcat(ft_strcat(str, "Box"), tmp_id);
	else if (type == o_round_box)
		ft_strcat(ft_strcat(str, "Round Box"), tmp_id);
	else if (type == o_torus)
		ft_strcat(ft_strcat(str, "Torus"), tmp_id);
	else if (type == o_capped_torus)
		ft_strcat(ft_strcat(str, "Capped Torus"), tmp_id);
	else if (type == o_link)
		ft_strcat(ft_strcat(str, "Link"), tmp_id);
	else
		rt_jtoc_get_type_name2(type, str, tmp_id);
	free(tmp_id);
	return (FUNCTION_SUCCESS);
}

static int	rt_jtoc_compare_name(t_object *obj, int i, char str[1000][15],
		int name)
{
	int	tmp;

	tmp = i;
	while (tmp > 0)
		if (ft_strcmp(obj->local_name, str[tmp - 1]) == 0)
			break ;
		else
			tmp--;
	if (tmp == 0)
		return (FUNCTION_SUCCESS);
	else
	{
		ft_bzero(str[i], 15);
		rt_jtoc_get_type_name(obj->type, name, str[i]);
		obj->local_name = str[i];
		name++;
		rt_jtoc_compare_name(obj, i, str, name);
	}
	return (FUNCTION_SUCCESS);
}

int			rt_jtoc_get_object_name(t_object *obj, t_jnode *n)
{
	t_jnode		*tmp;
	char		*str;
	int			name;
	static int	i = 0;
	static char	tmp_str[1000][15];

	if (!(str = (char *)ft_x_memalloc(sizeof(char) * 16)))
		return (FUNCTION_FAILURE);
	name = 0;
	if ((tmp = jtoc_node_get_by_path(n, "name")) && tmp->type == string)
	{
		ft_strncpy(str, jtoc_get_string(tmp), 15);
		obj->local_name = str;
	}
	else
	{
		rt_jtoc_get_type_name(obj->type, name, str);
		obj->local_name = str;
	}
	ft_strcpy(tmp_str[i], str);
	rt_jtoc_compare_name(obj, i, tmp_str, name);
	obj->local_name = tmp_str[i];
	i++;
	free(str);
	return (FUNCTION_SUCCESS);
}

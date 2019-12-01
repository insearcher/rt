/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_jtoc_scene_setup2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 20:03:14 by sbednar           #+#    #+#             */
/*   Updated: 2019/12/01 20:16:55 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_jtoc.h"

static int	rt_jtoc_get_scene_params(t_scene *scene, t_jnode *n)
{
	t_jnode	*tmp;
	char	*str;
	int		params;

	params = 0;
	tmp = n->down;
	while (tmp)
	{
		if (tmp->type != string)
			return (rt_jtoc_sdl_log_error("PARAMS TYPE ERROR", -1));
		str = jtoc_get_string(tmp);
		params |= ft_strcmp(str, "repetition") ? 0 : RT_REPETITION;
		params |= ft_strcmp(str, "path_trace") ? 0 : RT_PATH_TRACE;
		params |= ft_strcmp(str, "phong") ? 0 : RT_PHONG;
		if ((params & RT_PATH_TRACE) && (params & RT_PHONG))
			return (rt_jtoc_sdl_log_error("BOTH PT & PHONG - ERROR", -1));
		tmp = tmp->right;
	}
	scene->params |= params;
	return (FUNCTION_SUCCESS);
}

static int	rt_jtoc_get_scene3(t_jnode *root, t_scene *scene,
		t_obj_texture *texture)
{
	t_jnode	*t;

	if (!(t = jtoc_node_get_by_path(root, "objects")) || t->type != array)
		return (rt_jtoc_sdl_log_error("OBJECTS ERROR", -1));
	if (rt_jtoc_get_objects(scene, t, texture))
		return (rt_jtoc_sdl_log_error("OBJECTS ERROR", -1));
	if (rt_jtoc_get_objects_operation(scene, t))
		return (rt_jtoc_sdl_log_error("OBJECT OPERATION ERROR", -1));
	if (!(t = jtoc_node_get_by_path(root, "quality")) || t->type != integer)
		return (rt_jtoc_sdl_log_error("QUALITY ERROR", -1));
	scene->quality = jtoc_get_int(t);
	if (scene->quality > 100)
		return (rt_jtoc_sdl_log_error("MAX QUALITY IS 100", -1));
	jtoc_node_clear(root);
	return (FUNCTION_SUCCESS);
}

static int	rt_jtoc_get_scene2(t_jnode *root, t_scene *scene,
		t_obj_texture *texture)
{
	t_jnode	*t;

	if (!(t = jtoc_node_get_by_path(root, "path_trace_number"))
		|| t->type != integer)
		return (rt_jtoc_sdl_log_error("PATH_TRACE_NUMBER ERROR", -1));
	scene->path_trace_number = jtoc_get_int(t);
	if (!(t = jtoc_node_get_by_path(root, "path_trace_bounces"))
		|| t->type != integer)
		return (rt_jtoc_sdl_log_error("PATH_TRACE_BOUNCES ERROR", -1));
	scene->path_trace_bounces = jtoc_get_int(t);
	if (!(t = jtoc_node_get_by_path(root, "camera")) || t->type != object)
		return (rt_jtoc_sdl_log_error("CAMERA ERROR", -1));
	if (rt_jtoc_get_camera(&(scene->camera), t))
		return (rt_jtoc_sdl_log_error("CAMERA DATA ERROR", -1));
	if (!(t = jtoc_node_get_by_path(root, "lights")) || t->type != object)
		return (rt_jtoc_sdl_log_error("LIGHTS ERROR", -1));
	if (rt_jtoc_get_lights(scene, t))
		return (rt_jtoc_sdl_log_error("LIGHTS ERROR", -1));
	return (rt_jtoc_get_scene3(root, scene, texture));
}

int			rt_jtoc_get_scene(const char *path, t_scene *scene,
		t_obj_texture *texture)
{
	t_jnode	*root;
	t_jnode	*t;

	if (!(root = jtoc_read(path)))
		return (rt_jtoc_sdl_log_error("JSON", -1));
	if ((t = jtoc_node_get_by_path(root, "params")) && t->type == array)
		if (rt_jtoc_get_scene_params(scene, t))
			return (rt_jtoc_sdl_log_error("SCENE PARAMS ERROR", -1));
	if (!(t = jtoc_node_get_by_path(root, "quality")) || t->type != integer)
		return (rt_jtoc_sdl_log_error("QUALITY ERROR", -1));
	scene->quality = jtoc_get_int(t);
	if (scene->quality > 100)
		return (rt_jtoc_sdl_log_error("MAX QUALITY IS 100", -1));
	if (!(t = jtoc_node_get_by_path(root, "smoothing")) || t->type != integer)
		return (rt_jtoc_sdl_log_error("SMOOTHING ERROR", -1));
	scene->fsaa = jtoc_get_int(t);
	scene->fsaa = scene->fsaa % 2 ? scene->fsaa + 1 : scene->fsaa;
	if (scene->fsaa > 10)
		return (rt_jtoc_sdl_log_error("MAX SMOOTHING IS 10", -1));
	return (rt_jtoc_get_scene2(root, scene, texture));
}

#include "rt.h"
#include "rt_jtoc.h"

static int	rt_jtoc_get_lights(cl_float3 *ambient, t_light **lights, t_jnode *n)
{
	t_jnode	*tmp;

	if ((tmp = jtoc_node_get_by_path(n, "ambient")) && tmp->type == object)
	{
		if (rt_jtoc_get_float3(ambient, tmp))
			return (rt_jtoc_sdl_log_error("AMBIENT ERROR", -1));
	}
	(void)lights;
	return (FUNCTION_SUCCESS);
}

static int	rt_jtoc_get_scene(const char *path, t_scene *scene)
{
	t_jnode	*root;
	t_jnode	*tmp;

	if (!(root = jtoc_read(path)))
		return (rt_jtoc_sdl_log_error("JSON", -1));

	if (!(tmp = jtoc_node_get_by_path(root, "camera")) || tmp->type != object)
		return (rt_jtoc_sdl_log_error("CAMERA TYPE ERROR OR CAMERA IS MISSING", -1));
	if (rt_jtoc_get_camera(&(scene->camera), tmp))
		return (rt_jtoc_sdl_log_error("CAMERA DATA ERROR", -1));

	if (!(tmp = jtoc_node_get_by_path(root, "lights")) || tmp->type != object)
		return (rt_jtoc_sdl_log_error("LIGHTS TYPE ERROR OR LIGHTS IS MISSING", -1));
	if (rt_jtoc_get_lights(&(scene->ambient), &(scene->lights), tmp))
		return (rt_jtoc_sdl_log_error("LIGHTS ERROR", -1));

	jtoc_node_clear(root);
	return (FUNCTION_SUCCESS);
}

t_scene		*rt_jtoc_scenes_setup(char **jsons)
{
	int		i;
	t_scene	*scenes;

	i = -1;
	while (jsons[++i])
		;
	scenes = (t_scene *)ft_x_memalloc(sizeof(t_scene) * i);
	i = -1;
	while (jsons[++i])
	{
		if (rt_jtoc_get_scene(jsons[i], &(scenes[i])))
		{
			rt_jtoc_sdl_log_error("SCENE ERROR", i);
			exit(-1);
		}
	}
	return (scenes);
}
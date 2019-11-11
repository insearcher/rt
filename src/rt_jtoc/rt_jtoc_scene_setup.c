#include "rt.h"
#include "rt_jtoc.h"

static int	rt_jtoc_get_scene(const char *path, t_scene *scene, t_obj_texture *texture)
{
	t_jnode	*root;
	t_jnode	*tmp;

	if (!(root = jtoc_read(path)))
		return (rt_jtoc_sdl_log_error("JSON", -1));
	if (!(tmp = jtoc_node_get_by_path(root, "camera")) || tmp->type != object)
		return (rt_jtoc_sdl_log_error("CAMERA TYPE ERROR OR CAMERA IS NOT SET", -1));
	if (rt_jtoc_get_camera(&(scene->camera), tmp))
		return (rt_jtoc_sdl_log_error("CAMERA DATA ERROR", -1));
	if (!(tmp = jtoc_node_get_by_path(root, "lights")) || tmp->type != object)
		return (rt_jtoc_sdl_log_error("LIGHTS TYPE ERROR OR LIGHTS AREN'T SET", -1));
	if (rt_jtoc_get_lights(scene, tmp))
		return (rt_jtoc_sdl_log_error("LIGHTS ERROR", -1));
	if (!(tmp = jtoc_node_get_by_path(root, "objects")) || tmp->type != array)
		return (rt_jtoc_sdl_log_error("OBJECTS TYPE ERROR OR OBJECTS AREN'T SET", -1));
	if (rt_jtoc_get_objects(scene, tmp, texture))
		return (rt_jtoc_sdl_log_error("OBJECTS ERROR", -1));
	if (!(tmp = jtoc_node_get_by_path(root, "quality")) || tmp->type != integer)
		return (rt_jtoc_sdl_log_error("QUALITY ERROR", -1));
	scene->quality = jtoc_get_int(tmp);
	if (scene->quality > 100)
		return (rt_jtoc_sdl_log_error("MAX QUALITY IS 100", -1));
	jtoc_node_clear(root);
	return (FUNCTION_SUCCESS);
}

int rt_jtoc_scene_setup(t_rt_main *rt, const char *json)
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
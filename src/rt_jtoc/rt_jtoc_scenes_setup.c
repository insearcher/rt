#include "rt.h"
#include "rt_jtoc.h"

/*int			rt_jtoc_get_rb(t_rb *rb, t_jnode *n)
{

}

int			rt_jtoc_get_rigid_bodies(t_scene *scene, t_jnode *n)
{
	t_jnode				*tmp;
	int					i;
	int					id;
	t_physics_system	*ps;

	ps = ft_x_memalloc(sizeof(t_physics_system));
	ps->system.parent = ps;
	ps->rbs_count = 0;
	tmp = n->down;
	while (tmp)
	{
		if (tmp->type != object)
			return (rt_jtoc_sdl_log_error("TYPE ERROR", -1));
		ps->rbs_count++;
		tmp = tmp->right;
	}
	ps->rbs = (t_rb *)ft_x_memalloc(sizeof(t_physics_system));
	tmp = n->down;
	i = 0;
	while (tmp)
	{
		if (rt_jtoc_get_rb(&(ps->rbs[i])))
			return (rt_jtoc_sdl_log_error("RB ERROR", -1));
		tmp = tmp->right;
	}
	if (!(tmp = jtoc_node_get_by_path(n, "id")) || tmp->type != integer)
		return (rt_jtoc_sdl_log_error("ID ERROR", -1));
	if (rt_find_transform_by_id(scene, ));
	return (FUNCTION_SUCCESS);
}*/

static int	rt_jtoc_get_scene(const char *path, t_scene *scene)
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
	if (rt_jtoc_get_objects(scene, tmp))
		return (rt_jtoc_sdl_log_error("OBJECTS ERROR", -1));

/*	if ((tmp = jtoc_node_get_by_path(root, "rigid_bodies")) && tmp->type == array)
		if (rt_jtoc_get_rigid_bodies(scene, tmp))
			return (rt_jtoc_sdl_log_error("RIGID BODIES ERROR", -1));
	jtoc_node_clear(root);*/
	return (FUNCTION_SUCCESS);
}

int		rt_jtoc_scene_setup(t_rt_main *rt, const char *json)
{
	int		i;
	t_scene	*scene;

	scene = (t_scene *)ft_x_memalloc(sizeof(t_scene));
	i = -1;
	if (rt_jtoc_get_scene(json, scene))
	{
		rt_jtoc_sdl_log_error("SCENE ERROR", i);
		exit(-1);
	}
	rt->scene = scene;
	return (FUNCTION_SUCCESS);
}
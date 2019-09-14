#include "rt.h"
#include "rt_jtoc.h"

/*int				rt_jtoc_get_transform(t_transform *transform, t_jnode *n)
{
	t_jnode	*tmp;

	ft_bzero(transform, sizeof(t_transform));
	if (!(n = jtoc_node_get_by_path(n, "transform")) || n->type != object)
		return (rt_jtoc_sdl_log_error("TRANSFORM TYPE ERROR OR TRANSFORM MISSING", -1));

	if (!(tmp = jtoc_node_get_by_path(n, "pos")) || tmp->type != object)
		return (rt_jtoc_sdl_log_error("POS ERROR", -1));
	if (rt_jtoc_get_float3(&(transform->pos), tmp))
		return (rt_jtoc_sdl_log_error("POS ERROR", -1));

	if (!(tmp = jtoc_node_get_by_path(n, "right")) || tmp->type != object)
		return (rt_jtoc_sdl_log_error("RIGHT TYPE ERROR OR RIGHT MISSING", -1));
	if (rt_jtoc_get_float3(&(transform->right), tmp))
		return (rt_jtoc_sdl_log_error("RIGHT ERROR", -1));

	if (!(tmp = jtoc_node_get_by_path(n, "up")) || tmp->type != object)
		return (rt_jtoc_sdl_log_error("UP TYPE ERROR OR UP MISSING", -1));
	if (rt_jtoc_get_float3(&(transform->up), tmp))
		return (rt_jtoc_sdl_log_error("UP ERROR", -1));

	if (!(tmp = jtoc_node_get_by_path(n, "forward")) || tmp->type != object)
		return (rt_jtoc_sdl_log_error("FORWARD TYPE ERROR OR FORWARD MISSING", -1));
	if (rt_jtoc_get_float3(&(transform->forward), tmp))
		return (rt_jtoc_sdl_log_error("FORWARD ERROR", -1));
	return (FUNCTION_SUCCESS);
}*/

int				rt_jtoc_get_transform(t_transform *transform, t_jnode *n)
{
	t_jnode	*tmp;

	ft_bzero(transform, sizeof(t_transform));
	if (!(n = jtoc_node_get_by_path(n, "transform")) || n->type != object)
		return (rt_jtoc_sdl_log_error("TRANSFORM TYPE ERROR OR TRANSFORM MISSING", -1));

	if (!(tmp = jtoc_node_get_by_path(n, "pos")) || tmp->type != object)
		return (rt_jtoc_sdl_log_error("POS ERROR", -1));
	if (rt_jtoc_get_float3(&(transform->pos), tmp))
		return (rt_jtoc_sdl_log_error("POS ERROR", -1));

	if ((tmp = jtoc_node_get_by_path(n, "right")) && tmp->type == object)
		if (rt_jtoc_get_float3(&(transform->right), tmp))
			return (rt_jtoc_sdl_log_error("RIGHT ERROR", -1));

	if ((tmp = jtoc_node_get_by_path(n, "up")) && tmp->type == object)
		if (rt_jtoc_get_float3(&(transform->up), tmp))
			return (rt_jtoc_sdl_log_error("UP ERROR", -1));

	if ((tmp = jtoc_node_get_by_path(n, "forward")) && tmp->type == object)
		if (rt_jtoc_get_float3(&(transform->forward), tmp))
			return (rt_jtoc_sdl_log_error("FORWARD ERROR", -1));
	return (FUNCTION_SUCCESS);
}

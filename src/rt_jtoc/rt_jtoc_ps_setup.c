/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_jtoc_ps_setup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 05:13:21 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/03 20:16:18 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_jtoc.h"

static int	rt_jtoc_get_move_params(t_move_params *p, t_jnode *n)
{
	t_jnode		*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "vel")) || tmp->type != object)
		return (rt_jtoc_sdl_log_error("VEL MISSING OR TYPE ERROR", -1));
	if (rt_jtoc_get_float3(&p->vel, tmp))
		return (rt_jtoc_sdl_log_error("VEL ERROR", -1));
	if (!(tmp = jtoc_node_get_by_path(n, "raw_vel")) || tmp->type != object)
		return (rt_jtoc_sdl_log_error("RAW_VEL MISSING OR TYPE ERROR", -1));
	if (rt_jtoc_get_float3(&p->raw_vel, tmp))
		return (rt_jtoc_sdl_log_error("RAW_VEL ERROR", -1));
	if (!(tmp = jtoc_node_get_by_path(n, "acc")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("ACC MISSING OR TYPE ERROR", -1));
	p->acc = jtoc_get_float(tmp);
	if (p->acc < 0)
		return (rt_jtoc_sdl_log_error("ACC ERROR", -1));
	if (!(tmp = jtoc_node_get_by_path(n, "speed")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("SPEED MISSING OR TYPE ERROR", -1));
	p->speed = jtoc_get_float(tmp);
	if (p->speed < 0)
		return (rt_jtoc_sdl_log_error("SPEED ERROR", -1));
	if (!(tmp = jtoc_node_get_by_path(n, "speed_mult")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("SPEED_MULT MISSING OR TYPE ERROR", -1));
	p->speed_mult = jtoc_get_float(tmp);
	if (p->speed_mult < 0)
		return (rt_jtoc_sdl_log_error("SPED MULT ERROR", -1));
	return (FUNCTION_SUCCESS);
}

static int	rt_jtoc_get_rb(t_scene *scene, t_physics_system *ps, t_jnode *n)
{
	t_transform	*t;
	t_jnode		*tmp;
	t_rb		rb;

	ft_bzero(&rb, sizeof(t_rb));
	if (!(tmp = jtoc_node_get_by_path(n, "id")) || tmp->type != integer)
		return (rt_jtoc_sdl_log_error("ID MISSING OR TYPE ERROR", -1));
	if (!(t = rt_find_transform_by_id(scene, jtoc_get_int(tmp))))
		return (rt_jtoc_sdl_log_error("THAT ID DOESN'T EXISTS", -1));
	rb.transform = t;
	if (!(tmp = jtoc_node_get_by_path(n, "move")) || tmp->type != object)
		return (rt_jtoc_sdl_log_error("MOVE MISSING OR TYPE ERROR", t->id));
	if (rt_jtoc_get_move_params(&rb.move, tmp))
		return (FUNCTION_FAILURE);
	if (!(tmp = jtoc_node_get_by_path(n, "rot")) || tmp->type != object)
		return (rt_jtoc_sdl_log_error("ROT MISSING OR TYPE ERROR", t->id));
	if (rt_jtoc_get_move_params(&rb.rot, tmp))
		return (FUNCTION_FAILURE);
	vec_push_back(&ps->rbs, &rb);
	return (FUNCTION_SUCCESS);
}

static int	rt_jtoc_get_rbs(t_scene *scene, t_physics_system *ps, t_jnode *n)
{
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "rbs")) || tmp->type != array)
		return (rt_jtoc_sdl_log_error("RBS MISSING OR TYPE ERROR", -1));
	tmp = tmp->down;
	while (tmp)
	{
		if (rt_jtoc_get_rb(scene, ps, tmp))
			return (FUNCTION_FAILURE);
		tmp = tmp->right;
	}
	return (FUNCTION_SUCCESS);
}

int			rt_jtoc_ps_setup(t_scene *scene, t_physics_system *ps, const char *path)
{
	t_jnode	*n;
	int		res;

	if (!(n = jtoc_read(path)))
		return (rt_jtoc_sdl_log_error("PHYSICS SYSTEM ERROR", -1));
	ps->system.parent = ps;
	if (vec_setup(&ps->rbs, 1, sizeof(t_rb)))
		return (FUNCTION_FAILURE);
	res = rt_jtoc_get_rbs(scene, ps, n);
	jtoc_node_clear(n);
	return (res);
}
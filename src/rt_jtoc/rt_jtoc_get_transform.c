#include "rt.h"
#include "rt_jtoc.h"

static void		rt_jtoc_setup_transform_default(t_transform *t)
{
	t->right = (cl_float3){{1, 0, 0}};
	t->up = (cl_float3){{0, 1, 0}};
	t->forward = (cl_float3){{0, 0, 1}};
}

static void		rt_jtoc_mult_basis(t_transform *t, float *m)
{
	mult(m, &t->right);
	mult(m, &t->up);
	mult(m, &t->forward);
}

static void		rt_jtoc_rotate_transform(t_transform *t, float x, float y,
											float z)
{
	float	m[9];

	fill_rotation_matrix(m + 0, (cl_float3){{1, 0, 0}}, x);
	rt_jtoc_mult_basis(t, m + 0);
	fill_rotation_matrix(m + 0, (cl_float3){{0, 1, 0}}, y);
	rt_jtoc_mult_basis(t, m + 0);
	fill_rotation_matrix(m + 0, (cl_float3){{0, 0, 1}}, z);
	rt_jtoc_mult_basis(t, m + 0);
}

static int		rt_jtoc_get_eulers(t_transform *t, t_jnode *n)
{
	t_jnode	*tmp;
	float	x;
	float	y;
	float	z;

	if (!(tmp = jtoc_node_get_by_path(n, "x")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("EULERS.X TYPE ERROR OR MISSING", -1));
	x = jtoc_get_float(tmp);
	if (!(tmp = jtoc_node_get_by_path(n, "y")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("EULERS.Y TYPE ERROR OR MISSING", -1));
	y = jtoc_get_float(tmp);
	if (!(tmp = jtoc_node_get_by_path(n, "z")) || tmp->type != fractional)
		return (rt_jtoc_sdl_log_error("EULERS.Z TYPE ERROR OR MISSING", -1));
	z = jtoc_get_float(tmp);
	rt_jtoc_rotate_transform(t, x, y, z);
	return (FUNCTION_SUCCESS);
}

int				rt_jtoc_get_transform(t_transform *transform, t_jnode *n)
{
	t_jnode	*tmp;

	ft_bzero(transform, sizeof(t_transform));
	if (!(n = jtoc_node_get_by_path(n, "transform")) || n->type != object)
		return (rt_jtoc_sdl_log_error("TRANSFORM TYPE ERROR OR TRANSFORM MISSING", -1));
	if (!(tmp = jtoc_node_get_by_path(n, "pos")) || tmp->type != object)
		return (rt_jtoc_sdl_log_error("POS TYPE ERROR OR MISSING", -1));
	if (rt_jtoc_get_float3(&(transform->pos), tmp))
		return (rt_jtoc_sdl_log_error("POS ERROR", -1));
	rt_jtoc_setup_transform_default(transform);
	if (!(tmp = jtoc_node_get_by_path(n, "eulers")) || tmp->type != object)
		return (rt_jtoc_sdl_log_error("EULERS TYPE ERROR OR MISSING", -1));
	if (rt_jtoc_get_eulers(transform, tmp))
		return (rt_jtoc_sdl_log_error("EULERS ERROR", -1));
	return (FUNCTION_SUCCESS);
}

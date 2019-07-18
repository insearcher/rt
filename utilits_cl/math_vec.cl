#include "math_vec.h"

t_vector3d	mv_minus(const t_vector3d a, const t_vector3d b)
{
	t_vector3d	C;

	C.x = a.x - b.x;
	C.y = a.y - b.y;
	C.z = a.z - b.z;
	return (C);
}

t_vector3d	mv_plus(const t_vector3d a, const t_vector3d b)
{
	t_vector3d	C;

	C.x = a.x + b.x;
	C.y = a.y + b.y;
	C.z = a.z + b.z;
	return (C);
}

t_vector3d	mv_mult(t_vector3d a, t_vector3d b)
{
	t_vector3d res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}

t_vector3d	mv_mult_num(const t_vector3d a, float num)
{
	t_vector3d	C;

	C.x = a.x * num;
	C.y = a.y * num;
	C.z = a.z * num;
	return (C);
}

t_vector3d	mv_dev_num(const t_vector3d a, float num)
{
	t_vector3d	C;

	C.x = a.x / num;
	C.y = a.y / num;
	C.z = a.z / num;
	return (C);
}

float		mv_scalar_mult(const t_vector3d a, const t_vector3d b)
{
	float	scalar_mult;

	scalar_mult = a.x * b.x + a.y * b.y + a.z * b.z;
	return (scalar_mult);
}

t_vector3d  mv_get_vector3d(float x, float y, float z)
{
	t_vector3d  vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

float		mv_length(const t_vector3d a)
{
	float	length;

	length = half_sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
//	length = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	return (length);
}

t_vector3d	mv_normalize(const t_vector3d a)
{
	t_vector3d	vec;
	float		len;

	len = mv_length(a);
	if (len == 0)
		return (a);
	vec = mv_mult_num(a, 1 / len);
	return (vec);
}

t_vector3d	mv_inverse(const t_vector3d a)
{
	t_vector3d	vec;

	vec.x = -a.x;
	vec.y = -a.y;
	vec.z = -a.z;
	return (vec);
}

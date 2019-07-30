#include "math_vec.h"

# ifndef OPENCL___

cl_float3	mv_minus(const cl_float3 a, const cl_float3 b)
{
	cl_float3	C;

	C.x = a.x - b.x;
	C.y = a.y - b.y;
	C.z = a.z - b.z;
	return (C);
}

cl_float3	mv_plus(const cl_float3 a, const cl_float3 b)
{
	cl_float3	C;

	C.x = a.x + b.x;
	C.y = a.y + b.y;
	C.z = a.z + b.z;
	return (C);
}

cl_float3	mv_mult(cl_float3 a, cl_float3 b)
{
	cl_float3 res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}

cl_float3	mv_mult_num(const cl_float3 a, float num)
{
	cl_float3	C;

	C.x = a.x * num;
	C.y = a.y * num;
	C.z = a.z * num;
	return (C);
}

cl_float3	mv_dev_num(const cl_float3 a, float num)
{
	cl_float3	C;

	C.x = a.x / num;
	C.y = a.y / num;
	C.z = a.z / num;
	return (C);
}

float		mv_scalar_mult(const cl_float3 a, const cl_float3 b)
{
	float	scalar_mult;

	scalar_mult = a.x * b.x + a.y * b.y + a.z * b.z;
	return (scalar_mult);
}

cl_float3  mv_get_vector3d(float x, float y, float z)
{
	cl_float3  vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

float		mv_length(const cl_float3 a)
{
	float	length;

//	length = half_sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	length = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	return (length);
}

cl_float3	mv_normalize(const cl_float3 a)
{
	cl_float3	vec;
	float		len;

	len = mv_length(a);
	if (len == 0)
		return (a);
	vec = mv_mult_num(a, 1 / len);
	return (vec);
}

cl_float3	mv_inverse(const cl_float3 a)
{
	cl_float3	vec;

	vec.x = -a.x;
	vec.y = -a.y;
	vec.z = -a.z;
	return (vec);
}

#else

float3	mv_minus(const float3 a, const float3 b)
{
	float3	C;

	C.x = a.x - b.x;
	C.y = a.y - b.y;
	C.z = a.z - b.z;
	return (C);
}

float3	mv_plus(const float3 a, const float3 b)
{
	float3	C;

	C.x = a.x + b.x;
	C.y = a.y + b.y;
	C.z = a.z + b.z;
	return (C);
}

float3	mv_mult(float3 a, float3 b)
{
	float3 res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}

float3	mv_mult_num(const float3 a, float num)
{
	float3	C;

	C.x = a.x * num;
	C.y = a.y * num;
	C.z = a.z * num;
	return (C);
}

float3	mv_dev_num(const float3 a, float num)
{
	float3	C;

	C.x = a.x / num;
	C.y = a.y / num;
	C.z = a.z / num;
	return (C);
}

float		mv_scalar_mult(const float3 a, const float3 b)
{
	float	scalar_mult;

	scalar_mult = a.x * b.x + a.y * b.y + a.z * b.z;
	return (scalar_mult);
}

float3  mv_get_vector3d(float x, float y, float z)
{
	float3  vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

float		mv_length(const float3 a)
{
	float	length;

	length = half_sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
//	length = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	return (length);
}

float3	mv_normalize(const float3 a)
{
	float3	vec;
	float		len;

	len = mv_length(a);
	if (len == 0)
		return (a);
	vec = mv_mult_num(a, 1 / len);
	return (vec);
}

float3	mv_inverse(const float3 a)
{
	float3	vec;

	vec.x = -a.x;
	vec.y = -a.y;
	vec.z = -a.z;
	return (vec);
}

float ft_mod2(float a, float b)
{
	if (b == 0)
		b = 0.001;
	return (a - ((int)(a / b)) * b);
}

float3 ft_mod(float3 a, float3 b)
{
	return ((float3){ft_mod2(a.x, b.x), ft_mod2(a.y, b.y), ft_mod2(a.z, b.z)});
}
#endif

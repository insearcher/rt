#include "rt_cl.h"

static inline float		ft_mod2(float a, float b)
{
	if (b == 0)
		b = 0.001;
	return (a - ((int)(a / b)) * b);
}

static inline float3	ft_mod(float3 a, float3 b)
{
	return ((float3){ft_mod2(a.x, b.x), ft_mod2(a.y, b.y), ft_mod2(a.z, b.z)});
}

static inline float3	repeatSDF(float3 pos, float3 c)
{
	return (ft_mod(pos, c) - c * 0.5f);
}

static inline float		sdf_sphere(float3 pos, float radius)
{
//	return sin(pow(((mv_length(posc) - radius)), 2)); fun
	return (fast_length(pos) - radius);
}

static inline float		sdf_box(float3 pos, float3 bounds)
{
	float3 d = fabs(pos) - bounds;
	return fast_length(fmax(d, 0.f)) + fmin(fmax(d.x, fmax(d.y, d.z)), 0);
}

static inline float		sdf_round_box(float3 pos, float3 bounds, float r)
{
	float3 d = fabs(pos) - bounds;
	return fast_length(fmax(d, 0.f)) - r + fmin(fmax(d.x, fmax(d.y, d.z)), 0);
}

static inline float		sdf_torus(float3 pos, float radius, float inner_radius)
{
	float2 q = (float2)(fast_length(pos.xz) - radius, pos.y);
	return fast_length(q) - inner_radius;
}

static inline float		sdf_capped_torus(float3 pos, float2 sc, float ra, float rb)
{
	pos.x = fabs(pos.x);
	float k = (sc.y * pos.x > sc.x * pos.y) ? dot(pos.xy, sc) : fast_length(pos.xy);
	return sqrt(dot(pos, pos) + ra * ra - 2.0f * ra * k) - rb;
}

static inline float		sdf_link(float3 pos, float le, float r1, float r2)
{
	float3 q = (float3)(pos.x, fmax(fabs(pos.y) - le, 0.0f), pos.z);
	return fast_length((float2)(fast_length(q.xy) - r1, q.z)) - r2;
}

static inline float		sdf_cylinder(float3 pos, float3 c)
{
	return fast_length(pos.xz - c.xy) - c.z;
}

static inline float		sdf_cone(float3 pos, float2 c)
{
	float q = fast_length(pos.xy);
	return dot(normalize(c), (float2)(q, pos.z));
}

static inline float		sdf_plane(float3 pos, float3 n, float d)
{
	return dot(pos, n) + d;
}

static inline float4	sphere_fold(float3 z, float dz, float fixedradius, float minradius)
{
	float r2 = dot(z,z);

	if (r2 < minradius)
	{
		float temp = (fixedradius / minradius);
		z *= temp;
		dz *= temp;
	}
	else if (r2 < fixedradius)
	{
		float temp =(fixedradius/r2);
		z *= temp;
		dz *= temp;
	}
	return ((float4){z.x, z.y, z.z, dz});
}

static inline float3	box_fold(float3 z, float3 cube_size)
{
	z.x = clamp(z.x, -cube_size.x, cube_size.x) * 2.0 - z.x;
	z.y = clamp(z.y, -cube_size.y, cube_size.y) * 2.0 - z.y;
	z.z = clamp(z.z, -cube_size.z, cube_size.z) * 2.0 - z.z;
	return (z);
}

static inline float		sdf_mandelbox(float3 pos, float scale, float fixedradius,
										 float minradius, float3 cube_size, int iter)
{
	float3 z = pos;
	float3 offset = z;
	float dr = 2.0f;
	for (int n = 0; n < iter; n++)
	{
		float4 tmp;
		z = box_fold(z, cube_size);
		tmp = sphere_fold(z, dr, fixedradius, minradius);
		z.x = tmp.x;
		z.y = tmp.y;
		z.z = tmp.z;
		dr = tmp.w;
		z= scale * z + offset;
		dr = dr * fabs(scale) + 1.0f;
	}
	float r = fast_length(z);
	return (r / fabs(dr));
}

static inline float		sdf_mandelbulb(float3 pos, float power, int iter, int breakout)
{
	float3 z = pos;
	float dr = 1;
	float r;

	for (int i = 0; i < iter; i++)
	{
		r = fast_length(z);
		if (r > breakout)
			break ;

		float theta = acos(z.z / r) * power;
		float phi = atan2(z.y, z.x) * power;
		float zr = pow(r, power);
		dr = pow(r, power - 1) * power * dr + 1;

		z = zr * (float3)(half_sin(theta) * half_cos(phi), half_sin(phi) * half_sin(theta), half_cos(theta));
		z += pos;
	}
	return ((0.5 * log(r) * r / dr));
}

static inline float		sdf_cross_box(float3 pos, float3 b)
{
	float da = sdf_box(pos.xyz,(float3)(10.0, 1.0, 1.0));
	float db = sdf_box(pos.yzx,(float3)(1.0, 10.0, 1.0));
	float dc = sdf_box(pos.zxy,(float3)(1.0, 1.0, 10.0));
	return min(da,min(db,dc));
}

//static inline float	sdf_menger(float3 pos, float3 b)
//{
//	float3 a;
//	float3 r;
//
//	float d = sdf_box(pos, (float3)(1.0));
//	float c = sdf_cross_box(pos * 3.f, b) / 3.f;
//	d = max( d, -c );
//	a = fmod(pos * 1.f, 2.f ) - 1.f;
//	r = 1.f - 1.f * fabs(a);
//	c = sdf_cross_box(r, b) / 9.f;
//	d = max( d, -c );
//	return (d);
//}

static inline float		sdf_menger_sponge(float3 pos, float3 offset, float scale, int iteration)
{
	float4 z = (float4)(pos, 2.f);
	for (int n = 0; n < iteration; n++)
	{
		z = fabs(z);
		if (z.x < z.y)
			z.xy = z.yx;
		if (z.x < z.z)
			z.xz = z.zx;
		if (z.y < z.z)
			z.yz = z.zy;
		z = z * scale;
		z.xyz -= offset * (scale - 1.f);
		if (z.z < -0.5f * offset.z * (scale - 1.f))
			z.z += offset.z * (scale - 1.f);
	}
	return (length(max(fabs(z.xyz) - (float3)(1.f),0.f)) - 0.05f) / z.w;
}

static inline float		sdf_octahedron(float3 pos, float s)
{
	pos = fabs(pos);
	return ((pos.x + pos.y + pos.z - s) * 0.57735027f);
}

static inline float		dot2(float3 v)
{
	return (dot(v, v));
}

float	sdf(float3 origin, float3 direction, __global t_object *obj, float3 *lp, int scene_params)
{
	float3	gright = (float3){1, 0, 0};
	float3	gup = (float3){0, 1, 0};
	float	distance = 0.0f;
	float3	local_pos;

	if (scene_params & RT_REPETITION)
		local_pos = repeatSDF(origin, obj->transform.pos);
	else
		local_pos = origin - obj->transform.pos;

	float3 cr = cross(gup, obj->transform.up);
	float cos = dot(gup, obj->transform.up);
	float sin = length(cr);
	float3 a = normalize(cr);
	if (fabs(a.x) < RM_FLT_EPSILON && fabs(a.y) < RM_FLT_EPSILON && fabs(a.z)< RM_FLT_EPSILON)
	{
		cr = cross(gright, obj->transform.right);
		cos = dot(gright, obj->transform.right);
		sin = length(cr);
		a = normalize(cr);
		if (fabs(a.x) < RM_FLT_EPSILON && fabs(a.y) < RM_FLT_EPSILON && fabs(a.z)< RM_FLT_EPSILON)
		{
			a = gup;
		}
	}
	float3 x = (float3)
			{
					cos + (1 - cos) * a.x * a.x, (1 - cos) * a.x * a.y - sin * a.z, (1 - cos) * a.x * a.z + sin * a.y
			};
	float3 y = (float3)
			{
					(1 - cos) * a.x * a.y + sin * a.z, cos + (1 - cos) * a.y * a.y, (1 - cos) * a.y * a.z - sin * a.x
			};
	float3 z = (float3)
			{
					(1 - cos) * a.x * a.z - sin * a.y, (1 - cos) * a.y * a.z + sin * a.x, cos + (1 - cos) * a.z * a.z
			};
	float3 new_local_pos = (float3)
			{
					dot(x, local_pos),
					dot(y, local_pos),
					dot(z, local_pos)
			};
	local_pos = new_local_pos;
	switch (obj->type)
	{
		case o_sphere:
			distance = sdf_sphere(local_pos, obj->params.sphere.radius);
			break;
		case o_box:
			distance = sdf_box(local_pos, obj->params.box.bounds);
			break;
		case o_round_box:
			distance = sdf_round_box(local_pos, obj->params.round_box.bounds, obj->params.round_box.r);
			break;
		case o_torus:
			distance = sdf_torus(local_pos, obj->params.torus.radius, obj->params.torus.inner_radius);
			break;
		case o_capped_torus:
			distance = sdf_capped_torus(local_pos, obj->params.capped_torus.sc, obj->params.capped_torus.ra, obj->params.capped_torus.rb);
			break;
		case o_link:
			distance = sdf_link(local_pos, obj->params.link.le, obj->params.link.r1, obj->params.link.r2);
			break;
		case o_cylinder:
			distance = sdf_cylinder(local_pos, obj->params.cylinder.params);
			break;
		case o_cone:
			distance = sdf_cone(local_pos, obj->params.cone.c);
			break;
		case o_plane:
			distance = sdf_plane(local_pos, obj->transform.up, obj->params.plane.distance);
			break;
		case o_mandelbulb:
			distance = sdf_mandelbulb(local_pos, obj->params.mandelbulb.power,
									  obj->params.mandelbulb.iteration, obj->params.mandelbulb.breakout);
			break;
		case o_mandelbox:
			distance = sdf_mandelbox(local_pos, obj->params.mandelbox.scale, obj->params.mandelbox.fixedradius,
									 obj->params.mandelbox.minradius, obj->params.mandelbox.cube_size,
									 obj->params.mandelbox.iteration);
			break;
		case o_menger_sponge:
			distance = sdf_menger_sponge(local_pos, obj->params.menger_sponge.offset,
										 obj->params.menger_sponge.scale, obj->params.menger_sponge.iteration);
			break;
		case o_octahedron:
			distance = sdf_octahedron(local_pos, obj->params.octahedron.bounds);
			break;
	}
	if (lp)
	{
		float3 new_direction = (float3){
				dot(x, direction),
				dot(y, direction),
				dot(z, direction)};
		*lp = new_local_pos + new_direction * distance;
	}
	return (distance);
}

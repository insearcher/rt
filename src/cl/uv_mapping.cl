#include "rt_cl.h"

static inline float2			uv_mapping_for_cube(t_raycast_hit rh)
{
	float3 point = rh.local_point;
	float3 normvec;
	float3 crossvec;
	float v;
	float u;

	if (rh.normal.x != 0.0f || rh.normal.y != 0.0f)
		normvec = normalize((float3) {rh.normal.y, -rh.normal.x, 0.0f});
	else if (1 - fabs(rh.normal.z) < RM_FLT_EPSILON)
		normvec = (float3) {0.0f, 1.0f, 0.0f};
	else if (1 - fabs(rh.normal.x)< RM_FLT_EPSILON)
		normvec = (float3) {0.0f, 0.0f, 1.0f};
	else if (1 - fabs(rh.normal.y) < RM_FLT_EPSILON)
		normvec = (float3) {1.0f, 0.0f, 0.0f};
	crossvec = cross(normvec, rh.normal);
	u = 0.5 - fmod(dot(normvec, point), 1.0f) / 2;
	v = 0.5 + fmod(dot(crossvec, point), 1.0f) / 2;
	return ((float2){u, v});
}

static inline float2			uv_mapping_for_plane(t_raycast_hit rh)
{
	float3 point = rh.point;
//	float3 normvec;
//	float3 crossvec;
	float v;
	float u;

//	if (rh.normal.x != 0.0f || rh.normal.y != 0.0f)
//		normvec = normalize((float3) {rh.normal.y, -rh.normal.x, 0.0f});
//	else
//		normvec = (float3) {0.0f, 0.0f, 1.0f};
//	u = 0.5 - fmod(dot(normvec, point), 1.0f) / 2;
//	v = 0.5 + fmod(dot(crossvec, point), 1.0f) / 2;
//	float3 t = rh.point;
	u = fmod(fabs(dot(rh.hit->transform.right, point)), 128.0f) / 128;
	v = fmod(fabs(dot(rh.hit->transform.forward, point)), 128.0f) / 128;
	if (point.x < 0 && point.y < 0)
	{
		u = 1 - u;
		v = 1 - v;
	}
	else if (point.x < 0)
		u = 1 - u;
	else if (point.y < 0)
		v = 1 - v;
	return ((float2){u, v});
}

static inline float2			uv_mapping_for_sphere(t_raycast_hit rh)
{
	float3 vec = normalize(rh.local_point);
	float u = 0.5f + (atan2(vec.z, vec.x) / TWO_PI);
	float v = 0.5f - (asin(vec.y) / PI);
	return ((float2){u, v});
}

static inline float2			uv_mapping_for_cylinder(t_raycast_hit rh)
{
	float3 vec = normalize(rh.local_point);
	float u = 0.5f + (atan2(vec.z, vec.x) / TWO_PI);
	float v = 0.5f + (modf(rh.local_point.y * 1000 / 1024, &v) / 2);
	return ((float2){u, v});
}

static inline float2			uv_mapping_for_torus(t_raycast_hit rh)
{
	float3	vec = rh.local_point;
	float	u = 0.5f + (atan2(vec.z, vec.x) / TWO_PI);
	float 	v = 0.5f - asin(vec.y / rh.hit->params.torus.inner_radius) / PI;
	return ((float2){u, v});
}
void	normalize_coord_for_texture(t_raycast_hit rh, float2 uv, float3 *color,
									__global int *texture, __global int *texture_w, __global int *texture_h,
									__global int *prev_texture_size)
{
	int coord;
	int coord_x;
	int coord_y;
	float tmp_division;

	rh.hit->material.offset.x = 0.f;
	rh.hit->material.offset.y = 0.f;
	if (rh.hit->material.offset.x + uv.x > 1.f && rh.hit->material.offset.x + uv.x <= 0.f)
		rh.hit->material.offset.x = 0.f;
	if (rh.hit->material.offset.y + uv.y > 1.f && rh.hit->material.offset.y + uv.y <= 0.f)
		rh.hit->material.offset.y = 0.f;
	coord_x = int((uv.x + rh.hit->material.offset.x) * texture_w[rh.hit->material.texture_id]);
	coord_y = int((uv.y + rh.hit->material.offset.y) * texture_h[rh.hit->material.texture_id]);
	coord_y *= (texture_w[rh.hit->material.texture_id]);
	coord = coord_x + coord_y;
	coord += prev_texture_size[rh.hit->material.texture_id];

	color->x = (RED(texture[coord]));
	color->y = (GREEN(texture[coord]));
	color->z = (BLUE(texture[coord]));
	tmp_division = 0.00392156862; // 1/255
	color->x *= tmp_division;
	color->y *= tmp_division;
	color->z *= tmp_division;
}

int		choose_texture_for_object(t_raycast_hit rh,  __global int *texture,
									 float3 *color, __global int *texture_w, __global int *texture_h, __global int *prev_texture_size)
{
	float2	uv;
	int 	found_texture_for_obj;

	uv = (float2){-1.f, -1.f};
	found_texture_for_obj = 1;
	if (rh.hit->material.texture_id == -1)
		return (found_texture_for_obj);
	if (rh.hit->type == o_sphere)
		uv = uv_mapping_for_sphere(rh);
	else if (rh.hit->type == o_cylinder)
		uv = uv_mapping_for_cylinder(rh);
	else if (rh.hit->type == o_plane)
		uv = uv_mapping_for_plane(rh);
	else if (rh.hit->type == o_torus)
		uv = uv_mapping_for_torus(rh);
	else if (rh.hit->type == o_box)
		uv = uv_mapping_for_cube(rh);
	if (uv.x != -1.f && uv.y != -1.f)
	{
		found_texture_for_obj = 0;
		normalize_coord_for_texture(rh, uv, color, texture, texture_w, texture_h, prev_texture_size);
		return (found_texture_for_obj);
	}
	return (found_texture_for_obj);
}

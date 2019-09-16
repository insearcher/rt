#include "rt_cl.h"

float2			uv_mapping_for_cube(t_raycast_hit rh)
{
	float3 point = rh.point;
	float3 normvec;
	float3 crossvec;
	float v;
	float u;

	if (rh.normal.x != 0.0f || rh.normal.y != 0.0f)
		normvec = normalize((float3) {rh.normal.y, -rh.normal.x, 0.0f});
	else if (rh.normal.z == 1)
		normvec = (float3) {0.0f, 1.0f, 0.0f};
	else if (rh.normal.x == 1)
		normvec = (float3) {0.0f, 0.0f, 1.0f};
	else if (rh.normal.y == 1)
		normvec = (float3) {1.0f, 0.0f, 0.0f};
	crossvec = cross(normvec, rh.normal);
	u = 0.5 + fmod(dot(normvec, point), 1.0f) / 2;
	v = 0.5 + fmod(dot(crossvec, point), 1.0f) / 2;
	return ((float2){u, v});
}

float2			uv_mapping_for_plane(t_raycast_hit rh)
{
	float3 point = rh.point;
	float3 normvec;
	float3 crossvec;
	float v;
	float u;

	if (rh.normal.x != 0.0f || rh.normal.y != 0.0f)
		normvec = normalize((float3) {rh.normal.y, -rh.normal.x, 0.0f});
	else
		normvec = (float3) {0.0f, 0.0f, 1.0f};
	crossvec = cross(normvec, rh.normal);
	u = 0.5 + fmod(dot(normvec, point), 1.0f) / 2;
	v = 0.5 + fmod(dot(crossvec, point), 1.0f) / 2;
	return ((float2){u, v});
}

float2			uv_mapping_for_sphere(t_raycast_hit rh)
{
	float3	point = rh.point;
	float3	obj_pos = rh.hit->transform.pos;
	float3	vec;
	float 	v;
	float 	u;

	vec = normalize(point - obj_pos);
	u = 0.5f + (atan2(vec.z, vec.x) / TWO_PI);
	v = 0.5f - (asin(vec.y) / PI);
	return ((float2){u, v});
}

float2			uv_mapping_for_cylinder(t_raycast_hit rh)
{
	float3	point = rh.point;
	float3	obj_pos = rh.hit->transform.pos;
	float3	vec;
	float 	v;
	float 	u;

	vec = normalize(point - obj_pos);
	u = 0.5f + (atan2(vec.z, vec.x) / TWO_PI);
	v = 0.5f + (modf(point.y * 1000 / 1024, &v) / 2);
	return ((float2){u, v});
}

float2			uv_mapping_for_torus(t_raycast_hit rh)
{
	float3	vec = rh.point - rh.hit->transform.pos;
	float	u = 0.5f + (atan2(vec.z, vec.x) / TWO_PI);
	float 	v = 0.5f - asin(vec.y / rh.hit->params.torus.inner_radius) / PI;
	return ((float2){u, v});
}

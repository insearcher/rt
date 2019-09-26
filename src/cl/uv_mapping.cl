#include "rt_cl.h"

float2			uv_mapping_for_cube(t_raycast_hit rh)
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

float2			uv_mapping_for_plane(t_raycast_hit rh)
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

float2			uv_mapping_for_sphere(t_raycast_hit rh)
{
	float3 vec = normalize(rh.local_point);
	float u = 0.5f + (atan2(vec.z, vec.x) / TWO_PI);
	float v = 0.5f - (asin(vec.y) / PI);
	return ((float2){u, v});
}

float2			uv_mapping_for_cylinder(t_raycast_hit rh)
{
	float3 vec = normalize(rh.local_point);
	float u = 0.5f + (atan2(vec.z, vec.x) / TWO_PI);
	float v = 0.5f + (modf(rh.local_point.y * 1000 / 1024, &v) / 2);
	return ((float2){u, v});
}

float2			uv_mapping_for_torus(t_raycast_hit rh)
{
	float3	vec = rh.local_point;
	float	u = 0.5f + (atan2(vec.z, vec.x) / TWO_PI);
	float 	v = 0.5f - asin(vec.y / rh.hit->params.torus.inner_radius) / PI;
	return ((float2){u, v});
}

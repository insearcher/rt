#include "rt_cl.h"
#include "color.h"

void	normalize_coord_for_texture(t_raycast_hit rh, float2 uv, float3 *color,
		__global int *texture, __global int *texture_w, __global int *texture_h,
		__global int *prev_texture_size)
{
	int coord;
	int coord_x;
	int coord_y;

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
	color->x /= 255;
	color->y /= 255;
	color->z /= 255;
}

int		choose_texture_for_object(t_raycast_hit rh,  __global int *texture,
		float3 *color, __global int *texture_w, __global int *texture_h, __global int *prev_texture_size)
{
	float2	uv;
	int 	found_texture_for_obj;

	uv = (float2){-1.f, -1.f};
	found_texture_for_obj = 1;
	if (rh.hit->type == o_sphere)
	{
		uv = uv_mapping_for_sphere(rh);
		rh.hit->material.texture_id = 0;
	}
	else if (rh.hit->type == o_cylinder)
	{
		uv = uv_mapping_for_cylinder(rh);
		rh.hit->material.texture_id = 3;
	}
	else if (rh.hit->type == o_plane)
	{
		uv = uv_mapping_for_plane(rh);
		rh.hit->material.texture_id = 1;
	}
	else if (rh.hit->type == o_torus)
	{
		uv = uv_mapping_for_torus(rh);
		rh.hit->material.texture_id = 3;
	}
	else if (rh.hit->type == o_box)
	{
		uv = uv_mapping_for_cube(rh);
		rh.hit->material.texture_id = 2;
	}
	if (uv.x != -1.f && uv.y != -1.f)
	{
		found_texture_for_obj = 0;
		normalize_coord_for_texture(rh, uv, color, texture, texture_w, texture_h, prev_texture_size);
		return (found_texture_for_obj);
	}
	return (found_texture_for_obj);
}

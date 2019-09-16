#include "rt_cl.h"
#include "color.h"

void	normalize_coord_for_texture(float2 uv, float3 *color,  __global int *texture)
{
	int coord = int(uv.x * 1024) + int(uv.y * 1024) * 1024;

	color->x = (RED(texture[coord]));
	color->y = (GREEN(texture[coord]));
	color->z = (BLUE(texture[coord]));
	color->x /= 255;
	color->y /= 255;
	color->z /= 255;
}

int		choose_texture_for_object(t_raycast_hit rh,  __global int *texture, float3 *color)
{
	float2	uv;
	int 	found_texture_for_obj;

	uv = (float2){-1.f, -1.f};
	found_texture_for_obj = 1;
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
		normalize_coord_for_texture(uv, color, texture);
		return (found_texture_for_obj);
	}
	return (found_texture_for_obj);
}

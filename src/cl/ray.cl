#include "config_cl.h"

float3  get_cam_ray(int x, int y, int width, int height, float3 camera_pos, float3 camera_local_x, float3 camera_local_y, float3 camera_local_z, float camera_min_distance, float camera_max_distance, float fov, float *mult)
{
	float3  canvas_cell;
//    float3  cam_ray;

    //TODO it's not used
    //float cell_x = x * camera_aspect_ratio / width;
    //float cell_y = y / (float)height;
	x -= width / 2;
    y -= height / 2;

    float focus = sqrt((float)width * width + height * height) / 2 / tan(fov * 3.1416f / 180 / 2);
    float fovx = atan(width / 2.0f / focus);
	float fovy = atan(height / 2.0f / focus);
	float maxx = tan(fovx) * focus;
	float maxy = tan(fovy) * focus;
	float kx = x * (maxx * 2 / width);
	float ky = y * (maxy * 2 / height);
	canvas_cell = camera_local_z * focus + camera_local_x * kx + camera_local_y * ky;
	*mult = length(canvas_cell) / length(camera_local_z * focus);
	return normalize(canvas_cell);
}
#include "config_cl.h"

float3  get_cam_ray(int x, int y, int width, int height, float3 camera_pos, float3 camera_local_x, float3 camera_local_y, float3 camera_local_z, float camera_min_distance, float camera_max_distance)
{
	float3  canvas_cell;
    float3  cam_ray;

    //TODO it's not used
    //float cell_x = x * camera_aspect_ratio / width;
    //float cell_y = y / (float)height;
	x -= width / 2;
    y -= height / 2;
    canvas_cell = (float3){
    	camera_pos.x + camera_local_z.x * camera_min_distance + 
    	camera_local_x.x * x + camera_local_y.x * y,
		camera_pos.y + camera_local_z.y * camera_min_distance + 
		camera_local_x.y * x + camera_local_y.y * y,
		camera_pos.z + camera_local_z.z * camera_min_distance + 
		camera_local_x.z * x + camera_local_y.z * y};
	cam_ray = mv_normalize(canvas_cell);
	return (cam_ray);
}

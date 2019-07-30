#include "config_cl.h"

float3  get_cam_ray(int x, int y, t_camera camera, int width, int height)
{
	float3  canvas_cell;
    float3  cam_ray;

    //TODO it's not used
    //float cell_x = x * camera.aspect_ratio / width;
    //float cell_y = y / (float)height;
	x -= width / 2;
    y -= height / 2;
    canvas_cell = (float3){
    	camera.pos.x + camera.local_z.x * camera.min_distance + 
    	camera.local_x.x * x + camera.local_y.x * y,
		camera.pos.y + camera.local_z.y * camera.min_distance + 
		camera.local_x.y * x + camera.local_y.y * y,
		camera.pos.z + camera.local_z.z * camera.min_distance + 
		camera.local_x.z * x + camera.local_y.z * y};
	cam_ray = mv_normalize(canvas_cell);
	return (cam_ray);
}

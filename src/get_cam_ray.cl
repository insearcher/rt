#include "config_cl.h"

t_vector3d  get_cam_ray(int x, int y, t_canvas canvas, int width, int height)
{
	t_vector3d  canvas_cell;
    t_vector3d  cam_ray;

	x -= width / 2;
    y -= height / 2;
	canvas_cell.x = x * canvas.width / width;
    canvas_cell.y = y * canvas.height / height;
    canvas_cell.z = canvas.min_distance;
	cam_ray = mv_normalize(canvas_cell);
    return (cam_ray);
}

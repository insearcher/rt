#ifndef RM_H
# define RM_H

#include "libui.h"

typedef struct	s_object3d
{
	int			type;
	t_vector3d	center;
	float		radius;
}				t_object3d;

typedef struct          s_canvas
{
	float               width;
	float               height;
	float               min_distance;
	float               max_distance;
	t_vector3d          camera;
}               t_canvas;

#endif

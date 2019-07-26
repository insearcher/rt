/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 22:28:53 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/24 22:28:56 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "rt.h"
#include "rt_camera.h"
#include "config.h"

static int	physics(void *a)
{
	t_ui_main	*m;

	m = (t_ui_main *)a;
	while (1)
	{
		move_camera(m);
		rotate_camera(m);
		SDL_Delay(5);
	}
}

void	setup_scene(t_conf *conf)
{
	t_object3d	*objects;

	conf->objects_num = 1;
	objects = (t_object3d *)malloc(sizeof(t_object3d) * conf->objects_num);
	objects[0].type = 1;
	objects[0].radius = .5f;
	objects[0].center = (t_vector3d){4.f, 4.f, 4.f};
	conf->objects = objects;
}

void	initialization_surface(t_ui_el *el, t_ui_win *w)
{
	el->sdl_surface = SDL_CreateRGBSurface(0, w->size.x, w->size.y, 32, 0, 0, 0, 0);
}

int main(void)
{
	t_conf conf;

    ui_sdl_init();
    t_ui_main *m = ui_main_init();
    conf.cl = cl_setup((char *[]){"src/render.cl", "src/ray_marching.cl",
					"src/get_cam_ray.cl", "utilits_cl/math_vec.cl",
					"utilits_cl/color.cl", NULL}, (char *[]){"render", NULL});
	setup_scene(&conf);
	setup_camera(&conf.camera);
	m->data = &conf;
    ui_main_add_function_by_id(m, ray_marching_render, "ray_marching_render");
    ui_jtoc_main_from_json(m, "json/main.json");
    t_ui_win *w = ui_main_find_window_by_id(m, 0);
    t_ui_el *el = ui_win_find_el_by_id(w, 1);
	initialization_surface(el, w);

	/// !!!
	conf.camera.local_x = (t_vector3d){1, 0, 0};
	conf.camera.local_y = (t_vector3d){0, 1, 0};
	conf.camera.local_z = (t_vector3d){0, 0, 1};

	conf.camera.velocity = (t_vector3d){0, 0, 0};
	conf.camera.speed = .025f;
	conf.camera.acc_time = .04f;

	SDL_Thread	*thread;
	thread = SDL_CreateThread(physics, "physics", (void *)m);
	SDL_DetachThread(thread);
	/// !!!

    ui_main_run_program(m);
	return 0;
}

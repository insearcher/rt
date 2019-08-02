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
#include "rt_input.h"
#include "rt_camera.h"
#include "config.h"

//TODO create full box primitive

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

	conf->objects_num = 2;
	objects = (t_object3d *)malloc(sizeof(t_object3d) * conf->objects_num);
	objects[0].type = 1;
	objects[0].radius = 1;
	objects[0].center = (cl_float3){{4.f, 4.f, 4.f}};
	objects[1].type = 1;
	objects[1].radius = 2;
	objects[1].center = (cl_float3){{10.f, 4.f, 4.f}};
	conf->objects = objects;
}

int main(void)
{
	t_conf conf;

    ui_sdl_init();
    t_ui_main *m = ui_main_init();
    conf.cl = cl_setup((char *[]){"src/cl/render.cl",
								  "src/cl/ray_marching.cl",
								  "src/cl/primitives_sdf.cl",
								  "src/cl/get_cam_ray.cl",
								  NULL}, (char *[]){"render", NULL});
	setup_scene(&conf);
//	setup_camera(&conf.camera);
	m->data = &conf;
    ui_main_add_function_by_id(m, ray_marching_render, "ray_marching_render");
    ui_jtoc_main_from_json(m, "json/main.json");
    t_ui_win *w = ui_main_find_window_by_id(m, 0);
    t_ui_el *el = ui_win_find_el_by_id(w, 1);

//	el->sdl_surface = SDL_CreateRGBSurface(0, w->size.x, w->size.y, 32, 0, 0, 0, 0);
	conf.texture = SDL_CreateTexture(el->sdl_renderer, SDL_PIXELFORMAT_RGB888,
													  SDL_TEXTUREACCESS_STREAMING, w->size.x, w->size.y);

	/// !!!
//	t_jnode *n = jtoc_read("json/camera.json");
//	t_camera *data = jtoc_get_raw_data(n);
//	if (data)
//		conf.camera = *data;
//	else
//		exit(1);
	ft_bzero(&conf.camera, sizeof(t_camera));
	conf.camera.clipping_planes = (t_clipping){.5f, 50};
	conf.camera.fov = 56;

	conf.camera.transform.pos = (cl_float3){{0, 0, 0}};
	conf.camera.transform.local.right = (cl_float3){{1, 0, 0}};
	conf.camera.transform.local.up = (cl_float3){{0, 1, 0}};
	conf.camera.transform.local.forward = (cl_float3){{0, 0, 1}};

	conf.camera.rb.move.speed = .025f;
	conf.camera.rb.move.speed_mult = 4;
	conf.camera.rb.move.acc = .04f;

	conf.camera.rb.rot.speed = 1;
	conf.camera.rb.rot.acc = .04f;

	conf.camera.rb.transform = &conf.camera.transform;
	SDL_Thread	*thread;
	thread = SDL_CreateThread(physics, "input", (void *)m);
	SDL_DetachThread(thread);
	/// !!!

	t_physics_system *ps = ps_init(ps_func);

	ps->rbs_count = 1;
	ps->rbs = (t_rb **)malloc(sizeof(t_rb *) * ps->rbs_count);
	ps->rbs[0] = &conf.camera.rb;

	ps_start(ps);

    ui_main_run_program(m);
	return 0;
}

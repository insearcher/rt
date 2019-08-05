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

#include <stdlib.h>
#include "rt.h"
#include "rt_input_system.h"
#include "rt_camera.h"
#include "config.h"

static void	transform_setup_default(t_transform *transform)
{
	transform->local.right = (cl_float3){{1, 0, 0}};
	transform->local.up = (cl_float3){{0, 1, 0}};
	transform->local.forward = (cl_float3){{0, 0, 1}};
}

int main(void)
{
	/// RT/CL SETUP !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	t_rt_main	*rt;
	t_ui_main	*ui;

	ui_sdl_init();
	ui = ui_main_init();
	rt = ft_memalloc(sizeof(t_rt_main));
	rt->cl = cl_setup((char *[]){
							"src/cl/render.cl",
							"src/cl/ray_marching.cl",
							"src/cl/sdf.cl",
							"src/cl/sdf/sphere.cl",
							"src/cl/sdf/box.cl",
							"src/cl/sdf/round_box.cl",
							"src/cl/sdf/torus.cl",
							"src/cl/sdf/cylinder.cl",
							"src/cl/get_cam_ray.cl",
							NULL},
							(char *[]){"render", NULL});
	rt->scenes = ft_x_memalloc(sizeof(t_scene));
//	rt->scenes[0].objects_count = 20;
//	rt->scenes[0].objects = ft_x_memalloc(sizeof(t_object) * rt->scenes[0].objects_count);
//	for (int i = 0; i < 20; i++)
//	{
//		rt->scenes[0].objects[i].type = box;
//		rt->scenes[0].objects[i].params.box.bounds = (cl_float3){{1, 1, 1}};
//	}
//	rt->scenes[0].objects[0].transform.pos = (cl_float3){{-1, 5, 0}};
//	rt->scenes[0].objects[1].transform.pos = (cl_float3){{1, 5, 0}};
//	rt->scenes[0].objects[2].transform.pos = (cl_float3){{3, 5, 0}};
//	rt->scenes[0].objects[3].transform.pos = (cl_float3){{-1, 3, 0}};
//	rt->scenes[0].objects[4].transform.pos = (cl_float3){{-1, 1, 0}};
//	rt->scenes[0].objects[5].transform.pos = (cl_float3){{1, 1, 0}};
//	rt->scenes[0].objects[6].transform.pos = (cl_float3){{3, 1, 0}};
//	rt->scenes[0].objects[7].transform.pos = (cl_float3){{9, 5, 0}};
//	rt->scenes[0].objects[8].transform.pos = (cl_float3){{9, 3, 0}};
//	rt->scenes[0].objects[9].transform.pos = (cl_float3){{9, 1, 0}};
//	rt->scenes[0].objects[10].transform.pos = (cl_float3){{11, 5, 0}};
//	rt->scenes[0].objects[11].transform.pos = (cl_float3){{11, 1, 0}};
//	rt->scenes[0].objects[12].transform.pos = (cl_float3){{13, 3, 0}};
//	rt->scenes[0].objects[13].transform.pos = (cl_float3){{17, 5, 0}};
//	rt->scenes[0].objects[14].transform.pos = (cl_float3){{17, 3, 0}};
//	rt->scenes[0].objects[15].transform.pos = (cl_float3){{17, 1, 0}};
//	rt->scenes[0].objects[16].transform.pos = (cl_float3){{17, 7, 0}};
//	rt->scenes[0].objects[17].transform.pos = (cl_float3){{19, 7, 0}};
//	rt->scenes[0].objects[18].transform.pos = (cl_float3){{19, 3, 0}};
//	rt->scenes[0].objects[19].transform.pos = (cl_float3){{21, 5, 0}};

//	rt->scenes[0].ambient = (cl_float3){{.03f,.04f,.1f}};
	rt->scenes[0].ambient = (cl_float3){{1,1,1}};

	rt->scenes[0].objects_count = 1;
	rt->scenes[0].objects = ft_x_memalloc(sizeof(t_object) * rt->scenes[0].objects_count);
	rt->scenes[0].objects[0].type = sphere;
	rt->scenes[0].objects[0].params.sphere.radius = 2;
	rt->scenes[0].objects[0].transform.pos = (cl_float3){{-1, 5, 0}};

	rt->scenes[0].lights_count = 1;
	rt->scenes[0].lights = ft_x_memalloc(sizeof(t_light) * rt->scenes[0].lights_count);
	rt->scenes[0].lights[0].transform.pos = (cl_float3){{1, 1, 1}};
	transform_setup_default(&rt->scenes[0].lights[0].transform);
	rt->scenes[0].lights[0].type = directional;
	rt->scenes[0].lights[0].params.directional.intensity = (cl_float3){{.1f, .1f, .1f}};

	ui->data = rt;
    ui_main_add_function_by_id(ui, rt_render, "rt_render");
    ui_jtoc_main_from_json(ui, "json/main.json");
    t_ui_win *w = ui_main_find_window_by_id(ui, 0);
    t_ui_el *el = ui_win_find_el_by_id(w, 1);

    SDL_Texture *t = SDL_CreateTexture(el->sdl_renderer, SDL_PIXELFORMAT_RGB888,
									 SDL_TEXTUREACCESS_STREAMING, w->size.x, w->size.y);
	t_list *l = ft_lstnew(NULL, 0);
	l->content = t;
	l->content_size = ft_strhash("default");
	ft_lstadd(&el->sdl_textures, l);

	/// CAMERA SETUP !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	ft_bzero(&rt->scenes[0].camera, sizeof(t_camera));
	rt->scenes[0].camera.clipping_planes = (t_clipping){1, 500};
	rt->scenes[0].camera.fov = 45;
	rt->scenes[0].camera.quality = 4;

	rt->scenes[0].camera.transform.pos = (cl_float3){{0, 0, 0}};
	rt->scenes[0].camera.transform.local.right = (cl_float3){{1, 0, 0}};
	rt->scenes[0].camera.transform.local.up = (cl_float3){{0, 1, 0}};
	rt->scenes[0].camera.transform.local.forward = (cl_float3){{0, 0, 1}};

	rt->scenes[0].camera.rb.move.speed = 1000;
	rt->scenes[0].camera.rb.move.speed_mult = 4;
	rt->scenes[0].camera.rb.move.acc = 0.025f;
	rt->scenes[0].camera.rb.move.vel = (cl_float3){{0, 0, 0}};
	rt->scenes[0].camera.rb.move.raw_vel = (cl_float3){{0, 0, 0}};

	rt->scenes[0].camera.rb.rot.speed = 100;
	rt->scenes[0].camera.rb.rot.acc = .04f;

	rt->scenes[0].camera.rb.transform = &rt->scenes[0].camera.transform;

	/// INPUT SYSTEM START !!!!!!!!!!!!!!!!!!!!!!!!!
	t_input_system		*is = ft_memalloc(sizeof(t_input_system));
	is->system.parent = is;
//	is->system.mutex = SDL_CreateMutex();
	is->state = ui->state;
	is->active = &rt->scenes[0].camera.rb;
	system_setup(&is->system, "input", is_func, 3);
	system_start(&is->system);

	/// PHYSICS SYSTEM START !!!!!!!!!!!!!!!!!!!!!!!!!
	t_physics_system	*ps = ft_memalloc(sizeof(t_physics_system));
//	ps->system.mutex = is->system.mutex;
	ps->system.parent = ps;
	ps->rbs_count = 1;
	ps->rbs = (t_rb **)malloc(sizeof(t_rb *) * ps->rbs_count);
	ps->rbs[0] = &rt->scenes[0].camera.rb;
	system_setup(&ps->system, "physics", &ps_func, 5);
	system_start(&ps->system);

    ui_main_run_program(ui);
	return 0;
}

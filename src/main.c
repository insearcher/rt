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
#include "rt_raycast.h"
#include "rt_input_system.h"


/*static void	transform_setup_default(t_transform *transform)
{
	transform->right = (cl_float3){{1, 0, 0}};
	transform->up = (cl_float3){{0, 1, 0}};
	transform->forward = (cl_float3){{0, 0, 1}};
}*/

cl_int2		modification_rt_elem_and_get_screen_size(t_ui_main *ui)
{
	t_ui_win	*w;
	t_ui_el		*el;
	SDL_Texture	*t;
	t_list		*lst;
	cl_int2		rt_screen_size;

	w = ui_main_find_window_by_id(ui, 0);
	el = ui_win_find_el_by_id(w, 1);
	t = SDL_CreateTexture(el->sdl_renderer, SDL_PIXELFORMAT_RGB888,
						  SDL_TEXTUREACCESS_STREAMING, el->rect.w, el->rect.h);
	lst = ft_lstnew(NULL, 0);
	lst->content = t;
	lst->content_size = ft_strhash("default");
	ft_lstadd(&el->sdl_textures, lst);
	rt_screen_size.x = el->rect.w;
	rt_screen_size.y = el->rect.h;
	return (rt_screen_size);
}

#ifdef APPLE___
int main()
{
	t_rt_main	*rt;
	t_ui_main	*ui;
	cl_int2		rt_screen_size;

	ui = ui_main_init();
	ui_sdl_init();
	ui_main_add_function_by_id(ui, rt_render, "rt_render");
	ui_main_fill_default_functions(ui);
	ui_jtoc_main_from_json(ui, "json/interface/main.json");

	rt_screen_size = modification_rt_elem_and_get_screen_size(ui);

	rt = setup_rt(rt_screen_size);
	ui->data = (void *)rt;

//OBJECTS
//	rt->scenes[0].objects_count = 4;
//	rt->scenes[0].objects = ft_x_memalloc(sizeof(t_object) * rt->scenes[0].objects_count);

//TODO NEEDED FOR PLANE (NOW PLANE IN JSON DOESN'T WORK CORRECTLY) (MAKSON WHAT IT TAKOE WOBSHE?)
//	t_transform *temp = &rt->scenes[0].objects[4].transform;
//	float d = -(temp->up.x * temp->pos.x + temp->up.y * temp->pos.y + temp->up.z * temp->pos.z);
//	rt->scenes[0].objects[4].params.plane.distance = fabs(d) / sqrt(temp->up.x * temp->up.x + temp->up.y * temp->up.y + temp->up.z * temp->up.z);

//	rt->scenes[0].objects[4].type = o_capped_torus;
//	rt->scenes[0].objects[4].layer = DEFAULT_LAYER;
//	rt->scenes[0].objects[4].params.capped_torus.sc = (cl_float2){{0.4f, 0.5f}};
//	rt->scenes[0].objects[4].params.capped_torus.ra = 1;
//	rt->scenes[0].objects[4].params.capped_torus.rb = 2;
//	rt->scenes[0].objects[4].transform.pos = (cl_float3){{0, 10, 40}};
//	rt->scenes[0].objects[4].transform.id = 6;
//	rt->scenes[0].objects[4].material.color = (cl_float4){{0, 1, 1, 1}};
//
//	rt->scenes[0].objects[5].type = o_link;
//	rt->scenes[0].objects[5].layer = DEFAULT_LAYER;
//	rt->scenes[0].objects[5].transform.pos = (cl_float3){{0, 10, 50}};
//	rt->scenes[0].objects[5].params.link.le = 3;
//	rt->scenes[0].objects[5].params.link.r1 = 2;
//	rt->scenes[0].objects[5].params.link.r2 = 1;
//	rt->scenes[0].objects[5].transform.id = 7;
//	rt->scenes[0].objects[5].material.color = (cl_float4){{0, 1, 1, 1}};
//
//	rt->scenes[0].objects[6].type = o_cylinder;
//	rt->scenes[0].objects[6].layer = DEFAULT_LAYER;
//	rt->scenes[0].objects[6].transform.pos = (cl_float3){{0, 10, 60}};
//	rt->scenes[0].objects[6].params.cylinder.params = (cl_float3){{1, 2, 3}};
//	rt->scenes[0].objects[6].transform.id = 8;
//	rt->scenes[0].objects[6].material.color = (cl_float4){{0, 1, 1, 1}};
//
//	rt->scenes[0].objects[7].type = o_cone;
//	rt->scenes[0].objects[7].layer = DEFAULT_LAYER;
//	rt->scenes[0].objects[7].transform.pos = (cl_float3){{0, 10, 70}};
//	rt->scenes[0].objects[7].params.cone.c = (cl_float2){{10, -1}};
//	rt->scenes[0].objects[7].transform.id = 9;
//	rt->scenes[0].objects[7].material.color = (cl_float4){{0, 1, 1, 1}};

/// PHYSICS SYSTEM START !!!!!!!!!!!!!!!!!!!!!!!!!
	t_physics_system	*ps = ft_memalloc(sizeof(t_physics_system));
	ps->system.parent = ps;
	ps->rbs_count = 2;
	ps->rbs = (t_rb *)malloc(sizeof(t_rb) * ps->rbs_count);

	ps->rbs[0].move.speed = 10000;
	ps->rbs[0].move.speed_mult = 4;
	ps->rbs[0].move.acc = 0.025f;
	ps->rbs[0].move.vel = (cl_float3){{0, 0, 0}};
	ps->rbs[0].move.raw_vel = (cl_float3){{0, 0, 0}};

	ps->rbs[0].rot.speed = 100000;
	ps->rbs[0].rot.acc = .04f;
	ps->rbs[0].rot.vel = (cl_float3){{0, 0, 0}};
	ps->rbs[0].rot.raw_vel = (cl_float3){{0, 0, 0}};

	ps->rbs[0].transform = &rt->scenes[0].camera.transform;

	ps->rbs[1].move.speed = 10000;
	ps->rbs[1].move.speed_mult = 4;
	ps->rbs[1].move.acc = 0.025f;
	ps->rbs[1].move.vel = (cl_float3){{0, 0, 0}};
	ps->rbs[1].move.raw_vel = (cl_float3){{0, 0, 0}};

	ps->rbs[1].rot.speed = 100000;
	ps->rbs[1].rot.acc = .04f;
	ps->rbs[1].rot.vel = (cl_float3){{1, 1, 0}};
	ps->rbs[1].rot.raw_vel = (cl_float3){{1, 1, 0}};

	ps->rbs[1].transform = &rt->scenes[0].objects[1].transform;

	system_setup(&ps->system, "physics", &ps_func, 5);
	ps->change_indicator = 1;
	system_start(&ps->system);

/// INPUT SYSTEM START !!!!!!!!!!!!!!!!!!!!!!!!!
	t_input_system		*is = ft_memalloc(sizeof(t_input_system));
	is->system.parent = is;
	is->state = ui->state;
	is->active = &ps->rbs[0];
	system_setup(&is->system, "input", is_func, 3);
	system_start(&is->system);

	rt->systems_count = 2;
	rt->systems = ft_memalloc(sizeof(t_system *) * rt->systems_count);
	rt->systems[0] = &(is->system);
	rt->systems[1] = &(ps->system);

	ui_event_add_listener(((t_ui_win *)(ui->windows->content))->events->on_pointer_left_button_pressed, rt_raycast);

	ui_main_run_program(ui);
	return 0;
}
#else
int SDL_main(int argc, char *argv[])
{
/// RT/CL SETUP !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	t_rt_main	*rt;
	t_ui_main	*ui;

	ui_sdl_init();
	ui = ui_main_init();
	rt = ft_memalloc(sizeof(t_rt_main));
/*	rt->cl = cl_setup((char *[]){
							  "src/cl/render.c",
							  "src/cl/raymarch.c",
							  "src/cl/sdf.c",
							  "src/cl/ray.c",
							  "src/cl/gauss_blur.c",
							  NULL},
					  (char *[]){"render_rm", "gauss_blur_x", "gauss_blur_y", NULL});*/
	rt->cl = cl_setup((char *[]){
							  "src/cl/render.c",
							  "src/cl/raymarch.c",
							  "src/cl/sdf.c",
							  "src/cl/ray.c",
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

	rt->scenes[0].ambient = (cl_float3){{.1f, .1f, .1f}};

	rt->scenes[0].objects_count = 4;
	rt->scenes[0].objects = ft_x_memalloc(sizeof(t_object) * rt->scenes[0].objects_count);

	rt->scenes[0].objects[0].type = o_sphere;
	transform_setup_default(&rt->scenes[0].objects[0].transform);
	rt->scenes[0].objects[0].layer = DEFAULT_LAYER;
	rt->scenes[0].objects[0].params.sphere.radius = 3;
	rt->scenes[0].objects[0].transform.pos = (cl_float3){{0, 10, 0}};
	rt->scenes[0].objects[0].transform.id = 2;
	rt->scenes[0].objects[0].material.color = (cl_float4){{0, 1, 1, 1}};

	rt->scenes[0].objects[1].type = o_box;
	transform_setup_default(&rt->scenes[0].objects[1].transform);
	rt->scenes[0].objects[1].layer = DEFAULT_LAYER;
	rt->scenes[0].objects[1].params.box.bounds = (cl_float3){{1, 2, 3}};
	rt->scenes[0].objects[1].transform.pos = (cl_float3){{0, 10, 10}};
	rt->scenes[0].objects[1].transform.id = 3;
	rt->scenes[0].objects[1].material.color = (cl_float4){{0, 1, 1, 1}};

	rt->scenes[0].objects[2].type = o_round_box;
	transform_setup_default(&rt->scenes[0].objects[2].transform);
	rt->scenes[0].objects[2].layer = DEFAULT_LAYER;
	rt->scenes[0].objects[2].params.round_box.bounds = (cl_float3){{1, 2, 3}};
	rt->scenes[0].objects[2].params.round_box.r = 1;
	rt->scenes[0].objects[2].transform.pos = (cl_float3){{0, 10, 20}};
	rt->scenes[0].objects[2].transform.id = 4;
	rt->scenes[0].objects[2].material.color = (cl_float4){{0, 1, 1, 1}};

	rt->scenes[0].objects[3].type = o_torus;
	transform_setup_default(&rt->scenes[0].objects[3].transform);
	rt->scenes[0].objects[3].layer = DEFAULT_LAYER;
	rt->scenes[0].objects[3].params.torus.params = (cl_float2){{2, 2}};
	rt->scenes[0].objects[3].transform.pos = (cl_float3){{0, 10, 30}};
	rt->scenes[0].objects[3].transform.id = 5;
	rt->scenes[0].objects[3].material.color = (cl_float4){{0, 1, 1, 1}};

//	rt->scenes[0].objects[4].type = o_plane;
//	transform_setup_default(&rt->scenes[0].objects[4].transform);
//	rt->scenes[0].objects[4].layer = IGNORE_RAYCAST_LAYER;
//	rt->scenes[0].objects[4].transform.pos = (cl_float3){{-5, -5, -5}};
//	t_transform *temp = &rt->scenes[0].objects[4].transform;
//	float d = -(temp->up.x * temp->pos.x + temp->up.y * temp->pos.y + temp->up.z * temp->pos.z);
//	rt->scenes[0].objects[4].params.plane.distance = fabs(d) / sqrt(temp->up.x * temp->up.x + temp->up.y * temp->up.y + temp->up.z * temp->up.z);
//	rt->scenes[0].objects[4].transform.id = 5;
//	rt->scenes[0].objects[4].material.color = (cl_float4){{1, 0, 0, 1}};

//	rt->scenes[0].objects[4].type = o_capped_torus;
//	rt->scenes[0].objects[4].layer = DEFAULT_LAYER;
//	rt->scenes[0].objects[4].params.capped_torus.sc = (cl_float2){{0.4f, 0.5f}};
//	rt->scenes[0].objects[4].params.capped_torus.ra = 1;
//	rt->scenes[0].objects[4].params.capped_torus.rb = 2;
//	rt->scenes[0].objects[4].transform.pos = (cl_float3){{0, 10, 40}};
//	rt->scenes[0].objects[4].transform.id = 6;
//	rt->scenes[0].objects[4].material.color = (cl_float4){{0, 1, 1, 1}};
//
//	rt->scenes[0].objects[5].type = o_link;
//	rt->scenes[0].objects[5].layer = DEFAULT_LAYER;
//	rt->scenes[0].objects[5].transform.pos = (cl_float3){{0, 10, 50}};
//	rt->scenes[0].objects[5].params.link.le = 3;
//	rt->scenes[0].objects[5].params.link.r1 = 2;
//	rt->scenes[0].objects[5].params.link.r2 = 1;
//	rt->scenes[0].objects[5].transform.id = 7;
//	rt->scenes[0].objects[5].material.color = (cl_float4){{0, 1, 1, 1}};
//
//	rt->scenes[0].objects[6].type = o_cylinder;
//	rt->scenes[0].objects[6].layer = DEFAULT_LAYER;
//	rt->scenes[0].objects[6].transform.pos = (cl_float3){{0, 10, 60}};
//	rt->scenes[0].objects[6].params.cylinder.params = (cl_float3){{1, 2, 3}};
//	rt->scenes[0].objects[6].transform.id = 8;
//	rt->scenes[0].objects[6].material.color = (cl_float4){{0, 1, 1, 1}};
//
//	rt->scenes[0].objects[7].type = o_cone;
//	rt->scenes[0].objects[7].layer = DEFAULT_LAYER;
//	rt->scenes[0].objects[7].transform.pos = (cl_float3){{0, 10, 70}};
//	rt->scenes[0].objects[7].params.cone.c = (cl_float2){{10, -1}};
//	rt->scenes[0].objects[7].transform.id = 9;
//	rt->scenes[0].objects[7].material.color = (cl_float4){{0, 1, 1, 1}};

// TODO when lights count > 1 strange shit happens
	rt->scenes[0].lights_count = 1;
	rt->scenes[0].lights = ft_x_memalloc(sizeof(t_light) * rt->scenes[0].lights_count);

	rt->scenes[0].lights[0].transform.pos = (cl_float3){{0, 0, 0}};
	transform_setup_default(&rt->scenes[0].lights[0].transform);
	rt->scenes[0].lights[0].transform.forward = (cl_float3){{0, -1, 0}};
	rt->scenes[0].lights[0].type = directional;
	rt->scenes[0].lights[0].params.directional.color = (cl_float3){{.4f, .4f, .4f}};

//	rt->scenes[0].lights[1].transform.pos = (cl_float3){{0, 0, 0}};
//	rt->scenes[0].lights[1].type = point;
//	rt->scenes[0].lights[1].params.point.color = (cl_float3){{.5f, 0, 0}};
//	rt->scenes[0].lights[1].params.point.distance = 100;

	ui->data = rt;
	ui_main_add_function_by_id(ui, rt_render, "rt_render");
	ui_jtoc_main_from_json(ui, "json/main.json");
	t_ui_win *w = ui_main_find_window_by_id(ui, 0);
	t_ui_el *el = ui_win_find_el_by_id(w, 1);

	SDL_Texture *t = SDL_CreateTexture(el->sdl_renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, w->size.x, w->size.y);
	t_list *l = ft_lstnew(NULL, 0);
	l->content = t;
	l->content_size = ft_strhash("default");
	ft_lstadd(&el->sdl_textures, l);

/// CAMERA SETUP !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	ft_bzero(&rt->scenes[0].camera, sizeof(t_camera));
	rt->scenes[0].camera.clipping_planes = (t_clipping){0.5f, 500};
	rt->scenes[0].camera.fov = 90;
	rt->scenes[0].camera.quality = 1;
	rt->scenes[0].camera.transform.id = 1;
	rt->scenes[0].camera.screen = (cl_int2){{el->rect.w, el->rect.h}};

	rt->scenes[0].camera.transform.pos = (cl_float3){{0, 0, 20}};
	rt->scenes[0].camera.transform.right = (cl_float3){{-1, 0, 0}};
	rt->scenes[0].camera.transform.up = (cl_float3){{0, 1, 0}};
	rt->scenes[0].camera.transform.forward = (cl_float3){{0, 0, -1}};

	rt->mutex = SDL_CreateMutex();
/// PHYSICS SYSTEM START !!!!!!!!!!!!!!!!!!!!!!!!!
	t_physics_system	*ps = ft_memalloc(sizeof(t_physics_system));
	ps->rt = rt;
	ps->system.parent = ps;
	ps->rbs_count = 2;
	ps->rbs = (t_rb *)malloc(sizeof(t_rb) * ps->rbs_count);

	ps->rbs[0].move.speed = 10000;
	ps->rbs[0].move.speed_mult = 4;
	ps->rbs[0].move.acc = 0.025f;
	ps->rbs[0].move.vel = (cl_float3){{0, 0, 0}};
	ps->rbs[0].move.raw_vel = (cl_float3){{0, 0, 0}};

	ps->rbs[0].rot.speed = 100000;
	ps->rbs[0].rot.acc = .04f;

	ps->rbs[0].transform = &rt->scenes[0].camera.transform;

	ps->rbs[1].move.speed = 10000;
	ps->rbs[1].move.speed_mult = 4;
	ps->rbs[1].move.acc = 0.025f;
	ps->rbs[1].move.vel = (cl_float3){{0, 0, 0}};
	ps->rbs[1].move.raw_vel = (cl_float3){{0, 0, 0}};

	ps->rbs[1].rot.speed = 100000;
	ps->rbs[1].rot.acc = .04f;
	ps->rbs[1].rot.vel = (cl_float3){{1, 1, 0}};
	ps->rbs[1].rot.raw_vel = (cl_float3){{1, 1, 0}};

	ps->rbs[1].transform = &rt->scenes[0].objects[1].transform;

	system_setup(&ps->system, "physics", &ps_func, 5);
	ps->change_indicator = 1;
	system_start(&ps->system);
	SDL_SetThreadPriority(SDL_THREAD_PRIORITY_HIGH);

/// INPUT SYSTEM START !!!!!!!!!!!!!!!!!!!!!!!!!
	t_input_system		*is = ft_memalloc(sizeof(t_input_system));
	is->rt = rt;
	is->system.parent = is;
	is->state = ui->state;
	is->active = &ps->rbs[0];
	system_setup(&is->system, "input", is_func, 3);
	system_start(&is->system);
	SDL_SetThreadPriority(SDL_THREAD_PRIORITY_HIGH);

	ps->system.delay = 50;
	is->system.delay = 50;
	rt->systems_count = 2;
	rt->systems = ft_memalloc(sizeof(t_system *) * rt->systems_count);
	rt->systems[0] = &is->system;
	rt->systems[1] = &ps->system;

	ui_event_add_listener(((t_ui_win *)(ui->windows->content))->events->on_pointer_left_button_pressed, rt_raycast);

	ui_main_run_program(ui);
	return 0;
}
#endif

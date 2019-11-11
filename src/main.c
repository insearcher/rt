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
#include <rt_jtoc.h>
#include "rt.h"
#include "rt_raycast.h"
#include "rt_input_system.h"

int	rt_free_gpu_mem(t_ui_main *m, void *a1)
{
	t_rt_main	*rt;

	(void)a1;
	rt = (t_rt_main *)m->data;
	clReleaseMemObject(rt->gpu_mem->cl_aux);
	clReleaseMemObject(rt->gpu_mem->cl_image);
	clReleaseMemObject(rt->gpu_mem->cl_prev_texture_size);
	clReleaseMemObject(rt->gpu_mem->cl_texture);
	clReleaseMemObject(rt->gpu_mem->cl_texture_h);
	clReleaseMemObject(rt->gpu_mem->cl_texture_w);
	return (1);
}

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

//static void	vec_test()
//{
//
//	t_vec v;
//	vec_setup(&v, 4, sizeof(long));
//	long a = 2;
//	vec_push_back(&v, &a);
//	for (size_t i = 0; i < v.capacity * v.cell_size * sizeof(long); ++i)
//	{
//		printf("%d", ((char *)v.storage)[i]);
//	}
//	printf("\n");
//	a = 3;
//	vec_push_back(&v, &a);
//	for (size_t i = 0; i < v.capacity * v.cell_size * sizeof(long); ++i)
//	{
//		printf("%d", ((char *)v.storage)[i]);
//	}
//	printf("\n");
//	a = 2;
//	vec_push_back(&v, &a);
//	for (size_t i = 0; i < v.capacity * v.cell_size * sizeof(long); ++i)
//	{
//		printf("%d", ((char *)v.storage)[i]);
//	}
//	printf("\n");
//	a = 3;
//	vec_push_back(&v, &a);
//	a = 4;
//	vec_push_back(&v, &a);
//	a = 5;
//	vec_push_back(&v, &a);
//	for (size_t i = 0; i < v.capacity * v.cell_size * sizeof(long); ++i)
//	{
//		printf("%d", ((char *)v.storage)[i]);
//	}
//	printf("\n");
//	SDL_Log("vec size = %zu, capacity = %zu", v.size, v.capacity);
//	SDL_Log("vec last = %ld", *((long *)vec_last(&v)));
//	for (size_t i = 0; i < v.size; ++i)
//	{
//		SDL_Log("%zu: %ld", i, *(long *)vec_at(&v, i));
//	}
//}

int main()
{
	t_rt_main	*rt;
	t_ui_main	*ui;
	cl_int2		rt_screen_size;

	ui = ui_main_init();
	ui_sdl_init();
	ui_main_add_function_by_id(ui, rt_render, "rt_render");
	ui_main_add_function_by_id(ui, rt_free_gpu_mem, "rt_free_gpu_mem");
	ui_main_fill_default_functions(ui);
	ui_jtoc_main_from_json(ui, "json/interface/main.json");

	rt_screen_size = modification_rt_elem_and_get_screen_size(ui);

	rt = rt_setup(rt_screen_size, "json/textures.json", "json/scenes/scene2/mandelbulb.json");
	ui->data = (void *)rt;
//	rt->params |= RT_GAUSS_BLUR;
//	rt->scene->params |= RT_PATH_TRACE;
//	rt->scene->params |= RT_PHONG;


//TODO NEEDED FOR PLANE (NOW PLANE IN JSON DOESN'T WORK CORRECTLY) (MAKSON WHAT IT TAKOE WOBSHE?)
//	t_transform *temp = &rt->scene[0].objects[4].transform;
//	float d = -(temp->up.x * temp->pos.x + temp->up.y * temp->pos.y + temp->up.z * temp->pos.z);
//	rt->scene[0].objects[4].params.plane.distance = fabs(d) / sqrt(temp->up.x * temp->up.x + temp->up.y * temp->up.y + temp->up.z * temp->up.z);

//TODO CONE IS STRANGE

//TODO CYLINDER PARAMS X AND Y ARE USELESS (IT'S Z AND X OFFSET, BUT WE HAVE TRANSFORM)

//TODO	capped torus doesn't work correctly
//	rt->scene[0].objects[4].type = o_capped_torus;
//	rt->scene[0].objects[4].layer = DEFAULT_LAYER;
//	rt->scene[0].objects[4].params.capped_torus.sc = (cl_float2){{0.4f, 0.5f}};
//	rt->scene[0].objects[4].params.capped_torus.ra = 1;
//	rt->scene[0].objects[4].params.capped_torus.rb = 2;
//	rt->scene[0].objects[4].transform.pos = (cl_float3){{0, 10, 40}};
//	rt->scene[0].objects[4].transform.id = 6;
//	rt->scene[0].objects[4].material.color = (cl_float4){{0, 1, 1, 1}};

/// PHYSICS SYSTEM START !!!!!!!!!!!!!!!!!!!!!!!!!

//	rt->scenes[0].objects[0].params.mandelbumb.power = 2;

	t_physics_system	*ps = ft_memalloc(sizeof(t_physics_system));
	if (rt_jtoc_ps_setup(rt->scene, ps, "json/default_ps.json"))
		exit(0);
//	ps->rbs_count = 1;
//	ps->rbs = (t_rb *)malloc(sizeof(t_rb) * ps->rbs_count);

//	ps->rbs[0].move.speed = 10000;
//	ps->rbs[0].move.speed_mult = 4;
//	ps->rbs[0].move.braking_coef = 0.025f;
//	ps->rbs[0].move.vel = (cl_float3){{0, 0, 0}};
//	ps->rbs[0].move.raw_vel = (cl_float3){{0, 0, 0}};
//
//	ps->rbs[0].rot.speed = 100000;
//	ps->rbs[0].rot.braking_coef = .04f;
//	ps->rbs[0].rot.vel = (cl_float3){{0, 0, 0}};
//	ps->rbs[0].rot.raw_vel = (cl_float3){{0, 0, 0}};
//	ps->rbs[0].transform = rt_find_transform_by_id(rt->scene, 1);

/*	t_object *objs = rt->scene->objects;
	objs[0].material.luminosity = (cl_float3){{.0f, .0f, 0.f}};
	objs[1].material.luminosity = (cl_float3){{.0f, .0f, 0.f}};
	objs[2].material.luminosity = (cl_float3){{.0f, .0f, 0.f}};
	objs[3].material.luminosity = (cl_float3){{.0f, .0f, 0.f}};
	objs[4].material.luminosity = (cl_float3){{1.f, 1.f, 1.f}};*/

//
// mandelbumb
//	ps->rbs[1].move.speed = 10000;
//	ps->rbs[1].move.speed_mult = 4;
//	ps->rbs[1].move.acc = 0.025f;
//	ps->rbs[1].move.vel = (cl_float3){{0, 0, 0}};
//	ps->rbs[1].move.raw_vel = (cl_float3){{0, 0, 0}};
//
//	ps->rbs[1].rot.speed = 100000;
//	ps->rbs[1].rot.acc = .04f;
//	ps->rbs[1].rot.vel = (cl_float3){{0, 0, 1}};
//	ps->rbs[1].rot.raw_vel = (cl_float3){{0, 0, 1}};
//
//	ps->rbs[1].transform = &rt->scenes[0].objects[0].transform;
//
/*	ps->rbs[1].move.speed = 10000;
	ps->rbs[1].move.speed_mult = 4;
	ps->rbs[1].move.braking_coef = 0.025f;
	ps->rbs[1].move.vel = (cl_float3){{0, 0, 0}};
	ps->rbs[1].move.raw_vel = (cl_float3){{0, 0, 0}};

	ps->rbs[1].rot.speed = 100000;
	ps->rbs[1].rot.braking_coef = .04f;
	ps->rbs[1].rot.vel = (cl_float3){{1, 0, 1}};
	ps->rbs[1].rot.raw_vel = (cl_float3){{1, 0, 1}};
	ps->rbs[1].transform = rt_find_transform_by_id(rt->scene, 2);


	ps->rbs[2].move.speed = 10000;
	ps->rbs[2].move.speed_mult = 4;
	ps->rbs[2].move.braking_coef = 0.025f;
	ps->rbs[2].move.vel = (cl_float3){{0, 0, 0}};
	ps->rbs[2].move.raw_vel = (cl_float3){{0, 0, 0}};

	ps->rbs[2].rot.speed = 150000;
	ps->rbs[2].rot.braking_coef = .04f;
	ps->rbs[2].rot.vel = (cl_float3){{1, 0, 1}};
	ps->rbs[2].rot.raw_vel = (cl_float3){{0, 1, 1}};
	ps->rbs[2].transform = rt_find_transform_by_id(rt->scene, 3);


	ps->rbs[3].move.speed = 10000;
	ps->rbs[3].move.speed_mult = 4;
	ps->rbs[3].move.braking_coef = 0.025f;
	ps->rbs[3].move.vel = (cl_float3){{0, 0, 0}};
	ps->rbs[3].move.raw_vel = (cl_float3){{0, 0, 0}};

	ps->rbs[3].rot.speed =  200000;
	ps->rbs[3].rot.braking_coef = .04f;
	ps->rbs[3].rot.vel = (cl_float3){{1, 0, 1}};
	ps->rbs[3].rot.raw_vel = (cl_float3){{1, 1, 1}};
	ps->rbs[3].transform = rt_find_transform_by_id(rt->scene, 4);

	ps->rbs[4].move.speed = 100000;
	ps->rbs[4].move.speed_mult = 4;
	ps->rbs[4].move.braking_coef = 0.025f;
	ps->rbs[4].move.vel = (cl_float3){{0, 0, 0}};
	ps->rbs[4].move.raw_vel = (cl_float3){{0, 0, 0}};

	ps->rbs[4].rot.speed =  200000;
	ps->rbs[4].rot.braking_coef = .04f;
	ps->rbs[4].rot.vel = (cl_float3){{1, 1, 1}};
	ps->rbs[4].rot.raw_vel = (cl_float3){{1, 1, 1}};
	ps->rbs[4].transform = rt_find_transform_by_id(rt->scene, 5);*/

	system_setup(&ps->system, "physics", &ps_func, 5);
	ps->change_indicator = 1;
	system_start(&ps->system);

/// INPUT SYSTEM START !!!!!!!!!!!!!!!!!!!!!!!!!
	t_input_system		*is = ft_memalloc(sizeof(t_input_system));
	is->system.parent = is;
	is->state = ui->state;
	is->active = vec_at(&ps->rbs, 0);
	system_setup(&is->system, "input", is_func, 3);
	system_start(&is->system);

	rt->systems_count = 2;
	rt->systems = ft_memalloc(sizeof(t_system *) * rt->systems_count);
	rt->systems[0] = &(is->system);
	rt->systems[1] = &(ps->system);

	ui_event_add_listener(((t_ui_win *)(ui->windows->content))->events->on_pointer_left_button_pressed, rt_raycast);

	SDL_Log("%d", rt->scene->params);

	((t_object *)rt->scene->objects->storage)->material.luminosity.x = 0.0f;
	((t_object *)rt->scene->objects->storage)->material.luminosity.y = 0.0f;
	((t_object *)rt->scene->objects->storage)->material.luminosity.z = 0.0f;

	SDL_Log("%f", ((t_object *)rt->scene->objects->storage)->material.luminosity.x);
	SDL_Log("%f", ((t_object *)rt->scene->objects->storage)->material.luminosity.y);
	SDL_Log("%f", ((t_object *)rt->scene->objects->storage)->material.luminosity.z);
	ui_main_run_program(ui);
	return 0;
}

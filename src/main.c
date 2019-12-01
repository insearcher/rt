/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 22:28:53 by sbecker           #+#    #+#             */
/*   Updated: 2019/12/01 17:08:27 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <rt_jtoc.h>
#include "rt.h"
#include "rt_input_system.h"
#include "interface.h"

int					rt_free_gpu_mem(t_ui_main *m, void *a1)
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

static void			setup_systems(t_rt_main *rt, t_ui_main *ui)
{
	t_physics_system	*ps = ft_memalloc(sizeof(t_physics_system));
	if (rt_jtoc_ps_setup(rt->scene, ps, "json/scenes/mandelbox_scene/ps.json"))
	{
		rt_jtoc_sdl_log_error("PATH PS ERROR OR NOT FOUND", -1);
		exit (0);
	}

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
}

static cl_int2		modification_rt_elem_and_get_screen_size(t_ui_main *ui)
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

int main()
{
	t_rt_main	*rt;
	t_ui_main	*ui;
	cl_int2		rt_screen_size;

	ui = ui_main_init();
	ui_sdl_init();
	ui_main_add_function_by_id(ui, rt_render, "rt_render");
	ui_main_add_function_by_id(ui, rt_free_gpu_mem, "rt_free_gpu_mem");
	rt_uix_interface_setup(ui, "json/interface/main.json");
	rt_screen_size = modification_rt_elem_and_get_screen_size(ui);
	rt = rt_setup(rt_screen_size, "json/textures.json", "json/scenes/test1_scene/test1.json");
	ui->data = (void *)rt;
	rt_uix_scene_setup(ui);
	setup_systems(rt, ui);
	ui_main_run_program(ui);
	return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uix_fill_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 18:49:42 by sbednar           #+#    #+#             */
/*   Updated: 2019/09/28 18:49:45 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

static t_ui_el	*create_tmp_el(t_ui_win *win, t_ui_el *obj_menu, size_t l_id)
{
	t_ui_el		*tmp_el;

	tmp_el = ui_el_init();
	ui_el_setup_default(tmp_el);
	ui_el_setup_default_scroll_menu_elem(tmp_el);
	ui_el_add_child(obj_menu, tmp_el);
	tmp_el->id = obj_menu->id * 10 + (Uint32)l_id;
	ui_el_set_new_pos(tmp_el, 0, 0,
					  (t_fvec2){0.01, 0.01
									 + 0.1f * (float)l_id});
	ui_el_set_size(tmp_el, 0, (t_fvec2){0.98, 0.09});
	tmp_el->sdl_renderer = win->sdl_renderer;
	ui_el_add_color_texture(tmp_el, (t_vec2){350, 80},0x606060, "default");
	ui_el_add_color_texture(tmp_el, (t_vec2){350, 80}, 0x450010, "selected");
	ui_el_add_color_texture(tmp_el, (t_vec2){350, 80}, 0xA0A0A0, "highlighted");
	ui_event_add_listener(tmp_el->events->on_pointer_left_button_pressed,
			rt_uix_button_choose);
	ui_event_add_listener(tmp_el->events->on_pointer_enter,
			rt_uix_on_button_enter);
	ui_event_add_listener(tmp_el->events->on_pointer_left_button_pressed,
			rt_uix_choose_obj_from_scene);
	ui_event_add_listener(tmp_el->events->on_pointer_exit,
			rt_uix_on_button_exit);
	return (tmp_el);
}

static void		process(t_ui_el *p, t_ui_main *m)
{
	t_ui_el	*el;

	el = ui_el_init();
	ui_el_setup_default(el);
	el->params |= EL_IGNOR_RAYCAST | EL_IS_DEPENDENT;
	ui_el_add_child(p, el);
	ui_el_set_pos(el, 0, (t_fvec2){0.0, 0.1});
	ui_el_set_size(el, 0, (t_fvec2){0.2, 0.7});
	el->id = p->id * 10;
	ui_el_set_text(el, ui_main_get_font_by_id(m, "Diablo"),
				   (t_text_params){(t_color){255, 255, 255, 0}, (t_color){0, 0, 0, 0},
								   0, TEXT_IS_REGULAR, TEXT_IS_SOLID});
	ui_el_update_text(el, ((t_object *)p->data)->local_name);
}

void			fill_scene(t_ui_main *ui, t_ui_el *obj_menu)
{
	t_ui_el		*tmp_el;
	t_ui_win	*uix_w;
	t_scene		*scene;
	size_t	i;

	scene = ((t_rt_main *)ui->data)->scene;
	uix_w = ui_main_find_window_by_id(ui, 1);
	i = -1;
	while (++i < scene->objects->size)
	{
		tmp_el = create_tmp_el(uix_w, obj_menu, i);
		tmp_el->data = (void *)(scene->objects->storage + i * scene->objects->cell_size);
		process(tmp_el, ui);
	}
}
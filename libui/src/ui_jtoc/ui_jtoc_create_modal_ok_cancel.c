/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_jtoc_create_modal_ok_cancel.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 16:16:08 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/15 14:36:43 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static void	create_ok_cancel_button(t_ui_el *p, t_ui_text *ui_text, t_ui_win *w)
{
	t_ui_el	*el;
	t_ui_el	*el_text;

	el = ui_el_init();
	el->id = 2;
	ui_el_add_child(p, el);
	ui_el_set_pos(el, PIXEL, (t_fvec2){0.5 * p->rect.w - 100, p->rect.h - 90});
	ui_el_set_size(el, PIXEL, (t_fvec2){200, 65});
	ui_el_add_color_texture(el, (t_vec2){el->rect.w, el->rect.h},
			ft_atoi_base("AAAAAA", 16), "default");
	ui_el_setup_default(el);
	el->modal_win = w;
	ui_event_add_listener(el->events->on_pointer_left_button_pressed,
		ui_el_event_close_window);
	el_text = ui_el_init();
	el_text->id = 3;
	ui_el_add_child(el, el_text);
	ui_el_set_pos(el_text, 0, (t_fvec2){0.3, 0});
	ui_el_set_size(el_text, 0, (t_fvec2){0.4, 1});
	ui_el_set_text(el_text, ui_text->font, (t_text_params){(SDL_Color){0, 0, 0,
		0}, (SDL_Color){0, 0, 0, 0}, 0, 0, TEXT_IS_BLENDED});
	ui_el_update_text(el_text, "OK");
	ui_el_setup_default(el_text);
	el_text->params |= EL_IGNOR_RAYCAST;
}

static void	fill_modal_ok_cancel(t_ui_text *ui_text, t_ui_el *p, char **text,
				t_ui_win *w)
{
	t_ui_el	*el;
	int		i;
	float	y;

	i = 0;
	y = 10;
	create_ok_cancel_button(p, ui_text, w);
	while (text[i])
	{
		el = ui_el_init();
		el->id = i + 5;
		el->params |= EL_IS_DEPENDENT;
		ui_el_add_child(p, el);
		ui_el_set_pos(el, PIXEL, (t_fvec2){150, y});
		ui_el_set_size(el, PIXEL, (t_fvec2){p->rect.w - 150, 40});
		y += 40 + 5;
		ui_el_set_text(el, ui_text->font,
			(t_text_params){(SDL_Color){0, 0, 0, 0}, (SDL_Color){170, 170, 170,
			0}, 0, TEXT_IS_REGULAR | ui_text->params, TEXT_IS_SOLID});
		ui_el_update_text(el, text[i]);
		ui_el_setup_default(el);
		i++;
	}
}

void		ui_jtoc_create_modal_ok_cancel(t_ui_main *m, t_ui_win *w,
				t_ui_text *ui_text)
{
	char	**text;
	size_t	num_strs;
	t_ui_el	*win_el;

	text = ft_strsplit_on_size(ui_text->text, ui_text->string_len, &num_strs);
	w->size.x = 300 + ui_text->string_len * 16;
	w->size.y = num_strs * 45 + 120;
	free(ui_text->text);
	ui_event_add_listener(w->events->on_close, ui_main_event_close_window);
	ui_event_add_listener(w->events->on_key_down[SDL_SCANCODE_ESCAPE],
		ui_main_event_close_window);
	ui_win_setup_default(w);
	ui_win_create(w, SDL_WINDOW_SHOWN);
	w->params |= WIN_IS_HIDDEN;
	win_el = ui_el_init();
	win_el->id = 1;
	ui_el_setup_default(win_el);
	ui_el_add_child(w->canvas, win_el);
	ui_el_set_pos(win_el, 0, (t_fvec2){0, 0});
	ui_el_set_size(win_el, 0, (t_fvec2){1, 1});
	ui_el_add_color_texture(win_el, (t_vec2){win_el->rect.w, win_el->rect.h},
			ft_atoi_base("757575", 16), "default");
	fill_modal_ok_cancel(ui_text, win_el, text, w);
	ui_main_add_window(m, w);
}

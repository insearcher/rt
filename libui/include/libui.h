/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <edraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 19:09:04 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/15 18:53:36 by edraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBUI_H
# define LIBUI_H

# include <SDL.h>
# include <SDL_ttf.h>
# include <SDL_image.h>
# include <math.h>
# include "libft.h"
# include "libjtoc.h"

# define DEBUG_STATUS		0

# define KNRM				"\x1B[0m"
# define KRED				"\x1B[31m"
# define KGRN				"\x1B[32m"
# define KYEL				"\x1B[33m"
# define KBLU				"\x1B[34m"
# define KMAG				"\x1B[35m"
# define KCYN				"\x1B[36m"
# define KWHT				"\x1B[37m"

# define KEYS_COUNT			285

# define CAST_X_TO_Y(x, y)	((y)x)

# define SCROLL_SPEED		20

/*
** el params
*/
# define EL_IGNOR_RAYCAST	(1 << 0)
# define EL_IS_HIDDEN		(1 << 1)
# define EL_IS_PTR_INSIDE	(1 << 2)
# define EL_IS_SCROLLABLE	(1 << 3)
# define EL_IS_DEPENDENT	(1 << 4)
# define EL_IS_TEXT			(1 << 5)
# define EL_MODAL_OK		(1 << 6)
# define EL_MODAL_OK_CANCEL	(1 << 7)
# define EL_IS_ICON			(1 << 8)

/*
** text params
*/
# define TEXT_IS_CENTERED	(1 << 0)
# define TEXT_IS_INPUTTING	(1 << 1)
# define TEXT_IS_REGULAR	(1 << 2)

/*
** text render_params
*/
# define TEXT_IS_SOLID		(1 << 0)
# define TEXT_IS_SHADED		(1 << 1)
# define TEXT_IS_BLENDED	(1 << 2)

/*
** main events/params
*/
# define MAIN_LMB_PRESSED	(1 << 0)
# define MAIN_RMB_PRESSED	(1 << 1)
# define MAIN_SCROLL_UP		(1 << 2)
# define MAIN_SCROLL_DOWN	(1 << 3)
# define MAIN_LMB_RELEASED	(1 << 4)
# define MAIN_LMB_HOLD		(1 << 5)
# define MAIN_RMB_RELEASED	(1 << 6)
# define MAIN_RMB_HOLD		(1 << 7)
# define MAIN_ON_QUIT		(1 << 8)

/*
** win params
*/
# define WIN_RESIZABLE		(1 << 0)
# define WIN_IS_SHOWN		(1 << 1)
# define WIN_IS_HIDDEN		(1 << 2)

/*
** img types
*/
# define IMG_TYPE_PNG		0
# define IMG_TYPE_JPG		1

/*
** for set/chage pos/size
*/
# define ABS				(1 << 0)
# define PIXEL				(1 << 1)

/*
** choto dlya tekstur
*/
# define RGBA8888			373694468
# define BLEND				1
# define NONE				0
# define STATIC				0

# define WIN_CENTER			SDL_WINDOWPOS_CENTERED

typedef	void				(*t_func_ptr)(void *, void *);
typedef	int					(*t_pred_ptr)(void *, void *);
typedef	t_list				t_queue;
typedef	SDL_Rect			t_rect;
typedef	SDL_Texture			t_texture;
typedef	t_list				t_list_texture;
typedef	SDL_Renderer		t_renderer;
typedef	SDL_Color			t_color;
typedef	SDL_Surface			t_sur;

/*
** Smart things:
** 1) It's possible to replace t_name_init just by ft_bzero in code;
** ...To be continued...
*/

typedef struct				s_frect
{
	float					x;
	float					y;
	float					w;
	float					h;
}							t_frect;

typedef struct				s_ui_event
{
	t_list					*events;
}							t_ui_event;

typedef struct				s_ui_text
{
	TTF_Font				*font;
	SDL_Color				text_color;
	SDL_Color				bg_color;
	char					*text;
	size_t					string_len;
	size_t					cursor_pos;
	Uint32					render_param;
	Uint32					params;
}							t_ui_text;

typedef struct				s_ui_el_events
{
	t_ui_event				*on_pointer_enter;
	t_ui_event				*on_pointer_stay;
	t_ui_event				*on_pointer_exit;
	t_ui_event				*on_pointer_left_button_pressed;
	t_ui_event				*on_pointer_left_button_hold;
	t_ui_event				*on_pointer_left_button_released;
	t_ui_event				*on_pointer_right_button_pressed;
	t_ui_event				*on_pointer_right_button_hold;
	t_ui_event				*on_pointer_right_button_released;
	t_ui_event				*on_scroll_up;
	t_ui_event				*on_scroll_down;
	t_ui_event				*on_render;
	t_ui_event				*on_resize;
}							t_ui_el_events;

struct s_ui_win;

typedef struct				s_ui_el
{
	SDL_Surface				*sdl_surface;
	t_list					*sdl_textures;
	SDL_Renderer			*sdl_renderer;
	struct s_ui_el			*parent;
	t_list					*children;
	size_t					current_texture;
	t_rect					rect;
	t_rect					crect;
	t_frect					rrect;
	t_vec2					ptr_rel_pos;
	Uint32					id;
	Uint32					params;
	t_ui_text				*text_area;
	struct s_ui_win			*modal_win;
	t_ui_el_events			*events;
	void					*data;
}							t_ui_el;

typedef struct				s_cursor
{
	SDL_Surface				*s;
	int						hot_x;
	int						hot_y;
}							t_cursor;

typedef struct				s_ui_win_events
{
	t_ui_event				*on_pointer_moved;
	t_ui_event				*on_pointer_enter;
	t_ui_event				*on_pointer_exit;
	t_ui_event				*on_pointer_left_button_pressed;
	t_ui_event				*on_pointer_left_button_released;
	t_ui_event				*on_pointer_right_button_pressed;
	t_ui_event				*on_pointer_right_button_released;
	t_ui_event				*on_scroll_up;
	t_ui_event				*on_scroll_down;
	t_ui_event				*on_focus_gained;
	t_ui_event				*on_focus_lost;
	t_ui_event				*on_resize;
	t_ui_event				*on_close;
	t_ui_event				*on_moved;
	t_ui_event				**on_key_down;
	t_ui_event				**on_key_up;
}							t_ui_win_events;

typedef struct				s_ui_win
{
	SDL_Window				*sdl_window;
	SDL_Renderer			*sdl_renderer;
	Uint32					sdl_window_id;
	char					*title;
	t_vec2					size;
	t_vec2					pos;
	t_ui_el					*canvas;
	t_ui_win_events			*events;
	Uint32					id;
	Uint32					params;
}							t_ui_win;

typedef struct				s_ui_raycaster
{
	t_ui_win				*focused_win;
	t_ui_el					*selected;
}							t_ui_raycaster;

typedef struct				s_ui_main
{
	t_list					*windows;
	SDL_Event				*sdl_event;
	SDL_mutex				*mutex;
	t_ui_raycaster			*raycaster;
	t_list					*sdl_surfaces;
	t_list					*sdl_fonts;
	t_list					*functions;
	t_ui_el					*modal_el;
	t_ui_el					*focused_el;
	Uint8					cur_keycode;
	Uint8					is_upper;
	void					*data;
	Uint32					params;
	t_vec2					ptr_pos;
}							t_ui_main;

typedef struct				s_scroll_m_pref
{
	int						type_pos;
	t_fvec2					begin_pos;
	int						type_size;
	t_fvec2					size;
	int						type_indent;
	t_fvec2					indent;
	int						params;
	int						begin_id;
	SDL_Renderer			*sdl_renderer;
	char					*texture;
}							t_scroll_m_pref;

typedef struct				s_resize_data
{
	t_fvec2					elem_pos;
	t_fvec2					elem_size;
	t_fvec2					indent;
}							t_resize_data;

typedef struct				s_font_params
{
	int						style;
	int						hinting;
	int						kerning;
	int						outline;
}							t_font_params;

typedef struct				s_text_params
{
	SDL_Color				text_color;
	SDL_Color				bg_color;
	int						string_len;
	int						params;
	int						render_param;
}							t_text_params;

typedef	int					(*t_pred_ptr_event)(t_ui_main *, void *);

t_ui_el						*ui_raycast(t_ui_main *m, t_ui_win *w);

void						ui_main_run_program(t_ui_main *m);
t_ui_main					*ui_main_init(void);
void						ui_main_loop(t_ui_main *m);

void						ui_main_handle_event(t_ui_main *m);
void						ui_main_handle_raycast(t_ui_main *m);
void						ui_main_handle_window_event(t_ui_main *m);
void						ui_main_handle_mouse_event(t_ui_main *m);
void						ui_main_handle_keyboard_event(t_ui_main *m);
void						ui_main_handle_continious_event(t_ui_main *m,
		t_ui_el *el);

void						ui_main_try_invoke_modal_windows(t_ui_main *m);

int							ui_main_event_close_window(t_ui_main *m, void *a);
int							ui_main_event_close_program(t_ui_main *m, void *a);
int							ui_main_event_pointer_moved(t_ui_main *m, void *a);
int							ui_main_event_lmb_pressed(t_ui_main *m, void *a);
int							ui_main_event_lmb_released(t_ui_main *m, void *a);
int							ui_main_event_rmb_pressed(t_ui_main *m, void *a);
int							ui_main_event_rmb_released(t_ui_main *m, void *a);
int							ui_main_event_scroll_up(t_ui_main *m, void *a);
int							ui_main_event_scroll_down(t_ui_main *m, void *a);

int							ui_main_add_font_by_path(t_ui_main *m,
		const char *path, const char *font_id);
int							ui_main_add_surface_by_path(t_ui_main *m,
		const char *path, const char *sur_id);
int							ui_main_add_window(t_ui_main *m, t_ui_win *w);
int							ui_main_add_function_by_id(t_ui_main *m,
		t_pred_ptr_event f, const char *func_id);

t_ui_win					*ui_main_find_window_by_sdl_id(t_ui_main *m,
		Uint32 window_id);
t_ui_win					*ui_main_find_window_by_id(t_ui_main *m,
		Uint32 window_id);

TTF_Font					*ui_main_get_font_by_id(t_ui_main *m,
		const char *font_id);
SDL_Surface					*ui_main_get_surface_by_id(t_ui_main *m,
		const char *sur_id);
t_pred_ptr_event			ui_main_get_function_by_id(t_ui_main *m,
		const char *func_id);

void						ui_main_fill_default_surfaces(t_ui_main *m);
void						ui_main_fill_default_fonts(t_ui_main *m);

void						ui_main_save_texture(t_ui_win *win, SDL_Texture *t,
		const char *path, int type);
void						ui_main_open_texture(SDL_Renderer *r, t_ui_el *e,
		const char *path);

int							ui_main_set_font_params(t_ui_main *m,
		const char *font_id, t_font_params params);

SDL_Texture					*ui_main_merge_layers(SDL_Renderer *r, t_list *l);

int							ui_log_mouse_motion(t_ui_main *m, void *a);
int							ui_log_mouse_button_up(t_ui_main *m, void *a);
int							ui_log_mouse_button_down(t_ui_main *m, void *a);

int							ui_log_window_focus_gained(t_ui_main *m, void *a);
int							ui_log_window_focus_lost(t_ui_main *m, void *a);
int							ui_log_window_closed(t_ui_main *m, void *a);
int							ui_log_window_resized(t_ui_main *m, void *a);
int							ui_log_window_moved(t_ui_main *m, void *a);

int							ui_log_el_pointer_enter(t_ui_main *m, void *a);
int							ui_log_el_pointer_stay(t_ui_main *m, void *a);
int							ui_log_el_pointer_exit(t_ui_main *m, void *a);

int							ui_log_el_scroll_up(t_ui_main *m, void *a);
int							ui_log_el_scroll_down(t_ui_main *m, void *a);

int							ui_log_el_left_button_hold(t_ui_main *m,
		void *a);
int							ui_log_el_left_button_pressed(t_ui_main *m,
		void *a);
int							ui_log_el_left_button_released(t_ui_main *m,
		void *a);
int							ui_log_el_right_button_pressed(t_ui_main *m,
		void *a);
int							ui_log_el_right_button_released(t_ui_main *m,
		void *a);
int							ui_log_el_right_button_hold(t_ui_main *m, void *a);

int							ui_log_key_pressed(t_ui_main *m, void *a);
int							ui_log_key_released(t_ui_main *m, void *a);

void						q_push(t_queue **q, t_list *el);
void						*q_pop(t_queue **q);

void						bfs_iter(const t_list *root, const t_func_ptr f,
		const void *arg);
void						bfs_iter_root(const t_ui_el *root,
		const t_func_ptr f, const void *arg);

void						bfs_for_resize(const t_ui_el *root, t_ui_main *m);
void						bfs_for_draw(t_ui_main *m, const t_ui_el *root);
t_ui_el						*bfs_for_raycast(t_ui_main *m, const t_ui_el *root,
		t_pred_ptr p);
t_ui_el						*bfs_for_find_el_by_id(const t_ui_el *root,
		Uint32 id);

void						ui_draw(t_ui_main *m);
void						ui_draw_window(t_ui_main *m, t_ui_win *w);
void						ui_draw_windows(t_ui_main *m);
void						ui_clear_windows(t_ui_main *m);
void						ui_show_window(t_ui_win *w);
void						ui_show_windows(t_ui_main *m);

t_ui_el						*ui_el_init(void);
int							ui_el_add_child(t_ui_el *el, t_ui_el *child);

void						ui_el_destroy(t_ui_el *e);
void						ui_el_destroy_children(t_list *c);

void						ui_el_set_pos(t_ui_el *el, int type, t_fvec2 v);
void						ui_el_set_size(t_ui_el *el, int type, t_fvec2 v);
void						ui_el_set_new_pos(t_ui_el *el, t_ui_el *canvas,
		int type, t_fvec2 v);
void						ui_el_set_new_size(t_ui_el *el, t_ui_el *canvas,
		int type, t_fvec2 v);
void						ui_el_set_new_pos_for_children(void *a1, void *a2);
void						ui_el_set_new_size_for_children(void *a1, void *a2);
void						ui_el_set_new_pos(t_ui_el *el, t_ui_el *canvas,
		int type, t_fvec2 v);
void						ui_el_change_pos(t_ui_el *el, t_ui_el *canvas,
		int type, t_fvec2 v);

SDL_Texture					*ui_el_create_texture(t_ui_el *el);
SDL_Texture					*ui_el_create_texture_from_surface(t_ui_el *el,
		SDL_Surface *sur);

SDL_Texture					*ui_el_get_current_texture(t_ui_el *el);
SDL_Texture					*ui_el_get_texture_by_id(t_ui_el *el,
		const char *id);

int							ui_el_add_texture_from_file(t_ui_el *el,
						const char *path, const char *texture_id);
int							ui_el_add_empty_texture(t_ui_el *el, int w, int h,
						const char *texture_id);
int							ui_el_add_white_texture(t_ui_el *el, int w, int h,
						const char *texture_id);
int							ui_el_add_gradient_texture(t_ui_el *el, t_vec2 wh,
		int color, const char *texture_id);
int							ui_el_add_color_texture(t_ui_el *el, t_vec2 wh,
		int color, const char *texture_id);
int							ui_el_add_texture_from_file_dialog(t_ui_el *el);
int							ui_el_add_texture_from_file_dialog_with_size(
		t_ui_el *el, int w, int h);
int							ui_el_add_texture_from_main_by_id(t_ui_main *m,
		t_ui_el *el, const char *id, const char *texture_id);

int							ui_el_set_current_texture_by_id(t_ui_el *el,
		const char *texture_id);

int							ui_el_load_surface_from(t_ui_el *el,
		const char *path);

int							ui_el_set_text(t_ui_el *el, TTF_Font *font,
		t_text_params params);
int							ui_el_update_text(t_ui_el *el, const char *text);

void						ui_el_setup_default_draggable(t_ui_el *el);
void						ui_el_setup_default_resizable(t_ui_el *el);
void						ui_el_setup_default_scroll_menu_elem(t_ui_el *el);
void						ui_el_setup_default_scroll_menu(t_ui_el *el);
void						ui_el_setup_default(t_ui_el *el);
void						ui_el_setup_horizontal_draggable(t_ui_el *el);
void						ui_el_setup_menu_resizable(t_ui_el *el);
void						ui_el_setup_radio(t_ui_el *el);

int							ui_el_event_switch_radio(t_ui_main *m, void *a);
int							ui_el_event_default_pointer_enter(t_ui_main *m,
		void *a);
int							ui_el_event_default_pointer_exit(t_ui_main *m,
		void *a);
int							ui_el_event_scroll_menu_up(t_ui_main *m, void *a);
int							ui_el_event_scroll_menu_down(t_ui_main *m, void *a);
int							ui_el_event_scroll_child_menu_up(t_ui_main *m,
		void *a);
int							ui_el_event_scroll_child_menu_down(t_ui_main *m,
		void *a);
int							ui_el_event_default_draw(t_ui_main *m, void *a);
int							ui_el_event_drag(t_ui_main *m, void *a);
int							ui_el_event_hor_slider_drag(t_ui_main *m, void *a);
int							ui_el_event_menu_resize(t_ui_main *m, void *a);
int							ui_el_event_default_resize(t_ui_main *m, void *a);
int							ui_el_event_children_set_default(t_ui_main *m,
		void *a);
int							ui_el_event_show_child(t_ui_main *m, void *a);
int							ui_el_event_show_window(t_ui_main *m, void *a);
int							ui_el_event_close_window(t_ui_main *m, void *a);

int							ui_el_event_set_default_texture(t_ui_main *m,
		void *a);
int							ui_el_event_set_focused_texture(t_ui_main *m,
		void *a);
int							ui_el_event_set_active_texture(t_ui_main *m,
		void *a);
void						ui_el_texture_x_w(t_ui_el *e, t_rect *srect,
		t_rect *tmp_rect, int w);
void						ui_el_texture_y_h(t_ui_el *e, t_rect *srect,
		t_rect *tmp_rect, int h);

t_ui_win					*ui_win_init(void);
void						ui_win_create(t_ui_win *w, int params);
void						ui_win_setup_default(t_ui_win *w);
void						ui_win_destroy(t_ui_win *w);

t_ui_el						*ui_win_find_el_by_id(t_ui_win *w, Uint32 id);

int							ui_win_event_update_size(t_ui_main *m, void *a);
int							ui_win_event_change_text_in_focused_el(t_ui_main *m,
		void *a);
int							ui_win_event_focus_lost(t_ui_main *m, void *a);
int							ui_win_event_focus_gained(t_ui_main *m, void *a);

int							ui_sdl_init(void);
void						ui_sdl_deinit(int exit_status);

int							ui_jtoc_main_from_json(t_ui_main *m, const char *p);

int							ui_jtoc_win_from_json(t_ui_main *m, t_jnode *n);
int							ui_jtoc_get_win_param_from_string(const char *str);
t_ui_event					*ui_jtoc_win_from_json_get_event_by_name(
		t_ui_win *w, const char *n);

int							ui_jtoc_el_from_json(t_ui_main *m, t_ui_win *w,
		t_jnode *n);
t_ui_event					*ui_jtoc_el_from_json_get_event_by_name(t_ui_el *e,
						const char *n);
int							ui_jtoc_get_el_param_from_string(const char *str);
int							ui_jtoc_el_setup_by_type(t_ui_el *e, t_jnode *n);
int							ui_jtoc_el_pref_text(t_ui_main *m, t_ui_el *e,
		t_jnode *n);
int							ui_jtoc_pref_text_modal_win(t_ui_main *m,
		t_jnode *n, t_ui_text *ui_text);
int							ui_jtoc_el_pref_modal_win(t_ui_main *m, t_ui_el *e,
		t_jnode *n);
void						ui_jtoc_create_modal_ok(t_ui_main *m, t_ui_win *w,
						t_ui_text *ui_text);
void						ui_jtoc_create_modal_ok_cancel(t_ui_main *m,
		t_ui_win *w, t_ui_text *ui_text);

int							ui_jtoc_get_pos_size(const char *str);

int							ui_jtoc_sdl_log_error(const char *p, const int id);

/*
**TODO NORMAL NAME
*/
int							ui_el_from_json_textures(t_ui_main *m, t_ui_el *e,
								t_jnode *n);
int							ui_parse_canvas(t_ui_main *m, t_ui_el *e,
		t_jnode *n);
int							ui_el_from_json_size(t_ui_main *m,
								t_ui_el *e, t_jnode *n);
int							ui_el_from_json_texture(t_ui_main *m, t_ui_el *e,
								t_jnode *n);
int							ui_el_from_json_event(t_ui_main *m, t_ui_el *e,
								t_jnode *n);
int							ui_el_from_json_events(t_ui_main *m, t_ui_el *e,
								t_jnode *n);
int							ui_el_from_json_white_texture(t_ui_el *e,
		t_jnode *n);
int							ui_el_from_json_empty_texture(t_ui_el *e,
		t_jnode *n);
int							ui_el_from_json_color_texture(t_ui_el *e,
		t_jnode *n);
int							ui_el_from_json_gradient_texture(t_ui_el *e,
		t_jnode *n);
int							ui_el_from_json_cursor(t_ui_main *m, t_ui_el *e,
						t_jnode *n);

t_ui_event					*ui_event_init(void);
t_ui_el_events				*ui_event_el_events_init(void);
t_ui_win_events				*ui_event_win_events_init(void);

int							ui_event_add_listener(t_ui_event *e,
		t_pred_ptr_event f);
int							ui_event_add_listener_front(t_ui_event *e,
		t_pred_ptr_event f);

void						ui_event_invoke(t_ui_event *e, t_ui_main *m,
		void *a);
void						ui_event_clear(t_ui_event *e);

void						ui_event_destroy(t_ui_event *e);
void						ui_event_win_events_destroy(t_ui_win_events *we);
void						ui_event_el_events_destroy(t_ui_el_events *ee);

t_rect						ui_util_get_rect_from_frect(t_frect frect);
SDL_Color					ui_util_get_sdl_color(int color);
Uint32						ui_util_get_pixel_color_from_texture(
		SDL_Renderer *renderer, SDL_Texture *texture, t_vec2 coord);
Uint32						ui_util_get_pixel_color_from_el(
		SDL_Renderer *renderer, t_ui_el *el, t_vec2 coord);
void						ui_util_set_pixel_color_to_texture_replace(
		SDL_Renderer *renderer, SDL_Texture *texture,
		t_vec2 coord, SDL_Color color);

t_cursor					*ui_cursor_init(void);

void						ui_cursor_to_default(t_ui_main *m, void *a);

int							ui_cursor_from_el_data(t_ui_main *m, void *a);
void						ui_cursor_from(t_cursor *c);

int							ui_file_parse_path(char **res);
int							ui_file_find_last_slash(const char *str);
int							ui_file_open_file_dialog(char **res);
int							ui_file_save_file_dialog(char **res);

/*
** IT'S PUITA, BUT NOT DEL, COULD BE USEFUL FOR CREATE JSON PREFAB
*/
void						ui_prefab_scroll_menu(t_ui_main *m, t_ui_el *canvas,
		t_ui_el *scroll_menu, t_scroll_m_pref *scroll_data);
void						ui_prefab_get_pixel_pos(t_ui_el *p, t_ui_el *canvas,
		int type, t_fvec2 *pos);
void						ui_prefab_get_pixel_size(t_ui_el *p,
		t_ui_el *canvas, int type, t_fvec2 *size);

/*
** TODO normal names, pack on groups
*/
int							ctid(t_list_texture *lst, int tid);
void						ui_el_remove_texture_by_id(t_ui_el *el,
		const char *id);

void						ui_sdl_set_render_target(SDL_Renderer *r,
		SDL_Texture *t);
void						ui_sdl_set_texture_color_mode(SDL_Texture *t,
		Uint8 r, Uint8 g, Uint8 b);
void						ui_sdl_set_texture_alpha_mode(SDL_Texture *t,
		Uint8 a);
void						ui_sdl_render_copy(SDL_Renderer *r, SDL_Texture *t,
		SDL_Rect *r1,
		SDL_Rect *r2);
void						ui_sdl_set_render_draw_color(SDL_Renderer *r,
		SDL_Color *c);
void						ui_sdl_set_render_draw_blend_mode(SDL_Renderer *r,
		SDL_BlendMode b);
void						ui_sdl_render_draw_line(SDL_Renderer *r,
		t_vec2 *v1, t_vec2 *v2);
void						ui_sdl_render_fill_rect(SDL_Renderer *r,
		SDL_Rect *rect);
void						ui_sdl_destroy_texture(SDL_Texture *t);
SDL_Texture					*ui_sdl_create_texture(SDL_Renderer *r, Uint32 f,
		int a, t_vec2 *s);
SDL_Texture					*ui_sdl_create_texture_from_surface(SDL_Renderer *r,
		SDL_Surface *s);
void						ui_sdl_render_clear(SDL_Renderer *r);

void						ui_sdl_set_window_position(SDL_Window *w,
		int x, int y);
void						ui_sdl_get_window_position(SDL_Window *w,
		int *x, int *y);
void						ui_sdl_raise_window(SDL_Window *w);

void						ui_sdl_free_surface(SDL_Surface *s);
SDL_Surface					*ui_sdl_create_rgb_surface(t_vec2 *s);
void						ui_sdl_renderer_read_pixels(SDL_Renderer *r,
		Uint32 f, void *p, int ph);

void						ui_surface_set_pixel(t_sur *surface, int x, int y,
		Uint32 pixel);
Uint32						ui_surface_get_pixel(t_sur *surface, int x, int y);

#endif

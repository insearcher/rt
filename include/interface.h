/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:19:35 by edraugr-          #+#    #+#             */
/*   Updated: 2019/09/26 14:19:39 by edraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_INTERFACE_H
# define RT_INTERFACE_H

# include "rt.h"
# include "libui.h"

# define DEFAULT_BUT_STATE		"default"
# define HIGHLIGHTED_BUT_STATE	"highlighted"
# define SELECTED_BUT_STATE		"selected"
# define ACTIVE_MENU			1
# define UNACTIVE_MENU			0

# define INSPECTOR_EL_ID		210
# define CHANGE_POS_SPEED		0.05f
# define CHANGE_ROT_SPEED		1

int								rt_uix_on_button_exit(t_ui_main *main, void *el_v);
int								rt_uix_on_button_enter(t_ui_main *main, void *el_v);
int								rt_uix_button_choose(t_ui_main *main, void *el_v);
int								rt_uix_button_select(t_ui_main *main, void *el_v);
int								rt_uix_choose_path_trace(t_ui_main *main, void *el_v);
int								rt_uix_choose_none(t_ui_main *main, void *el_v);
int								rt_uix_choose_pong(t_ui_main *main, void *el_v);
int								rt_uix_show_menu(t_ui_main *main, void *el_v);
int								rt_uix_choose_obj_from_scene(t_ui_main *main, void *el_v);
int								rt_uix_inspector_pos_button(t_ui_main *main, void *el_v);
int								rt_uix_inspector_rot_button(t_ui_main *main, void *el_v);



int								rt_uix_switch_blur(t_ui_main *main, void *el_v);
int								rt_uix_switch_monochrome(t_ui_main *main, void *el_v);
int								rt_uix_switch_anaglyph(t_ui_main *main, void *el_v);
int								rt_uix_switch_dithering(t_ui_main *main, void *el_v);
int								rt_uix_clear_pp(t_ui_main *main, void *el_v);


void							rt_uix_add_functions(t_ui_main *m);
void							rt_uix_update_inspector_values(t_ui_main *ui);
void							fill_scene(t_ui_main *ui, t_ui_el *obj_menu);
void							rt_uix_scene_setup(t_ui_main *ui);
void							rt_uix_interface_setup(t_ui_main *ui, const char *json_path);
void							rt_uix_fill_default_images(t_ui_main *ui);

#endif

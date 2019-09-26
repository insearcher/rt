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

int								rt_uix_on_button_exit(t_ui_main *main, void *el_v);
int								rt_uix_on_button_enter(t_ui_main *main, void *el_v);
int								rt_uix_button_choose(t_ui_main *main, void *el_v);
int								rt_uix_button_select(t_ui_main *main, void *el_v);
int								rt_uix_choose_path_trace(t_ui_main *main, void *el_v);
int								rt_uix_choose_none(t_ui_main *main, void *el_v);
int								rt_uix_choose_pong(t_ui_main *main, void *el_v);
int								rt_uix_switch_gauss_blur(t_ui_main *main, void *el_v);

void							rt_uix_add_functions(t_ui_main *m);

#endif
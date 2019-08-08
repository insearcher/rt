/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_input.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 05:13:21 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/03 20:16:18 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_INPUT_H
# define RT_INPUT_H

# include "config.h"
# include "rt_camera.h"
# include "rt_rotations.h"
# include "rt_system.h"

typedef struct		s_input_system
{
	t_system		system;
	const Uint8		*state;
	t_rb			*active;
	t_transform		*selected;
}					t_input_system;

void				move_active(t_input_system *s);
void				rotate_active(t_input_system *s);

void				change_selected(t_input_system *s, t_object *o);

int					is_func(void *isv);

#endif

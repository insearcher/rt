/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_el_event_show_window.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 07:48:29 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/14 16:47:33 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

int	ui_el_event_show_window(t_ui_main *m, void *a)
{
	t_ui_win	*w;

	w = ((t_ui_el *)a)->modal_win;
	(void)m;
	w->params |= WIN_IS_SHOWN;
	return (0);
}

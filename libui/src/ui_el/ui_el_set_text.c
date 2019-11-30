/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_el_set_text.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 01:55:53 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/14 09:31:18 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static void	add_change_text_events(t_ui_el *el)
{
	int	i;

	i = -1;
	while (++i < KEYS_COUNT)
		ui_event_add_listener(el->events->on_key_down[i],
							ui_el_event_change_text);
}

int			ui_el_set_text(t_ui_el *el, TTF_Font *font, t_text_params tp)
{
	el->text_area = (t_ui_text *)ft_memalloc(sizeof(t_ui_text));
	el->text_area->font = font;
	el->text_area->string_len = tp.string_len;
	el->text_area->text_color = tp.text_color;
	el->text_area->render_param = tp.render_param;
	el->text_area->params = tp.params;
	el->text_area->bg_color = tp.bg_color;
	el->params |= EL_IS_TEXT;
	add_change_text_events(el);
	ui_el_update_text(el, "");
	return (FUNCTION_SUCCESS);
}

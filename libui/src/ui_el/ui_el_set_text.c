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

int	ui_el_set_text(t_ui_el *el, TTF_Font *font, t_text_params text_params)
{
	el->text_area = (t_ui_text *)ft_memalloc(sizeof(t_ui_text));
	el->text_area->font = font;
	el->text_area->string_len = text_params.string_len;
	el->text_area->text_color = text_params.text_color;
	el->text_area->render_param = text_params.render_param;
	el->text_area->params = text_params.params;
	el->text_area->bg_color = text_params.bg_color;
	el->params |= EL_IS_TEXT;
	ui_el_update_text(el, "");
	return (FUNCTION_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_jtoc_pref_text_modal_win.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 13:09:43 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/15 13:27:10 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static void	get_render_param(t_ui_text *ui_text, t_jnode *tmp)
{
	int		hash;

	hash = ft_strhash(jtoc_get_string(tmp));
	ui_text->render_param |= (hash == ft_strhash("TEXT_IS_SOLID") ?
			TEXT_IS_SOLID : 0);
	ui_text->render_param |= (hash == ft_strhash("TEXT_IS_SHADED") ?
			TEXT_IS_SHADED : 0);
	ui_text->render_param |= (hash == ft_strhash("TEXT_IS_BLENDED") ?
			TEXT_IS_BLENDED : 0);
}

static void	get_text_param(t_ui_text *ui_text, t_jnode *tmp)
{
	int		hash;

	hash = ft_strhash(jtoc_get_string(tmp));
	ui_text->params |= (hash == ft_strhash("TEXT_IS_CENTERED") ?
			TEXT_IS_CENTERED : 0);
	ui_text->params |= (hash == ft_strhash("TEXT_IS_INPUTTING") ?
			TEXT_IS_INPUTTING : 0);
	ui_text->params |= (hash == ft_strhash("TEXT_IS_REGULAR") ?
			TEXT_IS_REGULAR : 0);
}

static int	get_modal_text_params(t_ui_text *ui_text, t_jnode *n)
{
	t_jnode *tmp;

	if ((tmp = jtoc_node_get_by_path(n, "text_area.string_len"))
			&& tmp->type == number)
		ui_text->string_len = jtoc_get_int(tmp);
	if ((tmp = jtoc_node_get_by_path(n, "text_area.render_param"))
			&& tmp->type == string)
		get_render_param(ui_text, tmp);
	else
		ui_text->render_param |= TEXT_IS_BLENDED;
	if ((tmp = jtoc_node_get_by_path(n, "text_area.params")))
	{
		tmp = tmp->down;
		while (tmp)
		{
			if (tmp->type != string)
				return (FUNCTION_FAILURE);
			get_text_param(ui_text, tmp);
			tmp = tmp->right;
		}
	}
	return (FUNCTION_SUCCESS);
}

static int	get_modal_font_color(t_ui_main *m, t_ui_text *ui_text, t_jnode *n)
{
	t_jnode	*tmp;

	if ((tmp = jtoc_node_get_by_path(n, "text_area.font"))
			&& tmp->type == string)
	{
		if (!(ui_text->font = ui_main_get_font_by_id(m, jtoc_get_string(tmp))))
			return (FUNCTION_FAILURE);
	}
	else
		return (FUNCTION_FAILURE);
	if ((tmp = jtoc_node_get_by_path(n, "text_area.color"))
			&& tmp->type == string)
		ui_text->text_color = ui_util_get_sdl_color(
				ft_atoi_base(jtoc_get_string(tmp), 16));
	else
		return (FUNCTION_FAILURE);
	if ((tmp = jtoc_node_get_by_path(n, "text_area.bg_color"))
			&& tmp->type == string)
		ui_text->bg_color = ui_util_get_sdl_color(
				ft_atoi_base(jtoc_get_string(tmp), 16));
	return (FUNCTION_SUCCESS);
}

int			ui_jtoc_pref_text_modal_win(t_ui_main *m, t_jnode *n,
		t_ui_text *ui_text)
{
	t_jnode	*tmp;

	if ((jtoc_node_get_by_path(n, "text_area")))
	{
		if (get_modal_font_color(m, ui_text, n) == FUNCTION_FAILURE)
			return (FUNCTION_FAILURE);
		if (get_modal_text_params(ui_text, n) == FUNCTION_FAILURE)
			return (FUNCTION_FAILURE);
		if ((tmp = jtoc_node_get_by_path(n, "text_area.text"))
				&& tmp->type == string)
			ui_text->text = ft_strdup(jtoc_get_string(tmp));
		else
			return (FUNCTION_FAILURE);
		return (FUNCTION_SUCCESS);
	}
	return (FUNCTION_FAILURE);
}

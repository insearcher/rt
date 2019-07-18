/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_win_event_change_text_in_focused_el.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 19:18:31 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/15 11:21:25 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static void	circumcision(t_ui_el *el)
{
	char	*str;

	if (el->text_area->text == NULL || *el->text_area->text == '\0')
		str = ft_strnew(1);
	else
		str = ft_strsub(el->text_area->text, 0,
				ft_strlen(el->text_area->text) - 1);
	ui_el_update_text(el, str);
	if (str != NULL)
		free(str);
}

static void	join_with_letter(t_ui_el *el, unsigned int keycode, Uint8 is_upper)
{
	char	*str;
	char	*str_letter;

	str_letter = ft_strnew(1);
	str_letter[0] = (char)(keycode + 93);
	if (is_upper)
		str_letter[0] = ft_toupper(str_letter[0]);
	if (el->text_area->text == NULL)
		str = ft_strdup(str_letter);
	else
		str = ft_strjoin(el->text_area->text, str_letter);
	ui_el_update_text(el, str);
	if (str != NULL)
		free(str);
	free(str_letter);
}

static void	join_with_number(t_ui_el *el, unsigned int keycode)
{
	char	*str_letter;
	char	*str;

	str_letter = ft_strnew(1);
	str_letter[0] = (char)(keycode + 19);
	if (el->text_area->text == NULL)
		str = ft_strdup(str_letter);
	else
		str = ft_strjoin(el->text_area->text, str_letter);
	ui_el_update_text(el, str);
	if (str != NULL)
		free(str);
	free(str_letter);
}

static void	join_with_other(t_ui_el *el, unsigned int keycode)
{
	char	*str_letter;
	char	*str;

	str_letter = ft_strnew(1);
	if (keycode == 56)
		str_letter[0] = '/';
	else if (keycode == 55)
		str_letter[0] = '.';
	else if (keycode == SDL_SCANCODE_SPACE)
		str_letter[0] = ' ';
	else if (keycode == 45)
		str_letter[0] = '-';
	else if (keycode == SDL_SCANCODE_0)
		str_letter[0] = '0';
	if (el->text_area->text == NULL)
		str = ft_strdup(str_letter);
	else
		str = ft_strjoin(el->text_area->text, str_letter);
	ui_el_update_text(el, str);
	if (str != NULL)
		free(str);
	free(str_letter);
}

int			ui_win_event_change_text_in_focused_el(t_ui_main *m, void *a)
{
	t_ui_win	*w;
	t_ui_el		*el;

	w = (t_ui_win *)a;
	el = m->focused_el;
	if (!el || !(el->params & EL_IS_TEXT)
			|| !(el->text_area->params & TEXT_IS_INPUTTING))
		return (1);
	if (m->cur_keycode >= SDL_SCANCODE_A && m->cur_keycode <= SDL_SCANCODE_Z)
		join_with_letter(el, m->cur_keycode, m->is_upper);
	else if (m->cur_keycode >= SDL_SCANCODE_1
			&& m->cur_keycode <= SDL_SCANCODE_9)
		join_with_number(el, m->cur_keycode);
	else if (m->cur_keycode == SDL_SCANCODE_BACKSPACE)
		circumcision(el);
	else if (m->cur_keycode == 55 || m->cur_keycode == 56 ||
			m->cur_keycode == SDL_SCANCODE_0 ||
			m->cur_keycode == SDL_SCANCODE_SPACE || m->cur_keycode == 45)
		join_with_other(el, m->cur_keycode);
	return (1);
}

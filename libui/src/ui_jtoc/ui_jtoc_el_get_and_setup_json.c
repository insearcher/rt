/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_jtoc_el_get_and_setup_json.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 06:44:19 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/15 15:24:36 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

t_ui_event	*ui_jtoc_win_from_json_get_event_by_name(t_ui_win *w,
					const char *n)
{
	int			hash;
	t_ui_event	*res;

	hash = ft_strhash(n);
	res = NULL;
	res = (hash == ft_strhash("onPointerMoved") ? w->events->on_pointer_moved :
		res);
	res = (hash == ft_strhash("onPointerLeftButtonPressed") ?
		w->events->on_pointer_left_button_pressed : res);
	res = (hash == ft_strhash("onPointerLeftButtonReleased") ?
		w->events->on_pointer_left_button_released : res);
	res = (hash == ft_strhash("onPointerRightButtonPressed") ?
		w->events->on_pointer_right_button_pressed : res);
	res = (hash == ft_strhash("onPointerRightButtonReleased") ?
		w->events->on_pointer_right_button_released : res);
	res = (hash == ft_strhash("onScrollUp") ? w->events->on_scroll_up : res);
	res = (hash == ft_strhash("onScrollDown") ?
			w->events->on_scroll_down : res);
	res = (hash == ft_strhash("onFocusGained") ? w->events->on_focus_gained :
		res);
	res = (hash == ft_strhash("onFocusLost") ? w->events->on_focus_lost : res);
	res = (hash == ft_strhash("onResize") ? w->events->on_resize : res);
	res = (hash == ft_strhash("onClose") ? w->events->on_close : res);
	res = (hash == ft_strhash("onMoved") ? w->events->on_moved : res);
	return (res);
}

int			ui_jtoc_get_el_param_from_string(const char *str)
{
	int	hash;
	int	i;

	hash = ft_strhash(str);
	i = 0;
	i |= (hash == ft_strhash("EL_IGNOR_RAYCAST") ? EL_IGNOR_RAYCAST : 0);
	i |= (hash == ft_strhash("EL_IS_HIDDEN") ? EL_IS_HIDDEN : 0);
	i |= (hash == ft_strhash("EL_IS_SCROLLABLE") ? EL_IS_SCROLLABLE : 0);
	i |= (hash == ft_strhash("EL_IS_DEPENDENT") ? EL_IS_DEPENDENT : 0);
	i |= (hash == ft_strhash("EL_IS_ICON") ? EL_IS_ICON : 0);
	return (i);
}

int			ui_jtoc_get_pos_size(const char *str)
{
	int	hash;
	int	i;

	hash = ft_strhash(str);
	i = 0;
	i |= (hash == ft_strhash("ABS") ? ABS : 0);
	i |= (hash == ft_strhash("PIXEL") ? PIXEL : 0);
	return (i);
}

int			ui_jtoc_el_setup_by_type(t_ui_el *e, t_jnode *n)
{
	int		h;
	t_jnode	*tmp;

	ui_el_setup_default(e);
	if (!(tmp = jtoc_node_get_by_path(n, "type")))
		return (FUNCTION_SUCCESS);
	tmp = tmp->down;
	while (tmp)
	{
		if (tmp->type != string)
			ui_sdl_deinit(228);
		h = ft_strhash(jtoc_get_string(tmp));
		(h == ft_strhash("DRAGGABLE") ? ui_el_setup_default_draggable(e) : 0);
		(h == ft_strhash("RESIZABLE") ? ui_el_setup_default_resizable(e) : 0);
		(h == ft_strhash("SCROLL_MENU_ELEM") ?
			ui_el_setup_default_scroll_menu_elem(e) : 0);
		(h == ft_strhash("SCROLL_MENU") ? ui_el_setup_default_scroll_menu(e) :
			0);
		(h == ft_strhash("HORIZONTAL_DRAGGABLE") ?
			ui_el_setup_horizontal_draggable(e) : 0);
		(h == ft_strhash("MENU_RESIZABLE") ? ui_el_setup_menu_resizable(e) : 0);
		(h == ft_strhash("RADIO") ? ui_el_setup_radio(e) : 0);
		tmp = tmp->right;
	}
	return (FUNCTION_SUCCESS);
}

int			ui_jtoc_get_win_param_from_string(const char *str)
{
	int	i;

	i = 0;
	i |= ((ft_strcmp(str, "WIN_RESIZABLE") == 0) ? WIN_RESIZABLE : 0);
	return (i);
}

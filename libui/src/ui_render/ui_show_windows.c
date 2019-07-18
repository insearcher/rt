/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_show_windows.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 06:26:19 by edraugr-          #+#    #+#             */
/*   Updated: 2019/07/06 18:28:10 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_show_windows(t_ui_main *m)
{
	t_list	*node;

	node = m->windows;
	while (node)
	{
		ui_show_window((t_ui_win *)node->content);
		node = node->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_event_invoke.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 19:38:40 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/13 10:42:06 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	ui_event_invoke(t_ui_event *e, t_ui_main *m, void *a)
{
	t_list				*node;
	t_pred_ptr_event	f;

	if (!e)
		return ;
	node = e->events;
	while (node)
	{
		f = (t_pred_ptr_event)(*((long *)node->content));
		if (!((*f)(m, a)))
			return ;
		node = node->next;
	}
}

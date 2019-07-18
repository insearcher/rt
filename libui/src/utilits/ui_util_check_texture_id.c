/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_util_check_texture_id.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 11:23:11 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/15 11:23:29 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

int	ctid(t_list_texture *lst, int tid)
{
	while (lst)
	{
		if (lst->content_size == (size_t)tid)
			ui_sdl_deinit(228);
		lst = lst->next;
	}
	return (FUNCTION_SUCCESS);
}

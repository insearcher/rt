/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 21:47:16 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/24 21:47:17 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	gc_collect(void)
{
	t_gc	*gc;
	t_list	*cur;
	t_list	*tmp;

	if ((gc = gc_get()))
		return (-1);
	cur = gc->root;
	while (cur)
	{
		tmp = cur->next;
		free(cur->content);
		free(cur);
		cur = tmp;
	}
	gc->root = NULL;
	return (0);
}
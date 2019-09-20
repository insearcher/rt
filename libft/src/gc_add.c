/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 21:47:16 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/24 21:47:17 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	gc_add(void *c)
{
	t_gc	*gc;
	t_list	*node;

	if ((gc = gc_get()))
		return (-1);
	if (!(node = ft_lstnew(NULL, 0)))
		return (-1);
	node->content = c;
	ft_lstadd(&gc->root, node);
	return (0);
}
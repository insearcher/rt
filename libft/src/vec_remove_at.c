/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_remove_at.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 23:51:41 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/10 14:41:24 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	vec_remove_at(t_vec *v, size_t i)
{
	void	*c;
	void	*l;

	if (i >= v->size)
		return (-1);
	c = vec_at(v, i);
	l = vec_last(v);
	ft_memcpy(c, l, v->cell_size * sizeof(int));
	--v->size;
	return (0);
}
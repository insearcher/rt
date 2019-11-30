/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 21:47:16 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/24 21:47:17 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	vec_insert(t_vec *v, void *d, size_t i)
{
	if (i > v->size)
		return (-1);
	else if (i == v->size)
		vec_push_back(v, d);
	else
		ft_memcpy(v->storage + v->cell_size * i, d, v->real_cell_size);
	return (0);
}

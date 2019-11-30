/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_push_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 21:47:16 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/24 21:47:17 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	vec_push_back(t_vec *v, void *d)
{
	size_t	offset;

	if (v->size >= v->capacity && vec_resize(v, v->capacity * 2))
		return (-1);
	offset = v->size * v->cell_size;
	ft_memcpy(v->storage + offset, d, v->real_cell_size);
	++v->size;
	return (0);
}

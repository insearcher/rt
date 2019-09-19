/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_resize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 21:47:16 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/24 21:47:17 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	vec_resize(t_vec *v, size_t c)
{
	int		*new_storage;
	size_t	s;
	size_t	b;

	s = c * v->cell_size * sizeof(int);
	if (!(new_storage = malloc(s)))
		return (-1);
	v->capacity = c;
	b = v->capacity * v->cell_size * sizeof(int);
	ft_memcpy(new_storage, v->storage, b);
	ft_bzero(new_storage + b, s - b);
	free(v->storage);
	v->storage = new_storage;
	return (0);
}
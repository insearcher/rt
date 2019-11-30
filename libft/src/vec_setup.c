/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 21:47:16 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/24 21:47:17 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	vec_setup(t_vec *v, size_t c, size_t cs)
{
	size_t	s;

	v->cell_size = (cs % 4 ? 1 : 0) + cs / 4;
	v->real_cell_size = cs;
	s = v->cell_size * c * sizeof(int);
	if (!(v->storage = ft_memalloc(s)))
		return (-1);
	v->capacity = c;
	v->size = 0;
	return (0);
}

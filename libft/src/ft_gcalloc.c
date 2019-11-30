/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gcalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 21:47:16 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/24 21:47:17 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_gcalloc(size_t size)
{
	void	*res;

	if (!(res = ft_memalloc(size)))
		return (NULL);
	if (!gc_add(res))
	{
		free(res);
		return (NULL);
	}
	return (res);
}

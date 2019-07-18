/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jtoc_get_raw_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 20:24:00 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/18 20:24:00 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libjtoc.h"
#include <stdio.h>

static size_t	get_tree_size(t_jnode *n)
{
	t_jnode	*children;
	char	contains_ptrs;
	size_t	res;

	children = n->down;
	contains_ptrs = 0;
	res = 0;
	while (children)
	{
		if (children->type == integer || children->type == fractional)
			res += 4;
		else
		{
			if (res % 8 != 0)
				res += 4;
			res += 8;
			contains_ptrs = 1;
		}
		children = children->right;
	}
	if (contains_ptrs && res % 8 != 0)
		res += 4;
	return (res);
}

void	print(char *t, int c)
{
	printf("res: \n");
	for (int i = 0; i < c; i++)
		printf("%d%d%d%d%d%d%d%d ",
			   (t[i] >> 7) & 1,
			   (t[i] >> 6) & 1,
			   (t[i] >> 5) & 1,
			   (t[i] >> 4) & 1,
			   (t[i] >> 3) & 1,
			   (t[i] >> 2) & 1,
			   (t[i] >> 1) & 1,
			   (t[i] >> 0) & 1
		);
	printf("\n\n");
}

static void		*get_string(t_jnode *n)
{
	size_t	len;
	void	*src;
	void	*res;

	src = jtoc_get_string(n);
	len = ft_strlen(src);
	if (!(res = malloc(len + 1)))
		return (NULL);
	ft_memcpy(res, src, len + 1);
	return (res);
}

void			*jtoc_get_raw_data(t_jnode *n)
{
	size_t		size;
	char		*res;
	size_t		i;
	t_jnode		*cur;
	void		*tmp;

	size = get_tree_size(n);
	if (!(res = (char *)ft_memalloc(size)))
		return (NULL);
	i = 0;
	cur = n->down;
	while (cur)
	{
		if (i != 0 && cur->type != integer && cur->type != fractional && i % 8 != 0)
			i += 4;
		if (cur->type == integer || cur->type == fractional)
			ft_memcpy(res + i, cur->data, 4);
		else if (cur->type == string)
		{
			if (!(tmp = get_string(cur)))
				return (NULL);
			ft_memcpy(res + i, &tmp, 8);
			i += 4;
		}
		else
		{
			if (!(tmp = jtoc_get_raw_data(cur)))
				return (NULL);
			ft_memcpy(res + i, &tmp, 8);
			i += 4;
		}
		cur = cur->right;
		i += 4;
	}
	return ((void *)res);
}
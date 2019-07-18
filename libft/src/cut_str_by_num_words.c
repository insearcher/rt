/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_str_by_num_words.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <edraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 01:35:42 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/14 20:58:18 by edraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*csbnw2(const char *s, size_t new_len_str, size_t num_words)
{
	char	*res;
	int		i;
	int		j;
	int		k;

	res = (char *)ft_memalloc(new_len_str + 2);
	i = -1;
	j = 0;
	k = -1;
	while (s[++i] && (size_t)j < num_words)
	{
		if (s[i] != ' ')
		{
			while (s[i] != ' ' && s[i])
				res[++k] = s[i++];
			++j;
			res[++k] = ' ';
		}
	}
	res[k] = '\0';
	return (res);
}

char			*cut_str_by_num_words(const char *s, size_t num_words)
{
	size_t	i;
	size_t	j;
	size_t	new_len_str;

	i = -1;
	j = 0;
	new_len_str = 0;
	while (s[++i] && j < num_words)
	{
		if (s[i] != ' ')
		{
			++j;
			while (s[i] != ' ' && s[i])
			{
				++new_len_str;
				++i;
			}
			++new_len_str;
			--i;
		}
	}
	return (csbnw2(s, new_len_str, num_words));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_strs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 01:35:42 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/10 15:28:18 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			**get_strs(const char *s, size_t *nss,
						size_t *num_words_in_strs)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	**strs;

	i = -1;
	j = -1;
	k = -1;
	strs = (char **)ft_memalloc(sizeof(char *) * (*nss + 1));
	while (s[++i])
	{
		strs[++j] = cut_str_by_num_words(&(s[i]), num_words_in_strs[++k]);
		while (num_words_in_strs[k])
		{
			num_words_in_strs[k]--;
			while (s[i] == ' ' && s[i])
				++i;
			while (s[i] != ' ' && s[i])
				++i;
		}
		if (!s[i])
			break ;
	}
	free(num_words_in_strs);
	return (strs);
}

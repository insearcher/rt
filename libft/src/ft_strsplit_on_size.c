/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_on_size.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <sbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 01:35:42 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/10 15:28:18 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t	*get_lens_arr(const char *s, size_t num_words)
{
	size_t	*len_arr;
	size_t	i;
	size_t	j;

	len_arr = (size_t *)ft_memalloc(sizeof(size_t) * num_words);
	i = -1;
	j = -1;
	while (s[++i])
	{
		if (s[i] != ' ')
		{
			len_arr[++j] = ft_wordlen(&s[i], ' ');
			i += len_arr[j];
		}
		if (!s[i])
			break ;
	}
	return (len_arr);
}

static size_t	*num_join_free(size_t *arr, size_t num, size_t size)
{
	size_t	*tmp_arr;
	size_t	i;

	if (size == 1)
	{
		arr = (size_t *)malloc(sizeof(size_t));
		arr[0] = num;
		return (arr);
	}
	i = -1;
	tmp_arr = arr;
	arr = (size_t *)malloc(sizeof(size_t) * size);
	while (++i < size - 1)
		arr[i] = tmp_arr[i];
	arr[i] = num;
	if (tmp_arr)
		free(tmp_arr);
	return (arr);
}

static size_t	*get_nwiss(size_t *len_arr,
						size_t num_word, size_t s_len, size_t *num_strs)
{
	size_t *nwiss;
	size_t i;
	size_t len;
	size_t nwis;

	i = -1;
	len = 0;
	nwis = 0;
	nwiss = NULL;
	while (++i < num_word)
		if ((len += len_arr[i] + 1) <= s_len + 1)
			((++nwis && i + 1 == num_word) ?
				nwiss = num_join_free(nwiss, nwis, ++(*num_strs)) : 0);
		else
		{
			len = 0;
			if (++(*num_strs) && nwis == 0)
				nwiss = num_join_free(nwiss, 1, *num_strs);
			else if (--i || 1)
			{
				nwiss = num_join_free(nwiss, nwis, *num_strs);
				nwis = 0;
			}
		}
	return (nwiss);
}

char			**ft_strsplit_on_size(const char *s, size_t sl, size_t *nss)
{
	size_t	*arr_lens;
	size_t	*nwiss;
	size_t	num_word;

	if (!s)
		return (NULL);
	num_word = ft_wordscnt(s, ' ');
	arr_lens = get_lens_arr(s, num_word);
	*nss = 0;
	nwiss = get_nwiss(arr_lens, num_word, sl, nss);
	free(arr_lens);
	return (get_strs(s, nss, nwiss));
}

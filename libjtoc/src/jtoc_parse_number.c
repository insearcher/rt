/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jtoc_parse_number.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 21:20:00 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/18 21:20:00 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libjtoc.h"

static void		jtoc_atof_fraction(const char *str, int i, int s, float *res)
{
	float	b;

	b = 0.1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		*res += (str[i++] - '0') * b * s;
		b /= 10;
	}
}

static void		jtoc_atof(const char *str, float *res)
{
	int		sign;
	int		i;

	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		++i;
	if (str[i] == '-')
	{
		sign = -1;
		++i;
	}
	while (str[i] >= '0' && str[i] <= '9')
		*res = (*res * 10) + (str[i++] - '0') * sign;
	if (str[i] == '.')
		jtoc_atof_fraction(str, ++i, sign, res);
}

int				jtoc_parse_fractional(t_jnode *p, const char *str, int b, int e)
{
	char	*sub;
	float	*data;

	if (!(sub = ft_strsub(str, b, e - b + 1)))
		return (FUNCTION_FAILURE);
	if (!(data = (float *)malloc(sizeof(float))))
	{
		free(sub);
		return (FUNCTION_FAILURE);
	}
	jtoc_atof(sub, data);
	p->data = (void *)data;
	printf("p: %f\n", *data);
	free(sub);
	return (FUNCTION_SUCCESS);
}

int				jtoc_parse_integer(t_jnode *p, const char *str, int b, int e)
{
	char	*sub;
	int		*data;

	if (!(sub = ft_strsub(str, b, e - b + 1)))
		return (FUNCTION_FAILURE);
	if (!(data = (int *)malloc(sizeof(int))))
	{
		free(sub);
		return (FUNCTION_FAILURE);
	}
	*data = ft_atoi(sub);
	p->data = (void *)data;
	free(sub);
	return (FUNCTION_SUCCESS);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lerp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.fr.42>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 21:49:43 by sbednar           #+#    #+#             */
/*   Updated: 2018/11/27 21:50:10 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_lerp(float from, float to, float t)
{
	float	res;

	res = from + (to - from) * t;
	res = fmaxf(res, from);
	res = fminf(res, to);
	return (res);
}
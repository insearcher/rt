/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 05:13:21 by sbecker           #+#    #+#             */
/*   Updated: 2019/04/19 16:40:40 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilits.h"

t_color     get_rgb(int r, int g, int b)
{
	t_color color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

t_color		rgb_mult_num(t_color rgb, float num)
{
	rgb.r *= num;
	rgb.g *= num;
	rgb.b *= num;

	rgb.r = rgb.r > 255 ? 255 : rgb.r;
	rgb.g = rgb.g > 255 ? 255 : rgb.g;
	rgb.b = rgb.b > 255 ? 255 : rgb.b;
	return (rgb);
}

t_color     rgb_plus(t_color rgb1, t_color rgb2)
{
    t_color new_rgb;

    new_rgb.r = rgb1.r + rgb2.r;
    new_rgb.g = rgb1.g + rgb2.g;
    new_rgb.b = rgb1.b + rgb2.b;
    return (new_rgb);
}

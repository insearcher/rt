/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 03:01:47 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/03 19:48:39 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITS_H
# define UTILITS_H

typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

t_color			get_rgb(int r, int g, int b);
t_color			rgb_mult_num(t_color rgb, float num);
t_color			rgb_plus(t_color rgb1, t_color rgb2);

#endif

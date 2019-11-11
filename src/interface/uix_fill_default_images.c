/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uix_fill_default_images.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 21:34:58 by edraugr-          #+#    #+#             */
/*   Updated: 2019/09/29 21:35:00 by edraugr-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

void	rt_uix_fill_default_images(t_ui_main *ui)
{
	ui_main_add_surface_by_path(ui, "images/right.png", "right");
	ui_main_add_surface_by_path(ui, "images/left.png", "left");
}
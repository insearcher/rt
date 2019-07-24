/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbosmer <sbosmer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 04:47:49 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/18 22:25:19 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

void	setup_camera(t_camera *camera)
{
	camera->aspect_ratio = 16.f / 9.f;
	camera->min_distance = 1;
	camera->max_distance = 1000;
	camera->pos = (t_vector3d){0, 0, 0};
}


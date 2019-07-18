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

void	initialization_mlx(t_mlx *mlx)
{
	mlx->width = 800;
	mlx->height = 800;
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, mlx->width, mlx->height, "ray-marching");
	mlx->img_ptr = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	mlx->img_data = mlx_get_data_addr(mlx->img_ptr, &mlx->bpp, &mlx->size_line,
			&mlx->endian);
}

void	initialization_canvas(t_canvas *canvas)
{
	canvas->width = 1;
	canvas->height = 1;
	canvas->min_distance = 1;
	canvas->max_distance = 1000;
	canvas->camera = (t_vector3d){0, 0, 0};
}

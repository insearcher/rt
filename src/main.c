/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbosmer <sbosmer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 18:14:31 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/18 20:35:23 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

void	run_render(t_conf *conf, cl_mem *mem_img,
		cl_mem *mem_objects)
{
	int		err;
	size_t	global_size;

	err = clSetKernelArg(conf->cl.kernel, 0, sizeof(cl_mem), mem_img);
	err |= clSetKernelArg(conf->cl.kernel, 1, sizeof(int), &conf->mlx.width);
	err |= clSetKernelArg(conf->cl.kernel, 2, sizeof(int), &conf->mlx.height);
	err |= clSetKernelArg(conf->cl.kernel, 3, sizeof(int), &conf->objects_num);
	err |= clSetKernelArg(conf->cl.kernel, 4, sizeof(t_canvas), &conf->canvas);
	err |= clSetKernelArg(conf->cl.kernel, 5, sizeof(cl_mem), mem_objects);
	if (err != 0)
		ft_printf("set kernel arg - error\n");
	global_size = conf->mlx.width * conf->mlx.height;
	err = clEnqueueNDRangeKernel(conf->cl.queue, conf->cl.kernel, 1, NULL,
			&global_size, NULL, 0, NULL, NULL);
	if (err != 0)
		ft_printf("NDR - error\n");
	err = clEnqueueReadBuffer(conf->cl.queue, *mem_img, CL_TRUE, 0,
			conf->mlx.size_line * conf->mlx.height,
			conf->mlx.img_data, 0, NULL, NULL);
	if (err != 0)
		ft_printf("read buffer - error\n");
}

void	get_mem_for_render(t_conf *conf, cl_mem *mem_img,
		cl_mem *mem_objects)
{
	int	err;

	*mem_img = clCreateBuffer(conf->cl.context, CL_MEM_READ_WRITE,
			conf->mlx.size_line * conf->mlx.height, NULL, &err);
	*mem_objects = clCreateBuffer(conf->cl.context, CL_MEM_READ_ONLY,
			sizeof(t_object3d) * conf->objects_num, NULL, &err);
	err = clEnqueueWriteBuffer(conf->cl.queue, *mem_objects, CL_TRUE, 0,
			sizeof(t_object3d) * conf->objects_num,
			conf->objects, 0, NULL, NULL);
	if (err != 0)
		ft_printf("create buffer - error\n");
}

int		refresh(t_conf *conf)
{
	cl_mem		mem_img;
	cl_mem		mem_objects;
	int			err;

	get_mem_for_render(conf, &mem_img, &mem_objects);
	run_render(conf, &mem_img, &mem_objects);
	mlx_clear_window(conf->mlx.mlx, conf->mlx.win);
	mlx_put_image_to_window(conf->mlx.mlx, conf->mlx.win,
			conf->mlx.img_ptr, 0, 0);
	return (0);
}

void	initialization_scene(t_conf	*conf)
{
	t_object3d	*objects;

	conf->objects_num = 1;
	objects = (t_object3d *)malloc(sizeof(t_object3d) * conf->objects_num);
	objects[0].type = 1;
	objects[0].radius = 2;
	objects[0].center = (t_vector3d){0, 0, 4};
	conf->objects = objects;
}

int		main()
{
	t_conf		conf;

	initialization_cl(&conf.cl);
	initialization_scene(&conf);
	initialization_canvas(&conf.canvas);
	initialization_mlx(&conf.mlx);
	refresh(&conf);
	mlx_loop(conf.mlx.mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_cl.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbosmer <sbosmer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 22:06:08 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/18 21:39:26 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

void		get_files_buf(char **program_buf, size_t *program_size)
{
	program_buf[0] = get_program_buf("utilits_cl/math_vec.cl",
			&program_size[0]);
	program_buf[1] = get_program_buf("utilits_cl/color.cl", &program_size[1]);
	program_buf[2] = get_program_buf("srcs/render.cl", &program_size[2]);
	program_buf[3] = get_program_buf("srcs/get_cam_ray.cl", &program_size[3]);
	program_buf[4] = get_program_buf("srcs/ray_marching.cl", &program_size[4]);
//	program_buf[4] = get_program_buf("srcs/sphere.cl", &program_size[4]);
}

cl_program	create_program(cl_context context)
{
	cl_program	program;
	char		**program_buf;
	size_t		*program_size;
	int			files_num;
	int			err;

	files_num = 5;
	program_buf = (char**)malloc(sizeof(char*) * files_num);
	program_size = (size_t*)malloc(sizeof(size_t) * files_num);
	get_files_buf(program_buf, program_size);
	program = clCreateProgramWithSource(context, files_num,
			(const char**)program_buf, (const size_t*)program_size, &err);
	if (err != 0)
		ft_printf("create program - error\n");
	err = -1;
	while (++err < files_num)
		free(program_buf[err]);
	free(program_buf);
	free(program_size);
	return (program);
}

cl_kernel	get_kernel(cl_device_id *device, cl_context context)
{
	cl_program	program;
	int			err;
	cl_kernel	kernel;
	char		*log;
	size_t		log_size;

	program = create_program(context);
	err = clBuildProgram(program, 1, device, "-I includes/", NULL, NULL);
	if (err != 0)
	{
		clGetProgramBuildInfo(program, *device, CL_PROGRAM_BUILD_LOG,
				0, NULL, &log_size);
		log = (char*)malloc(log_size);
		clGetProgramBuildInfo(program, *device,
				CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
		ft_printf("build program - error (%d)\n", err);
		ft_printf("%s\n", log);
	}
	kernel = clCreateKernel(program, "render", &err);
	if (err != 0)
		ft_printf("create kernel - error\n");
	return (kernel);
}

void		initialization_cl(t_cl *cl)
{
	cl_device_id	device;
	int				err;

	device = get_device_id();
	cl->context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
	if (err != 0)
		ft_printf("create context - bad\n");
	cl->queue = clCreateCommandQueue(cl->context, device, 0, &err);
	if (err != 0)
		ft_printf("create command queue - bad\n");
	cl->kernel = get_kernel(&device, cl->context);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits_for_initialization_cl.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbosmer <sbosmer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 19:18:14 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/03 21:03:28 by sbosmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

cl_device_id	get_device_id(void)
{
	cl_platform_id	platform;
	cl_device_id	device;
	int				err;

	err = clGetPlatformIDs(1, &platform, NULL);
	if (err != 0)
		ft_printf("Get platform - error\n");
	err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
	if (err != 0)
		ft_printf("Get device id - error\n");
	return (device);
}

char			*get_program_buf(const char *name, size_t *program_size)
{
	size_t	file_size;
	FILE	*fd;
	char	*buf;

	fd = fopen(name, "r");
	if (!fd)
		ft_printf("Open kernel file '%s' - error\n", name);
	fseek(fd, 0, SEEK_END);
	file_size = ftell(fd);
	rewind(fd);
	buf = (char*)malloc(file_size + 1);
	fread(buf, sizeof(char), file_size, fd);
	buf[file_size] = '\0';
	fclose(fd);
	*program_size = file_size;
	return (buf);
}

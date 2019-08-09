/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_raycast.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 17:50:06 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/23 17:50:07 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_RAYCAST_H
# define RT_RAYCAST_H

# include "rt.h"
# include "rt_object.h"

# include "rt_raycast_hit.h"

# define DEFAULT_LAYER			0
# define IGNORE_RAYCAST_LAYER	1

int		rt_raycast(t_ui_main *ui, void *a);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_pp.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 17:50:06 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/23 17:50:07 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_PPNODE_H
# define RT_PPNODE_H

#include "rt.h"

//enum					e_pp_type
//{
//	pp_monohrome = 1,
//	pp_anagliph,
//	pp_blur,
//	pp_ordered_dithering
//};
//
//union					u_pp_params
//{
//	t_sphere			sphere;
//	t_box				box;
//	t_round_box			round_box;
//	t_torus				torus;
//	t_capped_torus		capped_torus;
//	t_link				link;
//	t_cylinder			cylinder;
//	t_cone				cone;
//	t_plane				plane;
//	t_octahedron		octahedron;
//	t_mandelbulb		mandelbulb;
//	t_mandelbox			mandelbox;
//	t_menger_sponge     menger_sponge;
//};

typedef struct			s_ppnode
{
	cl_kernel			*kernel;
//	enum e_pp_type		type;
//	union u_pp_oparams	params;
}						t_ppnode;

#endif

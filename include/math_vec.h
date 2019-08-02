/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_vec.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 19:47:50 by sbecker           #+#    #+#             */
/*   Updated: 2019/07/03 19:47:52 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_VEC_H
# define MATH_VEC_H

# ifndef OPENCL___
# include <OpenCL/opencl.h>
# include <math.h>
//float			mv_scalar_mult(const cl_float3 a, const cl_float3 b);
//cl_float3		mv_get_vector3d(float x, float y, float z);
//cl_float3		mv_minus(const cl_float3 a, const cl_float3 b);
//cl_float3		mv_plus(const cl_float3 a, const cl_float3 b);
//cl_float3		mv_mult_num(const cl_float3 a, float num);
//cl_float3		mv_dev_num(const cl_float3 a, float num);
//float			mv_length(const cl_float3 a);
//cl_float3		mv_normalize(const cl_float3 a);
//cl_float3		mv_mult(cl_float3 a, cl_float3 b);
//cl_float3		mv_inverse(const cl_float3 a);
#else
float			mv_scalar_mult(const float3 a, const float3 b);
float3		mv_get_vector3d(float x, float y, float z);
float3		mv_minus(const float3 a, const float3 b);
float3		mv_plus(const float3 a, const float3 b);
float3		mv_mult_num(const float3 a, float num);
float3		mv_dev_num(const float3 a, float num);
float			mv_length(const float3 a);
float3		mv_normalize(const float3 a);
float3		mv_mult(float3 a, float3 b);
float3		mv_inverse(const float3 a);
float3		ft_mod(float3 a, float3 b);
float		ft_mod2(float a, float b);

#endif

#endif

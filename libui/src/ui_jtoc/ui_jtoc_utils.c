/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_jtoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edraugr- <edraugr-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 20:05:37 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/24 19:40:51 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

int	ui_jtoc_sdl_log_error(const char *p, const int id)
{
	SDL_Log("%s ----> ERROR <---- %s", KRED, KNRM);
	SDL_Log("INCORRECT: %s%s%s%s%s",
		p,
		id < 0 ? "" : " IN ID = ",
		KGRN,
		id < 0 ? "" : ft_itoa(id),
		KNRM);
	return (FUNCTION_FAILURE);
}

int	ui_jtoc_isnum(enum e_type type)
{
	return (type == fractional || type == integer);
}

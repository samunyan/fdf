/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:29:41 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/26 13:51:26 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	set_point(t_3d *point, float x, float y, float z)
{
	point->x = x;
	point->y = y;
	point->z = z;
}

void	vec_copy(t_3d *src, t_3d *dst)
{
	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
}

t_3d	*get_3dpoint(t_vertex *point, int coord_sys)
{
	if (coord_sys == LOCAL)
		return (&point->local);
	if (coord_sys == WORLD)
		return (&point->world);
	else
		return (NULL);
}

t_2d	*get_2dpoint(t_vertex *point, int coord_sys)
{
	if (coord_sys == RASTER)
		return (&point->raster);
	if (coord_sys == SCREEN)
		return (&point->screen);
	else
		return (NULL);
}

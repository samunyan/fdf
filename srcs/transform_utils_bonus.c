/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:12:09 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/26 13:51:16 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	apply_transform(t_scene *scene, float mat[4][4], int from, int to)
{
	int		i;
	int		j;
	t_3d	*point_from;
	t_3d	tmp;
	t_3d	*point_to;

	i = 0;
	while (i < scene->map.dim_y)
	{
		j = 0;
		while (j < scene->map.dim_x)
		{
			point_from = get_3dpoint(&scene->map.points[i][j], from);
			point_to = get_3dpoint(&scene->map.points[i][j], to);
			vec_copy(point_from, &tmp);
			vec_mult_mat(&tmp, mat, point_to);
			j++;
		}
		i++;
	}
}

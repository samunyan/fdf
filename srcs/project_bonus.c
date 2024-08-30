/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:12:14 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/26 13:51:11 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	plane_to_spherical(t_scene *scene)
{
	int		i;
	int		j;
	float	lon;
	float	lat;

	i = 0;
	while (i < scene->map.dim_x)
	{
		lon = ft_lerp(-M_PI, M_PI, (double)(i) / (scene->map.dim_x - 1));
		j = 0;
		while (j < scene->map.dim_y)
		{
			lat = ft_lerp(-M_PI_2, M_PI_2, \
					(double)(j) / (scene->map.dim_y - 1));
			set_point(&scene->map.points[j][i].world, \
			(scene->map.dim_x * 0.5) * sin(lon) * cos(lat), \
			(scene->map.dim_x * 0.5) * sin(lon) * sin(lat), \
			((scene->map.dim_x * 0.5) + scene->map.points[j][i].local.z) \
																* cos(lon));
			j++;
		}
		i++;
	}
}

void	project(t_scene *scene, t_3d *p_world, t_2d *p_screen)
{
	if (scene->type_of_projection == ISO)
	{
		p_screen->x = (p_world->x - p_world->y) * cos(M_PI_2 / 3);
		p_screen->y = (p_world->x + p_world->y) * sin(M_PI_2 / 3) - p_world->z;
	}
	else
	{
		p_screen->x = p_world->x;
		p_screen->y = p_world->y;
	}
	p_screen->x += scene->map.pos_x;
	p_screen->y += scene->map.pos_y;
}

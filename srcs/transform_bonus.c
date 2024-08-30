/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:29:57 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/26 13:51:15 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	geometry_to_origin(t_scene *scene)
{
	float	m[4][4];

	mat_identity(m);
	mat_translate(m, (float)-scene->map.dim_x * 0.5f, \
	(float)-scene->map.dim_y * 0.5f, 0);
	apply_transform(scene, m, LOCAL, LOCAL);
}

void	local_to_world(t_scene *scene)
{
	float	m[4][4];

	if (scene->map.toggle_spherical)
		plane_to_spherical(scene);
	mat_identity(m);
	mat_scale(m, scene->map.scale, scene->map.scale, scene->map.scale);
	mat_rotate(m, scene->map.rot_x, scene->map.rot_y, scene->map.rot_z);
	if (scene->map.toggle_spherical)
		apply_transform(scene, m, WORLD, WORLD);
	else
		apply_transform(scene, m, LOCAL, WORLD);
}

void	world_to_screen(t_scene *scene)
{
	int		i;
	int		j;
	t_3d	*p_world;
	t_2d	*p_screen;

	i = 0;
	while (i < scene->map.dim_y)
	{
		j = 0;
		while (j < scene->map.dim_x)
		{
			p_world = get_3dpoint(&scene->map.points[i][j], WORLD);
			p_screen = get_2dpoint(&scene->map.points[i][j], SCREEN);
			project(scene, p_world, p_screen);
			j++;
		}
		i++;
	}
}

void	screen_to_raster(t_scene *scene)
{
	t_2d	*screen;
	t_2d	*raster;
	int		i;
	int		j;

	i = 0;
	while (i < scene->map.dim_y)
	{
		j = 0;
		while (j < scene->map.dim_x)
		{
			screen = get_2dpoint(&scene->map.points[i][j], SCREEN);
			raster = get_2dpoint(&scene->map.points[i][j], RASTER);
			raster->x = screen->x + (float)scene->width * 0.5f;
			raster->y = screen->y + (float)scene->height * 0.5f;
			j++;
		}
		i++;
	}
}

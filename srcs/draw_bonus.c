/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:53:36 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/26 13:50:43 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	draw_line(t_vertex *from, t_vertex *to, t_scene *scene)
{
	float	steps;
	int		i;
	t_2d	pixel;
	t_2d	delta;

	delta.x = to->raster.x - from->raster.x;
	delta.y = to->raster.y - from->raster.y;
	steps = get_steps(delta.x, delta.y);
	delta.x /= steps;
	delta.y /= steps;
	pixel.x = from->raster.x;
	pixel.y = from->raster.y;
	i = 0;
	while (i < (int)roundf(steps))
	{
		if (is_valid_pixel(&pixel, scene->width, scene->height))
			image_pixel_put(&scene->images[scene->current_image], \
			(int)roundf(pixel.x), (int)roundf(pixel.y), \
			get_gradient_color(from->color, to->color, steps, (float)i));
		pixel.x += delta.x;
		pixel.y += delta.y;
		i++;
	}
}

void	draw_map(t_scene *scene)
{
	int		i;
	int		j;

	fill_background(&scene->images[scene->current_image], scene->width, \
					scene->height, DEFAULT_BG_COLOR);
	i = 0;
	while (i < scene->map.dim_y)
	{
		j = 0;
		while (j < scene->map.dim_x)
		{
			if (j != scene->map.dim_x - 1)
				draw_line(&scene->map.points[i][j], \
				&scene->map.points[i][j + 1], scene);
			if (i != scene->map.dim_y - 1)
				draw_line(&scene->map.points[i + 1][j], \
				&scene->map.points[i][j], scene);
			j++;
		}
		i++;
	}
}

void	fill_background(t_img *image, int width, int height, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			image_pixel_put(image, x, y, color);
			x++;
		}
		y++;
	}
}

void	print_menu(t_scene *scene)
{
	mlx_string_put(scene->mlx, scene->win, 20, 60, DEFAULT_MENU_COLOR, \
	"Zoom : -/+");
	mlx_string_put(scene->mlx, scene->win, 20, 80, DEFAULT_MENU_COLOR, \
	"Move : Arrows");
	mlx_string_put(scene->mlx, scene->win, 20, 100, DEFAULT_MENU_COLOR, \
	"Rotate X : 1/2");
	mlx_string_put(scene->mlx, scene->win, 20, 120, DEFAULT_MENU_COLOR, \
	"Rotate Y : 4/5");
	mlx_string_put(scene->mlx, scene->win, 20, 140, DEFAULT_MENU_COLOR, \
	"Rotate Z:  7/8");
	mlx_string_put(scene->mlx, scene->win, 20, 180, DEFAULT_MENU_COLOR, \
	"Isometric : I");
	mlx_string_put(scene->mlx, scene->win, 20, 200, DEFAULT_MENU_COLOR, \
	"Parallel : P");
	mlx_string_put(scene->mlx, scene->win, 20, 220, DEFAULT_MENU_COLOR, \
	"Spherical : S");
	mlx_string_put(scene->mlx, scene->win, 20, 260, DEFAULT_MENU_COLOR, \
	"Reset : R");
	mlx_string_put(scene->mlx, scene->win, 20, 300, DEFAULT_MENU_COLOR, \
	"Toggle menu : M");
}

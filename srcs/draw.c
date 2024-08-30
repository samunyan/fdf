/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:53:36 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/26 13:50:48 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
			(int)roundf(pixel.x), (int)roundf(pixel.y), DEFAULT_COLOR);
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

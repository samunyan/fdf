/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:53:36 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/26 13:50:46 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

bool	is_valid_pixel(t_2d *pixel, int width, int height)
{
	int	x;
	int	y;

	x = (int)roundf(pixel->x);
	y = (int)roundf(pixel->y);
	return (!(x > width - 1 || y > height - 1 || x < 0 || y < 0));
}

float	get_steps(float delta_x, float delta_y)
{
	if (fabsf(delta_x) > fabsf(delta_y))
		return (fabsf(delta_x));
	else
		return (fabsf(delta_y));
}

void	image_pixel_put(t_img *image, int x, int y, int color)
{
	char	*dst;
	size_t	offset;

	offset = y * image->line_length + x * (image->bits_per_pixel / 8);
	dst = image->addr + offset;
	*(unsigned int *)dst = color;
}

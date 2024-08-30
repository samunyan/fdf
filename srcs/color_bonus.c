/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:07:44 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/26 13:50:40 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static int	get_red(int color)
{
	return (color >> 16 & 0xFF);
}

static int	get_green(int color)
{
	return (color >> 8 & 0xFF);
}

static int	get_blue(int color)
{
	return (color & 0xFF);
}

int	get_gradient_color(int start_color, int end_color, float len, float pos)
{
	int		red;
	int		green;
	int		blue;
	double	t;

	t = pos / len;
	red = (int)ft_lerp(get_red(start_color), get_red(end_color), t);
	green = (int)ft_lerp(get_green(start_color), get_green(end_color), t);
	blue = (int)ft_lerp(get_blue(start_color), get_blue(end_color), t);
	return ((red << 16) | (green << 8) | blue);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:12:14 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/26 13:51:13 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	project(t_3d *p_world, t_2d *p_screen)
{
	p_screen->x = (p_world->x - p_world->y) * cos(M_PI_2 / 3);
	p_screen->y = (p_world->x + p_world->y) * sin(M_PI_2 / 3) - p_world->z;
}

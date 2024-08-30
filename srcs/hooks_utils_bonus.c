/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:54:13 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/26 22:19:53 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	update_position(int keycode, t_scene *scene)
{
	if (keycode == KEY_LEFT)
		scene->map.pos_x -= 10;
	else if (keycode == KEY_RIGHT)
		scene->map.pos_x += 10;
	else if (keycode == KEY_DOWN)
		scene->map.pos_y += 10;
	else if (keycode == KEY_UP)
		scene->map.pos_y -= 10;
	return (1);
}

int	update_scale(unsigned int keycode, t_scene *scene)
{
	if (keycode == KEY_MIN)
		scene->map.scale -= 0.5f;
	else if (keycode == KEY_PLUS)
		scene->map.scale += 0.5f;
	return (1);
}

int	update_rotation(int keycode, t_scene *scene)
{
	if (keycode == KEY_1)
		scene->map.rot_x -= 0.1f;
	else if (keycode == KEY_2)
		scene->map.rot_x += 0.1f;
	else if (keycode == KEY_4)
		scene->map.rot_y -= 0.1f;
	else if (keycode == KEY_5)
		scene->map.rot_y += 0.1f;
	else if (keycode == KEY_7)
		scene->map.rot_z -= 0.1f;
	else if (keycode == KEY_8)
		scene->map.rot_z += 0.1f;
	return (1);
}

int	update_projection(int keycode, t_scene *scene)
{
	if (keycode == KEY_i)
		scene->type_of_projection = ISO;
	else if (keycode == KEY_p)
		scene->type_of_projection = PARALLEL;
	else if (keycode == KEY_s)
	{
		if (scene->map.toggle_spherical == false)
			scene->map.toggle_spherical = true;
		else
			scene->map.toggle_spherical = false;
	}
	else if (keycode == KEY_r)
		reset_map(&scene->map, scene->width, scene->height);
	return (1);
}

int	toggle_menu(int keycode, t_scene *scene)
{
	if (keycode == KEY_m)
	{
		if (scene->toggle_menu == false)
			scene->toggle_menu = true;
		else
			scene->toggle_menu = false;
	}
	return (1);
}

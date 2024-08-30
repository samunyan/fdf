/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:54:13 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/26 22:19:57 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	close_scene(t_scene *scene)
{
	free_scene(&scene);
	exit(EXIT_SUCCESS);
}

int	hooks_on_keydown(int keycode, t_scene *scene)
{
	if (keycode == KEY_ESC)
		close_scene(scene);
	update_scale(keycode, scene);
	update_rotation(keycode, scene);
	update_position(keycode, scene);
	update_projection(keycode, scene);
	toggle_menu(keycode, scene);
	return (0);
}

void	handle_events(t_scene *scene)
{
	mlx_hook(scene->win, ON_DESTROY, NOTIFY_MASK, close_scene, scene);
	mlx_hook(scene->win, ON_KEYDOWN, KEYPRESS_MASK, hooks_on_keydown, scene);
}

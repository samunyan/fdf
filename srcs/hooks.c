/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:54:13 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/26 13:51:01 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_scene(t_scene *scene)
{
	free_scene(&scene);
	exit(EXIT_SUCCESS);
}

int	hooks_on_keydown(int keycode, t_scene *scene)
{
	if (keycode == KEY_ESC)
		close_scene(scene);
	return (0);
}

void	handle_events(t_scene *scene)
{
	mlx_hook(scene->win, ON_DESTROY, NOTIFY_MASK, close_scene, scene);
	mlx_hook(scene->win, ON_KEYDOWN, KEYPRESS_MASK, hooks_on_keydown, scene);
}

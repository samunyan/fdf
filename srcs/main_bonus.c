/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:29:16 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/26 13:51:06 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	main(int argc, char *argv[])
{
	t_scene	*scene;

	if (argc != 2 || !is_valid_file_extension(argv[1], ".fdf"))
	{
		err_msg(false, 0, USAGE);
		return (2);
	}
	scene = init_scene(DEFAULT_WIDTH, DEFAULT_HEIGHT, argv[1]);
	handle_events(scene);
	mlx_loop_hook(scene->mlx, render_scene, scene);
	mlx_loop(scene->mlx);
}

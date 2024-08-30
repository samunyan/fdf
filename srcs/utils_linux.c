/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_linux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:30:11 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/26 22:12:32 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	render_scene(t_scene *scene)
{
	mlx_clear_window(scene->mlx, scene->win);
	local_to_world(scene);
	world_to_screen(scene);
	screen_to_raster(scene);
	scene->current_image = get_index_of_next_image(scene);
	draw_map(scene);
	mlx_put_image_to_window(scene->mlx, scene->win, \
						(&scene->images[scene->current_image])->img, \
						0, 0);
	return (0);
}

int	get_index_of_next_image(t_scene *scene)
{
	if (scene->current_image == DEFAULT_N_IMAGES - 1)
		return (0);
	else
		return (scene->current_image + 1);
}

void	free_scene(t_scene **scene)
{
	size_t	i;

	if ((*scene)->map.points)
		ft_free_arr((void **)(*scene)->map.points);
	if ((*scene)->images)
	{
		i = 0;
		while (i < DEFAULT_N_IMAGES)
		{
			mlx_destroy_image((*scene)->mlx, (*scene)->images[i].img);
			i++;
		}
		free((*scene)->images);
	}
	if ((*scene)->mlx)
	{
		if ((*scene)->win)
			mlx_destroy_window((*scene)->mlx, (*scene)->win);
		mlx_destroy_display((*scene)->mlx);
		free((*scene)->mlx);
	}
	free(*scene);
	*scene = NULL;
}

bool	is_valid_file_extension(char *filename, char *extension)
{
	char	*tmp;

	tmp = ft_strrchr(filename, '.');
	if (tmp && ft_strcmp(extension, tmp) == 0)
		return (true);
	else
		return (false);
}

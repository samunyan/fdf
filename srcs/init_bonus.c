/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:30:09 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/26 13:51:03 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

t_scene	*init_scene(int width, int height, char *file)
{
	t_scene	*scene;
	int		rt;

	scene = malloc(sizeof(t_scene));
	if (!scene)
	{
		err_msg(true, errno, "malloc in init_scene");
		return (NULL);
	}
	ft_memset(scene, 0, sizeof(t_scene));
	scene->width = width;
	scene->height = height;
	scene->type_of_projection = ISO;
	scene->toggle_menu = true;
	rt = init_map(&scene->map, file, width, height);
	if ((!rt || rt == 2) || !init_display(scene, file) || !init_images(scene))
	{
		free_scene(&scene);
		if (!rt || rt == 2)
			exit(rt <= 0);
		else
			exit(EXIT_FAILURE);
	}
	geometry_to_origin(scene);
	return (scene);
}

int	init_map(t_map *map, char *filename, int width, int height)
{
	char	**data;
	int		ret;

	if (!get_map_dimensions(filename, &map->dim_x, &map->dim_y))
		return (0);
	map->scale = ft_fmin((float)width / (float)map->dim_x, \
							(float)height / (float)map->dim_y) * 0.5f;
	data = get_map_data(filename);
	if (!data)
		return (0);
	if (init_vertex_arrays(map, data))
		ret = 1;
	else
		ret = 0;
	ft_free_arr((void **)data);
	return (ret);
}

int	init_display(t_scene *scene, char *name)
{
	scene->mlx = mlx_init();
	if (!scene->mlx)
	{
		err_msg(false, 0, "Error : mlx_init in init_display");
		return (0);
	}
	scene->win = mlx_new_window(scene->mlx, scene->width, scene->height, name);
	if (!scene->win)
	{
		err_msg(false, 0, "Error : mlx_new_window in init_display");
		return (0);
	}
	return (1);
}

int	init_images(t_scene *scene)
{
	size_t	i;

	scene->images = malloc(sizeof(t_img) * DEFAULT_N_IMAGES);
	if (!scene->images)
	{
		err_msg(true, errno, "malloc in init_images");
		return (0);
	}
	ft_memset(scene->images, 0, sizeof(t_img) * DEFAULT_N_IMAGES);
	i = 0;
	while (i < DEFAULT_N_IMAGES)
	{
		scene->images[i].img = mlx_new_image(scene->mlx, \
							scene->width, scene->height);
		if (!scene->images[i].img)
		{
			err_msg(false, 0, "Error : mlx_new_image in init_images");
			return (0);
		}
		scene->images[i].addr = mlx_get_data_addr(scene->images[i].img, \
		&scene->images[i].bits_per_pixel, &scene->images[i].line_length, \
		&scene->images[i].endian);
		i++;
	}
	return (1);
}

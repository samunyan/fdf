/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:43:27 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/26 13:51:04 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static int	allocate_vertex_arrays(t_map *map)
{
	int	j;

	map->points = malloc(sizeof(t_vertex *) * (map->dim_y + 1));
	if (!map->points)
	{
		err_msg(true, errno, "malloc in allocate_vertex_arrays");
		return (0);
	}
	ft_memset(map->points, 0, sizeof(t_vertex *) * (map->dim_y + 1));
	j = 0;
	while (j < map->dim_y)
	{
		map->points[j] = malloc(sizeof(t_vertex) * map->dim_x);
		if (!map->points[j])
		{
			err_msg(true, errno, "malloc in allocate_vertex_arrays");
			ft_free_arr_until((void **)map->points, j);
			return (0);
		}
		j++;
	}
	return (1);
}

static int	vertex_values_are_valid(t_vertex *vertex, char *token)
{
	char	*color;
	size_t	i;

	if (!ft_atoi_is_valid((int)roundf(vertex->local.z), token))
		return (0);
	i = 0;
	while (token[i])
	{
		token[i] = (char)ft_tolower(token[i]);
		i++;
	}
	color = ft_strstr(token, ",0x");
	if (color && !ft_atoi_base_is_valid(vertex->color, \
				color + ft_strlen(",0x"), BASE_16_LOW))
		return (0);
	return (1);
}

static int	set_vertex_values(t_vertex *vertex, float x, float y, char *token)
{
	char	*color;
	size_t	i;

	set_point(&vertex->local, x, y, ft_atoi(token));
	i = 0;
	while (token[i])
	{
		token[i] = (char)ft_tolower(token[i]);
		i++;
	}
	color = ft_strstr(token, ",0x");
	if (color)
		vertex->color = ft_atoi_base(color + ft_strlen(",0x"), BASE_16_LOW);
	else
		vertex->color = DEFAULT_COLOR;
	if (!vertex_values_are_valid(vertex, token))
	{
		err_msg(false, 0, MAP_ERROR);
		return (0);
	}
	return (1);
}

int	init_vertex_arrays(t_map *map, char **data)
{
	int		i;
	int		j;
	int		k;

	if (!allocate_vertex_arrays(map))
		return (0);
	j = 0;
	while (j < map->dim_y)
	{
		i = 0;
		while (i < map->dim_x)
		{
			k = (map->dim_x * j) + i;
			if (!set_vertex_values(&map->points[j][i], i, j, data[k]))
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:39:20 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/26 13:50:57 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_n_tokens(char *line)
{
	char	**tmp;
	int		j;

	tmp = ft_split_set(line, " \n");
	if (!tmp)
		return (-1);
	j = 0;
	while (tmp[j])
		j++;
	ft_free_arr((void **)tmp);
	return (j);
}

static int	get_map_dimensions_helper(int fd, int *dim_x, int *dim_y)
{
	char	*line;
	int		ret;

	ret = 1;
	while (ret)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (*dim_y == 0)
		{
			*dim_x = get_n_tokens(line);
			if (*dim_x < 0)
				ret = 0;
		}
		if (ret && *dim_y != 0 && get_n_tokens(line) != *dim_x)
		{
			err_msg(false, 0, MAP_ERROR);
			ret = 0;
		}
		(*dim_y)++;
		free(line);
	}
	return (ret);
}

int	get_map_dimensions(char *filename, int *dim_x, int *dim_y)
{
	int		fd;

	fd = open_map_file(filename);
	if (fd < 0)
		return (0);
	if (!get_map_dimensions_helper(fd, dim_x, dim_y))
	{
		close(fd);
		return (0);
	}
	if (close(fd) == -1)
	{
		err_msg(true, errno, "close in get_map_dimensions");
		return (0);
	}
	if (*dim_x == 0)
		return (2);
	return (1);
}

static char	*get_map_data_helper(int fd)
{
	char	*input;
	char	*line;

	input = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		ft_append(&input, ft_skip_space(line));
		free(line);
		if (!input)
		{
			close(fd);
			err_msg(true, errno, "ft_append in get_map_data");
			return (NULL);
		}
	}
	close(fd);
	return (input);
}

char	**get_map_data(char *filename)
{
	char	*input;
	int		fd;
	char	**data;

	fd = open_map_file(filename);
	if (fd < 0)
		return (0);
	input = get_map_data_helper(fd);
	if (!input)
		return (NULL);
	data = ft_split_set(input, "\n\t ");
	if (!data)
		err_msg(true, errno, "ft_split_set in get_map_data");
	free(input);
	return (data);
}

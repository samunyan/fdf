/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:39:20 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/26 13:50:56 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	open_map_file(char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		err_msg(true, errno, filename);
		return (-1);
	}
	return (fd);
}

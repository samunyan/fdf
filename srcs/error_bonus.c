/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 13:35:14 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/26 13:50:49 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	err_msg(bool errnoflag, int errnum, const char *msg)
{
	static char	buf[MAX_LINE];

	ft_memset(buf, 0, MAX_LINE);
	ft_strlcat(buf, msg, ft_strlen(msg) + 1);
	if (errnoflag)
	{
		ft_strlcat(buf, " : ", ft_strlen(buf) + ft_strlen(" : ") + 1);
		ft_strlcat(buf, strerror(errnum), \
			ft_strlen(buf) + ft_strlen(strerror(errnum)) + 1);
	}
	ft_strlcat(buf, "\n", ft_strlen(buf) + ft_strlen("\n") + 1);
	if (write(STDERR_FILENO, buf, ft_strlen(buf)) == -1)
		perror("write in err_msg");
}

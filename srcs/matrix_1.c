/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:29:34 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/26 13:51:09 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mat_mult_mat(float mat1[4][4], float mat2[4][4], float dst[4][4])
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			dst[i][j] = mat1[i][0] * mat2[0][j] + mat1[i][1] * mat2[1][j] \
				+ mat1[i][2] * mat2[2][j] + mat1[i][3] * mat2[3][j];
			j++;
		}
		i++;
	}
}

void	vec_mult_mat(t_3d *src, float mat[4][4], t_3d *dst)
{
	dst->x = src->x * mat[0][0] + src->y * mat[1][0] \
		+ src->z * mat[2][0] + mat[3][0];
	dst->y = src->x * mat[0][1] + src->y * mat[1][1] \
		+ src->z * mat[2][1] + mat[3][1];
	dst->z = src->x * mat[0][2] + src->y * mat[1][2] \
		+ src->z * mat[2][2] + mat[3][2];
}

void	mat_identity(float mat[4][4])
{
	ft_memset(mat, 0, sizeof(float) * 16);
	mat[0][0] = 1;
	mat[1][1] = 1;
	mat[2][2] = 1;
	mat[3][3] = 1;
}

void	mat_translate(float mat[4][4], float tx, float ty, float tz)
{
	float	tmat[4][4];

	mat_identity(tmat);
	tmat[3][0] = tx;
	tmat[3][1] = ty;
	tmat[3][2] = tz;
	mat_mult_mat(mat, tmat, mat);
}

void	mat_scale(float mat[4][4], float sx, float sy, float sz)
{
	float	smat[4][4];

	mat_identity(smat);
	smat[0][0] = sx;
	smat[1][1] = sy;
	smat[2][2] = sz;
	mat_mult_mat(mat, smat, mat);
}

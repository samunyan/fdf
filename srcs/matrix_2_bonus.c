/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:29:34 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/26 13:51:10 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	mat_rot_x(float mat[4][4], float alpha)
{
	mat_identity(mat);
	mat[1][1] = cos(alpha);
	mat[1][2] = sin(alpha);
	mat[2][1] = -sin(alpha);
	mat[2][2] = cos(alpha);
}

static void	mat_rot_y(float mat[4][4], float beta)
{
	mat_identity(mat);
	mat[0][0] = cos(beta);
	mat[0][2] = -sin(beta);
	mat[2][0] = sin(beta);
	mat[2][2] = cos(beta);
}

static void	mat_rot_z(float mat[4][4], float gamma)
{
	mat_identity(mat);
	mat[0][0] = cos(gamma);
	mat[0][1] = sin(gamma);
	mat[1][0] = -sin(gamma);
	mat[1][1] = cos(gamma);
}

void	mat_rotate(float mat[4][4], float alpha, float beta, float gamma)
{
	float	rot_x[4][4];
	float	rot_y[4][4];
	float	rot_z[4][4];
	float	tmp1[4][4];
	float	tmp2[4][4];

	mat_rot_x(rot_x, alpha);
	mat_rot_y(rot_y, beta);
	mat_rot_z(rot_z, gamma);
	mat_mult_mat(mat, rot_x, tmp1);
	mat_mult_mat(tmp1, rot_y, tmp2);
	mat_mult_mat(tmp2, rot_z, mat);
}

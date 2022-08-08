/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_calc_mtx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 13:37:51 by wendelin          #+#    #+#             */
/*   Updated: 2022/08/08 20:25:01 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Creates 4x4 matrix and fills it with 0.0
t_mtx	*new_mtx(void)
{
	t_mtx	*empty_mtx;
	int		i;
	int		j;

	empty_mtx = (t_mtx *)malloc(sizeof(t_mtx));
	if (empty_mtx == NULL)
		return (NULL);
	j = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			empty_mtx->m[j][i] = 0.0;
			i++;
		}
		j++;
	}
	return (empty_mtx);
}

//creates a rotation matrix with the corresponding angles
t_mtx	*create_rotmtx(float y, float b, float a)
{
	t_mtx	*rotmtx;

	a = a * (M_PI / 360);
	y = y * (M_PI / 360);
	b = b * (M_PI / 360);
	rotmtx = NULL;
	rotmtx = new_mtx();
	if (rotmtx == NULL)
		return (NULL);
	rotmtx->m[0][0] = (cos(a) * cos(b));
	rotmtx->m[0][1] = (cos(a) * sin(b) * sin(y) - sin(a) * cos(y));
	rotmtx->m[0][2] = (cos(a) * sin(b) * cos(y) + sin(a) * sin(y));
	rotmtx->m[1][0] = (sin(a) * cos(b));
	rotmtx->m[1][1] = (sin(a) * sin(b) * sin(y) + cos(a) * cos(y));
	rotmtx->m[1][2] = (sin(a) * sin(b) * cos(y) - cos(a) * sin(y));
	rotmtx->m[2][0] = (-sin(b));
	rotmtx->m[2][1] = (cos(b) * sin(y));
	rotmtx->m[2][2] = (cos(b) * cos(y));
	return (rotmtx);
}

// Calculates the multiplcation of a tripple vector with a 3x3 matrix
// If it is an Orthogonal matrix => ortho=1, which means a 4x4 matrix, w is
// the fourth value which divides the other tree results
//(see ORthogonal matrix)
void	mxp(t_mtx c, t_point in, t_point *out)
{
	out->x = (in.x * c.m[0][0] + in.y
			* c.m[0][1] + in.z * c.m[0][2] + c.m[0][3]);
	out->y = (in.x * c.m[1][0] + in.y
			* c.m[1][1] + in.z * c.m[1][2] + c.m[1][3]);
	out->z = (in.x * c.m[2][0] + in.y
			* c.m[2][1] + in.z * c.m[2][2] + c.m[2][3]);
}

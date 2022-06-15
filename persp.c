/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   persp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 09:32:35 by wweisser          #+#    #+#             */
/*   Updated: 2022/06/15 15:27:38 by wendelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

// Creates 4x4 matrix and fills it with 0.o
mtx	createmtx(void)
{
	mtx	emptyMtx;
	int	i;
	int	j;

	j = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			emptyMtx.m[j][i] = 0.0;
			i++;
		}
		j++;
	}
	return (emptyMtx);
}

// Calculates the multiplcation of a tripple vector with a 3x3 matrix
// If it is an Orthogonal matrix => ortho=1, which means a 4x4 matrix, w is
// the fourth value which divides the other tree results
//(see ORthogonal matrix)
void	mxp(mtx *c, float in[3], float *out[3], int ortho)
{
	int		i;
	float	w;

	*out[0] = (in[0] * c->m[0][0] + in[1] * c->m[0][1] + in[2] * c->m[0][2] + c->m[0][3]);
	*out[1] = (in[0] * c->m[1][0] + in[1] * c->m[1][1] + in[2] * c->m[1][2] + c->m[1][3]);
	*out[2] = (in[0] * c->m[2][0] + in[1] * c->m[2][1] + in[2] * c->m[2][2] + c->m[2][3]);
	if (ortho == 1 && w != 0)
	{
		w = (in[0] * c->m[3][2] + in[1] * c->m[3][2] + in[2] * c->m[3][2] + c->m[3][3]);
		*out[0] = *out[0] / w;
		*out[1] = *out[1] / w;
		*out[2] = *out[2] / w;
	}
}

// matrix mulitplies a triangle. If orthogoinal matrix => ortho=1
void	mxt(mtx *c, trigon in, trigon *out, int ortho)
{
	mpx(c, in.p0, out->p0, ortho);
	mpx(c, in.p1, out->p1, ortho);
	mpx(c, in.p2, out->p2, ortho);
}

//creates an Orthonormal matrix. Values for znear are set to 0.1
mtx	othromtx(float width, float length, float zfar, float viewangle)
{
	mtx	orthomtx;

	orthomtx = createmtx();
	orthomtx.m[0][0] = (width/length) * 1/(tan(viewangle / 2));
	orthomtx.m[1][1] = 1 / (tan(viewangle / 2));
	orthomtx.m[2][2] = zfar / (zfar - 0.1);
	orthomtx.m[2][3] = -(zfar / (zfar - 0.1) * 0.1);
	orthomtx.m[3][2] = 1;
}

//creates a rotation matrix
void rotmtx(mtx *rotmtx, float y, float ß, float a)
{
    rotmtx->m[0][0] = (cos(a) * cos(ß));
    rotmtx->m[0][1] = (cos(a) * sin(ß) * sin(y) - sin(a) * cos(y));
    rotmtx->m[0][2] = (cos(a) * sin(ß) * cos(y) + cos(a) * sin(y));
    rotmtx->m[1][0] = (sin(a) * cos(ß));
    rotmtx->m[1][1] = (sin(a) * sin(ß) * sin(y) + cos(a) * cos(y));
    rotmtx->m[1][2] = (sin(a) * sin(ß) * cos(y) - cos(a) * sin(y));
    rotmtx->m[2][0] = (-sin(ß));
    rotmtx->m[2][1] = (sin(a) * cos(ß));
    rotmtx->m[2][2] = (cos(a * cos(ß)));
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   persp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 09:32:35 by wweisser          #+#    #+#             */
/*   Updated: 2022/06/19 21:19:48 by wweisser         ###   ########.fr       */
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
void	mxp(mtx *c, point in, point *out, int ortho)
{
	float	w;

	out->x = (in.x * c->m[0][0] + in.y * c->m[0][1] + in.z * c->m[0][2] + c->m[0][3]);
	out->y = (in.x * c->m[1][0] + in.y * c->m[1][1] + in.z * c->m[1][2] + c->m[1][3]);
	out->z = (in.x * c->m[2][0] + in.y * c->m[2][1] + in.z * c->m[2][2] + c->m[2][3]);
	if (ortho == 1 && w != 0)
	{
		w = (in.x * c->m[3][2] + in.y * c->m[3][2] + in.z * c->m[3][2] + c->m[3][3]);
		// *out[0] = *out[0] / w;
		// *out[1] = *out[1] / w;
		// *out[2] = *out[2] / w;
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
mtx	othromtx(double width, double length, double zfar, double viewangle)
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
void create_rotmtx(mtx *rotmtx, double y, double ß, double a)
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
}

void	trans_op(point in, point *out, image *im)
{
	mtx	rotmtx;

	create_rotmtx(&rotmtx, im->angle[0], im->angle[1], im->angle[2]);
	mxp(&rotmtx, in, out, 0);
}


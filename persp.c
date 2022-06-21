/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   persp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 09:32:35 by wweisser          #+#    #+#             */
/*   Updated: 2022/06/21 19:19:11 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

// Creates 4x4 matrix and fills it with 0.0
mtx	*new_mtx(void)
{
	mtx	*emptyMtx;
	int	i;
	int	j;

	emptyMtx = (mtx *)malloc(sizeof(mtx));
	if (emptyMtx == NULL)
		return (NULL);
	j = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			emptyMtx->m[j][i] = 0.0;
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
void	mxp(mtx c, point in, point *out, int ortho)
{
	float	w;

	w = 1;
	out->x = (in.x * c.m[0][0] + in.y * c.m[0][1] + in.z * c.m[0][2] + c.m[0][3]);
	out->y = (in.x * c.m[1][0] + in.y * c.m[1][1] + in.z * c.m[1][2] + c.m[1][3]);
	out->z = (in.x * c.m[2][0] + in.y * c.m[2][1] + in.z * c.m[2][2] + c.m[2][3]);
	if (ortho == 1 && w != 0)
	{
		w = (in.x * c.m[3][2] + in.y * c.m[3][2] + in.z * c.m[3][2] + c.m[3][3]);
		// *out[0] = *out[0] / w;
		// *out[1] = *out[1] / w;
		// *out[2] = *out[2] / w;
	}
}

// matrix mulitplies a triangle. If orthogoinal matrix => ortho=1
// void	mxt(mtx *c, trigon in, trigon *out, int ortho)
// {
	// mxp(c, *in.p0, out->p0, ortho);
	// mxp(c, *in.p1, out->p1, ortho);
	// mxp(c, *in.p2, out->p2, ortho);
// }

//creates an Orthonormal matrix. Values for znear are set to 0.1
mtx	*othromtx(double width, double length, double zfar, double viewangle)
{
	mtx	*orthomtx;

	orthomtx = NULL;
	orthomtx = new_mtx();
	if (orthomtx == NULL)
		return (NULL);
	orthomtx->m[0][0] = (width/length) * 1/(tan(viewangle / 2));
	orthomtx->m[1][1] = 1 / (tan(viewangle / 2));
	orthomtx->m[2][2] = zfar / (zfar - 0.1);
	orthomtx->m[2][3] = -(zfar / (zfar - 0.1) * 0.1);
	orthomtx->m[3][2] = 1;
	return (orthomtx);
}

//creates a rotation matrix with the corresponding angles
mtx *create_rotmtx(double y, double ß, double a)
{
	mtx  *rotmtx;

	rotmtx = NULL;
	rotmtx = new_mtx();
	if (rotmtx == NULL)
		return (NULL);
	rotmtx->m[0][0] = (cos(a) * cos(ß));
	rotmtx->m[0][1] = (cos(a) * sin(ß) * sin(y) - sin(a) * cos(y));
	rotmtx->m[0][2] = (cos(a) * sin(ß) * cos(y) + sin(a) * sin(y));
	rotmtx->m[1][0] = (sin(a) * cos(ß));
	rotmtx->m[1][1] = (sin(a) * sin(ß) * sin(y) + cos(a) * cos(y));
	rotmtx->m[1][2] = (sin(a) * sin(ß) * cos(y) - cos(a) * sin(y));
	rotmtx->m[2][0] = (-sin(ß));
	rotmtx->m[2][1] = (cos(ß) * sin(y));
	rotmtx->m[2][2] = (cos(ß) * cos(y));
	return (rotmtx);
}

void	rottrigon(trigon in, trigon *out, mtx rotmtx)
{
	mxp(rotmtx, *(in.p0), out->p0, 0);
	mxp(rotmtx, *(in.p1), out->p1, 0);
	mxp(rotmtx, *(in.p2), out->p2, 0);
}

// transformas all objects in an image to the current angle
// ### PUT TRANSFORMED TRIGONS TO THE DISP-LINST IN IMAGE ###
void	trans_op(image *im)
{
	mtx		*rotmtx;
	trigon	*temp;
	trigon	out;

	rotmtx = create_rotmtx(im->angle[0], im->angle[1], im->angle[2]);
	temp = im->stat;
	while (temp)
	{
		rottrigon(*temp, &out, *rotmtx);
		addtrigon(&im->disp, out.p0, out.p1, out.p2);
		temp = temp->next;
	}
	free (rotmtx);
}


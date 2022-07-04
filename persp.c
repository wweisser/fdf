/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   persp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 09:32:35 by wweisser          #+#    #+#             */
/*   Updated: 2022/07/04 19:46:56 by wweisser         ###   ########.fr       */
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

//creates an Orthonormal matrix. Values for znear are set to 0.1
mtx	*create_othromtx(window *win)
{
	mtx		*orthomtx;
	double	zfar;
	double	znear;

	zfar = 1000;
	znear = 0.1;
	orthomtx = NULL;
	orthomtx = new_mtx();
	if (orthomtx == NULL)
		return (NULL);
	orthomtx->m[0][0] = 1/(tan((win->open_angle * (M_PI / 360)) / 2)) * (win->x / win->y);
	orthomtx->m[1][1] = 1/(tan((win->open_angle * (M_PI / 360)) / 2));
	orthomtx->m[2][2] = zfar / (zfar - znear);
	orthomtx->m[2][3] = -(zfar / (zfar - znear) * znear);
	orthomtx->m[3][2] = 1;
	printf(" 0/0: %f | 1/1: %f | 2/2: %f | 3/2: %f  \n", orthomtx->m[0][0], orthomtx->m[1][1], orthomtx->m[2][2], orthomtx->m[3][2]);
	return (orthomtx);
}

//creates a rotation matrix with the corresponding angles
mtx *create_rotmtx(double y, double ß, double a)
{
	mtx	*rotmtx;

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

// Calculates the multiplcation of a tripple vector with a 3x3 matrix
// If it is an Orthogonal matrix => ortho=1, which means a 4x4 matrix, w is
// the fourth value which divides the other tree results
//(see ORthogonal matrix)
void	mxp(mtx c, point in, point *out, int ortho)
{
	float	w;

	w = 1;
	out->x = in.x * c.m[0][0] + in.y * c.m[0][1] + in.z * c.m[0][2] + c.m[0][3];
	out->y = in.x * c.m[1][0] + in.y * c.m[1][1] + in.z * c.m[1][2] + c.m[1][3];
	out->z = in.x * c.m[2][0] + in.y * c.m[2][1] + in.z * c.m[2][2] + c.m[2][3];
	if (ortho == 1 && w != 0)
	{
		// w = (in.x * c.m[3][2] + in.y * c.m[3][2] + in.z * c.m[3][2] + c.m[3][3]);
		out->x = out->x / in.z;
		out->y = out->y / in.z;
		// out->z = out->z / in->z;
	}
}

// matrix mulitplies a triangle. If orthogoinal matrix => ortho=1
void	mxt(mtx c, trigon in, trigon *out, int ortho)
{
	mxp(c, *in.p0, out->p0, ortho);
	mxp(c, *in.p1, out->p1, ortho);
	mxp(c, *in.p2, out->p2, ortho);
	if (ortho == 0)
	{
		mxp(c, *in.n, out->n, 0);
		norm_vector(out->n);
	}

}


// rotates all vertices of a trigon together with its normal direction vector
// also norms the rotated direction vector
void	rottrigon(trigon in, trigon *out, mtx rotmtx)
{
	mxp(rotmtx, *in.p0, out->p0, 0);
	mxp(rotmtx, *in.p1, out->p1, 0);
	mxp(rotmtx, *in.p2, out->p2, 0);
	// printf("vor trafo %f %f %f\n", in->n->x, in->n->y, in->n->z);
	mxp(rotmtx, *in.n, out->n, 0);
	// printf("vor norm %f %f %f\n", out->n->x, out->n->y, out->n->z);
	norm_vector(out->n);
}

// transformas all objects in an image to the current angle
// void	trans_op(image *im)
void	trans_op(trigon *stat, trigon **disp, double angle[3], image *im)
{
	mtx		*rotmtx;
	mtx		*orthomtx;
	trigon	*temp;
	trigon	*out1;
	trigon	*out2;
	point	*p[3];
	rotmtx = create_rotmtx(angle[0], angle[1], angle[2]);
	orthomtx = create_othromtx(im->win);
	temp = NULL;
	out1 = NULL;
	out2 = NULL;
	p[0] = new_point(0, 0, 0);
	p[1] = new_point(0, 0, 0);
	p[2] = new_point(0, 0, 0);
	temp = stat;
	while (temp)
	{
		out1 = new_trigon(p[0], p[1], p[2]);
		out2 = new_trigon(p[0], p[1], p[2]);

		mxt(*rotmtx, *temp, out2, 0);
		printf("vor trafo %f %f %f\n", temp->p1->x, temp->p1->y, temp->p1->z);

		// mxt(*orthomtx, *out1, out2, 1);
		printf("nach trafo %f %f %f\n\n", out2->p1->x, out2->p1->y, out2->p1->z);

		addtrigon(disp, out2);
		temp = temp->next;
	}
	free_lst (&out1);
	free (rotmtx);
	free (orthomtx);
}

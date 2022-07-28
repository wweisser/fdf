/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   persp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 09:32:35 by wweisser          #+#    #+#             */
/*   Updated: 2022/07/28 16:33:15 by wweisser         ###   ########.fr       */
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

//creates a rotation matrix with the corresponding angles
mtx *create_rotmtx(float y, float ß, float a)
{
	mtx	*rotmtx;

	a = a * (M_PI/360);
	y = y * (M_PI/360);
	ß = ß * (M_PI/360);
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
void	mxp(mtx c, point in, point *out)
{
	float	w;
// ergebnisse der orthomatrix uberprufen, egbnisse auf den falschen slots
	w = 1;
	out->x = (in.x * c.m[0][0] + in.y * c.m[0][1] + in.z * c.m[0][2] + c.m[0][3]);
	out->y = (in.x * c.m[1][0] + in.y * c.m[1][1] + in.z * c.m[1][2] + c.m[1][3]);
	out->z = (in.x * c.m[2][0] + in.y * c.m[2][1] + in.z * c.m[2][2] + c.m[2][3]);
}

// rotates all vertices of a trigon together with its normal direction vector
// also norms the rotated direction vector
void	rottrigon(trigon in, trigon *out, mtx rotmtx)
{
	mxp(rotmtx, in.p0, &out->p0);
	mxp(rotmtx, in.p1, &out->p1);
	mxp(rotmtx, in.p2, &out->p2);
	mxp(rotmtx, in.n, &out->n);
	norm_vector(&out->n);
}

void	adjst_top(trigon *temp, float top_hight)
{
			temp->p0.y = temp->p0.y * top_hight;
			temp->p1.y = temp->p1.y * top_hight;
			temp->p2.y = temp->p2.y * top_hight;
}

// matrix mulitplies a triangle. If orthogoinal matrix => ortho=1
void	mxt(mtx c, trigon in, trigon *out, float top_hight)
{
	adjst_top(&in, top_hight);
	mxp(c, in.p0, &out->p0);
	mxp(c, in.p1, &out->p1);
	mxp(c, in.p2, &out->p2);
	out->p0.color = in.p0.color;
	out->p1.color = in.p1.color;
	out->p2.color = in.p2.color;
}

void	translate(trigon *tri, int offsetx, int offsety)
{
	tri->p0.x += tri->p0.x + offsetx;
	tri->p1.x += tri->p1.x + offsetx;
	tri->p2.x += tri->p2.x + offsetx;
	tri->p0.y += tri->p0.y + offsety;
	tri->p1.y += tri->p1.y + offsety;
	tri->p2.y += tri->p2.y + offsety;
}

void	scale(trigon *tri, int fact)
{
	tri->p0.x = (int )(tri->p0.x * fact);
	tri->p0.y = (int )(tri->p0.y * fact);
	tri->p1.x = (int )(tri->p1.x * fact);
	tri->p1.y = (int )(tri->p1.y * fact);
	tri->p2.x = (int )(tri->p2.x * fact);
	tri->p2.y = (int )(tri->p2.y * fact);
}

void	set_default(image *im)
{
	float	vert_hight;
	float	vert_low;
	float	temp1;
	trigon *temp;

	vert_hight = 0;
	vert_low = 0;
	temp = im->stat;
	while (temp)
	{
		if (temp->p2.y > vert_hight)
			vert_hight = temp->p2.y;
		if (temp->p2.y < vert_low)
			vert_hight = temp->p2.y;
		temp = temp->next;
	}
	temp1 = (im->lines + im->column) / 2;
	im->top_hight = temp1 / (temp1 + (vert_hight + vert_low));
	im->win->size = (im->x) / temp1;
	im->angle[0] = 490;
	im->angle[1] = 15;
	im->angle[2] = 45;
	im->offsetx = 0;
	im->offsety = 0;
}

// transformas all objects in an image to the current angle
void	trans_op(image *im)
{
	mtx		*rotmtx;
	trigon	*temps;
	trigon	tempd;


	rotmtx = create_rotmtx(im->angle[0], im->angle[1], im->angle[2]);
	temps = im->stat;
	while (temps)
	{
		mxt(*rotmtx, *temps, &tempd, im->top_hight);
		scale(&tempd, im->win->size);
		translate(&tempd, im->offsetx, im->offsety);
		if (tempd.p1.x < 500 && tempd.p1.x > -500 && tempd.p1.y < 500 && tempd.p1.y > -500)
		{
			line(tempd.p1, tempd.p2, im);
			line(tempd.p2, tempd.p0, im);
		}
		temps = temps->next;
	}
	free (rotmtx);
}

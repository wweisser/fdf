/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_calc_trigon.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 13:56:43 by wendelin          #+#    #+#             */
/*   Updated: 2022/08/06 13:58:08 by wendelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

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
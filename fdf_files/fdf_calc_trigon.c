/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_calc_trigon.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 13:56:43 by wendelin          #+#    #+#             */
/*   Updated: 2022/08/12 00:24:56 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// matrix mulitplies a triangle. If orthogoinal matrix => ortho=1
void	mxt(t_mtx c, t_trigon in, t_trigon *out, double top_hight)
{
	in.p0.y = in.p0.y * top_hight;
	in.p1.y = in.p1.y * top_hight;
	in.p2.y = in.p2.y * top_hight;
	mxp(c, &in.p0, &out->p0);
	mxp(c, &in.p1, &out->p1);
	mxp(c, &in.p2, &out->p2);
	out->p0.color = in.p0.color;
	out->p1.color = in.p1.color;
	out->p2.color = in.p2.color;
}

void	translate(t_trigon *tri, int offsetx, int offsety)
{
	tri->p0.x += tri->p0.x + offsetx;
	tri->p1.x += tri->p1.x + offsetx;
	tri->p2.x += tri->p2.x + offsetx;
	tri->p0.y += tri->p0.y + offsety;
	tri->p1.y += tri->p1.y + offsety;
	tri->p2.y += tri->p2.y + offsety;
}

void	scale(t_trigon *tri, int fact)
{
	tri->p0.x = (int )(tri->p0.x * fact);
	tri->p0.y = (int )(tri->p0.y * fact);
	tri->p1.x = (int )(tri->p1.x * fact);
	tri->p1.y = (int )(tri->p1.y * fact);
	tri->p2.x = (int )(tri->p2.x * fact);
	tri->p2.y = (int )(tri->p2.y * fact);
}

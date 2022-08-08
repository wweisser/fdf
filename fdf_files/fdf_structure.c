/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_structure.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:23:40 by wendelin          #+#    #+#             */
/*   Updated: 2022/08/08 20:25:36 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// a new point with xyz is allocated and returned
t_point	new_point(float x, float y, float z, int color)
{
	t_point	p;

	p.x = x;
	p.y = y;
	p.z = z;
	if ((y - (int )y) != 0)
		p.color = (y - (int )y) * 1000000;
	else
		p.color = color;
	return (p);
}

// takes a tree vertizes creates and returns a pointer to an new trigon
// calculates the dirtction vector d1 and d2 and the normale n by d2xd1
t_trigon	*new_trigon(t_point p0, t_point p1, t_point p2)
{
	t_trigon	*tri;

	tri = NULL;
	tri = malloc(sizeof(t_trigon));
	if (tri == NULL)
		return (NULL);
	tri->p0 = new_point(p0.x, p0.y, p0.z, p0.color);
	tri->p1 = new_point(p1.x, p1.y, p1.z, p1.color);
	tri->p2 = new_point(p2.x, p2.y, p2.z, p2.color);
	tri->next = NULL;
	return (tri);
}

void	build_square(double **tp, int i[4], t_image *im)
{
	t_point		np[3];
	t_trigon	*nt;
	int			c;

	c = setc(0, 255, tp[i[2]][i[1] - 1] * (float )(255 / im->top_hight), 100);
	np[0] = new_point(i[1] - 1 - (im->column / 2),
			tp[i[2]][i[1] - 1], i[2] - (im->lines / 2), c);
	c = setc(0, 255, tp[i[2] - 1][i[1]] * (float )(255 / im->top_hight), 100);
	np[1] = new_point(i[1] - (im->column / 2),
			tp[i[2] - 1][i[1]], i[2] - 1 - (im->lines / 2), c);
	c = setc(0, 255, tp[i[2]][i[1]] * (float )(255 / im->top_hight), 100);
	np[2] = new_point(i[1] - (im->column / 2),
			tp[i[2]][i[1]], i[2] - (im->lines / 2), c);
	nt = new_trigon(np[0], np[1], np[2]);
	addtrigon(&im->stat, nt);
	c = setc(0, 255, tp[i[2] - 1][i[1] - 1]
			* (float )(255 / im->top_hight), 100);
	np[2] = new_point(i[1] - 1 - (im->column / 2),
			tp[i[2] - 1][i[1] - 1], i[2] - 1 - (im->lines / 2), c);
	nt = new_trigon(np[0], np[1], np[2]);
	addtrigon(&im->stat, nt);
}

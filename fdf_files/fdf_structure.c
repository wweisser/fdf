/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_structure.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:23:40 by wendelin          #+#    #+#             */
/*   Updated: 2022/08/12 00:33:35 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// a new point with xyz is allocated and returned
t_point	value_to_point(float x, float y, float z, int color)
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

t_point	new_point(t_point p_in, t_point *p)
{
	p->x = p_in.x;
	p->y = p_in.y;
	p->z = p_in.z;
	if ((p_in.y - (int )p_in.y) != 0)
		p->color = (p_in.y - (int )p_in.y) * 1000000;
	else
		p->color = p_in.color;
	return (*p);
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
	tri->p0 = new_point(p0, &(tri->p0));
	tri->p1 = new_point(p1, &(tri->p1));
	tri->p2 = new_point(p2, &(tri->p2));
	tri->next = NULL;
	return (tri);
}

void	build_square(double **tp, int x, int y, t_image *im)
{
	t_point		np[3];
	t_trigon	*nt;
	int			c;

	c = setc(0, 255, tp[y][x - 1] * (double )(255 / im->top_hight), 100);
	np[0] = value_to_point(x - 1 + im->offsetx,
			tp[y][x - 1] * im->top_hight, y + im->offsety, c);
	c = setc(0, 255, tp[y - 1][x] * (double )(255 / im->top_hight), 100);
	np[1] = value_to_point(x + im->offsetx,
			tp[y - 1][x] * im->top_hight, y - 1 + im->offsety, c);
	c = setc(0, 255, tp[y][x] * (double )(255 / im->top_hight), 100);
	np[2] = value_to_point(x + im->offsetx,
			tp[y][x] * im->top_hight, y + im->offsety, c);
	nt = new_trigon(np[0], np[1], np[2]);
	addtrigon(&im->stat, nt);
	c = setc(0, 255, tp[y - 1][x - 1] * (double )(255 / im->top_hight), 100);
	np[2] = value_to_point(x - 1 + im->offsetx,
			tp[y - 1][x - 1] * im->top_hight, y - 1 + im->offsety, c);
	nt = new_trigon(np[0], np[1], np[2]);
	addtrigon(&im->stat, nt);
}

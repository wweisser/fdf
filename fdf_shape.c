/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:23:40 by wendelin          #+#    #+#             */
/*   Updated: 2022/07/20 14:37:05 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "fdf.h"

// a new point with xyz is allocated and returned
point	new_point(float x, float y, float z, int color)
{
	// point	*p;
	point	p;

	// p = NULL;
	// p = malloc(sizeof(point));
	// if (p == NULL)
	// 	return (NULL);
	p.x = x;
	p.y = y;
	p.z = z;
	p.color = color;
	return (p);
}

// takes a tree vertizes creates and returns a pointer to an new trigon
// calculates the dirtction vector d1 and d2 and the normale n by d2xd1
trigon	*new_trigon(point p0, point p1, point p2)
{
	trigon	*tri;
	// point	d1;
	// point	d2;

	// if (p0 == NULL || p1 == NULL || p2 == NULL)
	// 	return (NULL);
	tri = NULL;
	tri = malloc(sizeof(trigon));
	if (tri == NULL)
		return (NULL);
	tri->p0 = new_point(p0.x, p0.y, p0.z, p0.color);
	tri->p1 = new_point(p1.x, p1.y, p1.z, p1.color);
	tri->p2 = new_point(p2.x, p2.y, p2.z, p2.color);
	tri->n = new_point(0, 0, 0, 0);
	// calc_point(p1, p0, &d1, -1);
	// calc_point(p2, p0, &d2, -1);
	// cross_product(&d1, &d2, &tri->n);
	// norm_vector(tri->n);
	tri->next = NULL;
	return (tri);
}

// trigon	*new_trigon(point p0, point p1, point p2)
// {
// 	trigon	tri;
// 	point	d1;
// 	point	d2;

// 	// if (p0 == NULL || p1 == NULL || p2 == NULL)
// 	// 	return (NULL);
// 	// tri = NULL;
// 	// tri = malloc(sizeof(trigon));
// 	// if (tri == NULL)
// 	// 	return (NULL);
// 	tri.p0 = new_point(p0.x, p0.y, p0.z, p0.color);
// 	tri.p1 = new_point(p1.x, p1.y, p1.z, p1.color);
// 	tri.p2 = new_point(p2.x, p2.y, p2.z, p2.color);
// 	tri.n = new_point(0, 0, 0, 0);
// 	calc_point(p1, p0, &d1, -1);
// 	calc_point(p2, p0, &d2, -1);
// 	cross_product(&d1, &d2, tri.n);
// 	// norm_vector(tri->n);
// 	tri->next = NULL;
// 	return (tri);
// }

// appends a node containing a trigon at the end of a list of trigons
// ADDTRIGON UND NEW TRIGON MÜSSEN GETRENNT WERDEN
void	addtrigon(trigon **head, trigon *new)
{
	// trigon	**temp;

	if (new == NULL)
		return ;
	if (*head == NULL)
	{
		new->next = NULL;
		*head = new;
	}
	else
	{
		new->next = *head;
		*head = new;
		// temp = head;
		// while (*temp)
		// {
		// 	temp = &(*temp)->next;
		// }
		// new->next = *temp;
		// *temp = new;
	}
}

// draws a list of trigons.
void	draw_trigons(trigon *tri_lst, image *im)
{
	// double	normfact;
	point	nvector;
	int		color = setcolor(0, 255, 10, 10);

	// normfact = 0;
	nvector = new_point(0, 0, 0, 0);
	if (tri_lst != NULL)
	{
		// line(*(temp->p0), *(temp->p1), color, im);
		line(tri_lst->p1, tri_lst->p2, color, im);
		line(tri_lst->p2, tri_lst->p0, color, im);
		// fact_vector(temp->n, 100);
		// calc_point(*(temp->p0), *(temp->n), nvector, 1);
		// set_line(*(temp->p0), *nvector, im);
			// }
			// temp = temp->next;
	}
}

void	a_p(point *p, float x, float y, float z)
{
	p->x = x;
	p->y = y;
	p->z = z;
}

void	build_square(int **tp, int i , int j, image *im)
{
	point	np[3];
	trigon	*nt;

	a_p(&np[0], i - 1 - (im->column / 2), tp[j][i - 1], j - (im->lines / 2));
	a_p(&np[1], i - (im->column / 2), tp[j - 1][i], j - 1 - (im->lines / 2));
	a_p(&np[2], i - (im->column / 2), tp[j][i], j - (im->lines / 2));
	nt = new_trigon(np[0], np[1], np[2]);
	addtrigon(&im->stat, nt);
	a_p(&np[2], i - 1 - (im->column / 2), tp[j - 1][i - 1], j - 1 - (im->lines / 2));
	nt = new_trigon(np[0], np[1], np[2]);
	addtrigon(&im->stat, nt);
}

void	built_grid(int **tp, int ln, int cl, image *im)
{
	int	i;
	int	j;
	point	np[3];
	trigon	*nt;
	j = 1;
	while (tp[j] != NULL)
	{
		i = 1;
		while (tp[j][i] != 2147483647)
		{
			if ((tp[j - 1][i]) == 2147483647)
				break ;
			a_p(&np[0], i - 1 - (cl / 2), tp[j][i - 1], j - (ln / 2));
			a_p(&np[1], i - (cl / 2), tp[j - 1][i], j - 1 - (ln / 2));
			a_p(&np[2], i - (cl / 2), tp[j][i], j - (ln / 2));
			nt = new_trigon(np[0], np[1], np[2]);
			addtrigon(&im->stat, nt);
			a_p(&np[2], i - 1 - (cl / 2), tp[j - 1][i - 1], j - 1 - (ln / 2));
			nt = new_trigon(np[0], np[1], np[2]);
			addtrigon(&im->stat, nt);
			i++;
		}
		j++;
	}
}

void	free_lst(trigon **head)
{
	trigon *temp;

	temp = *head;
	if (*head != NULL)
	{
		while(*head)
		{
			temp = *head;
			*head = (*head)->next;
			free(temp);
		}
		head = NULL;
	}
}

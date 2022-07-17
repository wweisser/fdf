/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:23:40 by wendelin          #+#    #+#             */
/*   Updated: 2022/07/17 22:00:14 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "fdf.h"

// a new point with xyz is allocated and returned
point	*new_point(double x, double y, double z, int color)
{
	point	*p;

	p = NULL;
	p = malloc(sizeof(point));
	if (p == NULL)
		return (NULL);
	p->x = x;
	p->y = y;
	p->z = z;
	p->color = color;
	return (p);
}

// takes a tree vertizes creates and returns a pointer to an new trigon
// calculates the dirtction vector d1 and d2 and the normale n by d2xd1
trigon	*new_trigon(point p0, point p1, point p2)
{
	trigon	*tri;
	point	d1;
	point	d2;

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
	calc_point(p1, p0, &d1, -1);
	calc_point(p2, p0, &d2, -1);
	cross_product(&d1, &d2, tri->n);
	// norm_vector(tri->n);
	tri->next = NULL;
	return (tri);
}

// appends a node containing a trigon at the end of a list of trigons
// ADDTRIGON UND NEW TRIGON MÜSSEN GETRENNT WERDEN
void	addtrigon(trigon **head, trigon *new)
{
	trigon	**temp;

	if (new == NULL)
		return ;
	if (*head == NULL)
		*head = new;
	else
	{
		temp = head;
		while (*temp)
		{
			temp = &(*temp)->next;
		}
		new->next = *temp;
		*temp = new;
	}
}

// draws a list of trigons.
void	draw_trigons(trigon *tri_lst, image *im)
{
	// double	normfact;
	point	*nvector;
	trigon	*temp;
	int		color = setcolor(0, 255, 10, 10);

	// normfact = 0;
	nvector = new_point(0, 0, 0, 0);
	if (tri_lst != NULL)
	{
		temp = tri_lst;
		while (temp != NULL)
		{
			// if (scalar_product(temp->n, im->win->view) > 0)
			{
				// line(*(temp->p0), *(temp->p1), color, im);
				line(*(temp->p1), *(temp->p2), color, im);
				line(*(temp->p2), *(temp->p0), color, im);
				// fact_vector(temp->n, 100);
				// calc_point(*(temp->p0), *(temp->n), nvector, 1);
				// set_line(*(temp->p0), *nvector, im);
			}
			temp = temp->next;
		}
	free (nvector);
	}
}

void	a_p(point *p, double x, double y, double z)
{
	p->x = x;
	p->y = y;
	p->z = z;
}

void	built_grid(int **tp, image *im, int ln, int rw)
{
	int	i;
	int	j;
	point	np[3];
	trigon	*nt;

	j = 1;
	while (j <= ln)
	{
		i = 1;
		while (tp[j][i] != 2147483647)
		{
			a_p(&np[0], i - 1 - (rw / 2), tp[j][i - 1], j - (ln / 2));
			a_p(&np[1], i - (rw / 2), tp[j - 1][i], j - 1 - (ln / 2));
			a_p(&np[2], i - (rw / 2), tp[j][i], j - (ln / 2));
			nt = new_trigon(np[0], np[1], np[2]);
			addtrigon(&im->stat, nt);
			a_p(&np[2], i - 1 - (rw / 2), tp[j - 1][i - 1], j - 1 - (ln / 2));
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
			free(temp->n);
			free(temp->p0);
			free(temp->p1);
			free(temp->p2);
			*head = (*head)->next;
			free(temp);
		}
		head = NULL;
	}
}

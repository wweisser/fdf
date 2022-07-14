/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:23:40 by wendelin          #+#    #+#             */
/*   Updated: 2022/07/14 18:04:53 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "fdf.h"

// a new point with xyz is allocated and returned
point	*new_point(double x, double y, double z)
{
	point	*p;

	p = NULL;
	p = malloc(sizeof(point));
	if (p == NULL)
		return (NULL);
	p->x = x;
	p->y = y;
	p->z = z;
	return (p);
}

// takes a tree vertizes creates and returns a pointer to an new trigon
// calculates the dirtction vector d1 and d2 and the normale n by d2xd1
trigon	*new_trigon(point *p0, point *p1, point *p2)
{
	trigon	*tri;
	point	d1;
	point	d2;

	if (p0 == NULL || p1 == NULL || p2 == NULL)
		return (NULL);
	tri = NULL;
	tri = malloc(sizeof(trigon));
	if (tri == NULL)
		return (NULL);
	tri->p0 = new_point(p0->x, p0->y, p0->z);
	tri->p1 = new_point(p1->x, p1->y, p1->z);
	tri->p2 = new_point(p2->x, p2->y, p2->z);
	tri->n = new_point(0, 0, 0);
	calc_point(*p1, *p0, &d1, -1);
	calc_point(*p2, *p0, &d2, -1);
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
// HIER WEITERMACHEN NORMALEN VEKTOREN DATSTELLEN
// draws a list of trigons.
void	draw_trigons(trigon *tri_lst, image *im)
{
	// double	normfact;
	point	*nvector;
	trigon	*temp;
	int		color = setcolor(0, 255, 255, 255);

	// normfact = 0;
	nvector = new_point(0, 0, 0);
	if (tri_lst != NULL)
	{
		temp = tri_lst;
		while (temp != NULL)
		{
			// if (scalar_product(temp->n, im->win->view) > 0)
			{
				// set_line(*(temp->p0), *(temp->p1), im);
				// set_line(*(temp->p1), *(temp->p2), im);
				// set_line(*(temp->p1), *(temp->p0), im);

				line(*(temp->p0), *(temp->p1), color, im);
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

void	built_grid(int **top_map, image *im, int lines, int rows)
{
	int	i;
	int	j;
	point	*np[3];
	trigon	*nt;

	j = 1;
	while (j < lines)
	{
		i = 1;
		while (top_map[j][i] != 2147483647)
		{
			np[0] = new_point(i - 1 - (rows / 2), top_map[j][i - 1], j - (lines / 2));
			np[1] = new_point(i - (rows / 2), top_map[j - 1][i], j - 1 - (lines / 2));
			np[2] = new_point(i - (rows / 2), top_map[j][i], j - (lines / 2));
			nt = new_trigon(np[0], np[1], np[2]);
			addtrigon(&im->stat, nt);
			np[0] = new_point(i - 1 - (rows / 2), top_map[j][i - 1], j - (lines / 2));
			np[1] = new_point(i - (rows / 2), top_map[j - 1][i], j - 1 - (lines / 2));
			np[2] = new_point(i - 1 - (rows / 2), top_map[j - 1][i - 1], j - 1 - (lines / 2));
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

// creates a square consting of four trigons. The center => cent,
// side length => s_len, algn=0 x-plane, algn=1 y-plane, algn=2 z-plane
// void	new_sqare(double ctr[3], int l, image *im)
// {
// 	point	*p[3];
// 	trigon	*node;

// 	p[0] = new_point(ctr[0], ctr[1], ctr[2]);
// 	p[1] = new_point(ctr[0] - (l / 2), ctr[1] - (l / 2), ctr[2]);
// 	p[2] = new_point(ctr[0] + (l / 2), ctr[1] - (l / 2), ctr[2]);
// 	node = new_trigon(p[0], p[1], p[2]);
// 	printf("%p\n", node);
// 	addtrigon(&im->stat, node);
// 	p[1] = new_point(ctr[0] + (l / 2), ctr[1] - (l / 2), ctr[2]);
// 	p[2] = new_point(ctr[0] + (l / 2), ctr[1] + (l / 2), ctr[2]);
// 	node = new_trigon(p[0], p[1], p[2]);
// 	printf("%p\n", node);
// 	addtrigon(&im->stat, node);
// 	p[1] = new_point(ctr[0] + (l / 2), ctr[1] + (l / 2), ctr[2]);
// 	p[2] = new_point(ctr[0] - (l / 2), ctr[1] + (l / 2), ctr[2]);
// 	node = new_trigon(p[0], p[1], p[2]);
// 	printf("%p\n", node);
// 	addtrigon(&im->stat, node);
// 	p[1] = new_point(ctr[0] - (l / 2), ctr[1] + (l / 2), ctr[2]);
// 	p[2] = new_point(ctr[0] - (l / 2), ctr[1] - (l / 2), ctr[2]);
// 	node = new_trigon(p[0], p[1], p[2]);
// 	printf("%p\n", node);
// 	addtrigon(&im->stat, node);
// }
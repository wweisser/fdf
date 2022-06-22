/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:23:40 by wendelin          #+#    #+#             */
/*   Updated: 2022/06/22 16:28:43 by wweisser         ###   ########.fr       */
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
	cross_product(d1, d2, tri->n);
	tri->next = NULL;
	return (tri);
}

// appends a node containing a trigon at the end of a list of trigons
trigon	*addtrigon(trigon **head, point *p0, point *p1, point *p2)
{
	trigon	**temp;
	trigon	*node;

	node = NULL;
	printf(" -1- \n");
	node = new_trigon(p0, p1, p2);
	if (node == NULL)
		return (NULL);
	printf(" -2- \n");
	if (*head == NULL)
	{
		*head = node;
		printf(" -3- \n");
	}
	else
	{
		temp = head;
		while (*temp)
		{
			temp = &(*temp)->next;
			printf(" -4- \n");
		}
		node->next = *temp;
		*temp = node;
	}
	return (node);
}

// draws a list of trigons.
void	draw_trigons(trigon *tri_lst, image *im)
{
	// double	normfact;
	// point	*nvector;
	trigon	*temp;

	// nvector = NULL;
	if (tri_lst != NULL)
	{
		printf("test\n");
		temp = tri_lst;
		while (temp != NULL)
		{
			set_line(*(temp->p0), *(temp->p1), im);
			set_line(*(temp->p1), *(temp->p2), im);
			set_line(*(temp->p2), *(temp->p0), im);
			printf("Node to print %f %f %f", temp->p1->x, temp->p1->y, temp->p1->z);
			temp = temp->next;
		}
	}
	// calc_point(*(tri->n), *(tri->p0), nvector, 1);
	// normfact = sum_vektor(*nvector);
	// fact_vector(*nvector, (1 / normfact) * 10);
	// set_line(*(tri->p0), *nvector, im);
}

// creates a square consting of four trigons. The center => cent,
// side length => s_len, algn=0 x-plane, algn=1 y-plane, algn=2 z-plane
void	new_sqare(double ctr[3], int l, trigon **head)
{
	point	*p[3];

	p[0] = new_point(ctr[0], ctr[1], ctr[2]);
	p[1] = new_point(ctr[0] - (l / 2), ctr[1] - (l / 2), ctr[2]);
	p[2] = new_point(ctr[0] + (l / 2), ctr[1] - (l / 2), ctr[2]);
	addtrigon(head, p[0], p[1], p[2]);
	p[1] = new_point(ctr[0] + (l / 2), ctr[1] - (l / 2), ctr[2]);
	p[2] = new_point(ctr[0] + (l / 2), ctr[1] + (l / 2), ctr[2]);
	addtrigon(head, p[0], p[1], p[2]);
	p[1] = new_point(ctr[0] + (l / 2), ctr[1] + (l / 2), ctr[2]);
	p[2] = new_point(ctr[0] - (l / 2), ctr[1] + (l / 2), ctr[2]);
	addtrigon(head, p[0], p[1], p[2]);
	p[1] = new_point(ctr[0] - (l / 2), ctr[1] + (l / 2), ctr[2]);
	p[2] = new_point(ctr[0] - (l / 2), ctr[1] - (l / 2), ctr[2]);
	addtrigon(head, p[0], p[1], p[2]);
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
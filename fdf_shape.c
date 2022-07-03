/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:23:40 by wendelin          #+#    #+#             */
/*   Updated: 2022/06/25 16:59:14 by wendelin         ###   ########.fr       */
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
	double	fact;

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
	fact = sum_vektor(*(tri->n));
	if (fact != 0)
		fact = 1 / fact;
	fact_vector(tri->n, fact);
	printf("Node to print %f %f %f\n", tri->n->x, tri->n->y, tri->n->z);
	tri->next = NULL;
	return (tri);
}

// appends a node containing a trigon at the end of a list of trigons
// ADDTRIGON UND NEW TRIGON MÜSSEN GETRENNT WERDEN
void	addtrigon(trigon **head, trigon *new)
{
	trigon	**temp;


	// printf(" -1- \n");
	if (new == NULL)
		return ;
	// printf(" -2- \n");
	if (*head == NULL)
	{
		*head = new;
		// printf(" -3- \n");
	}
	else
	{
		temp = head;
		// while (*temp)
		// {
			temp = &(*temp)->next;
			// printf(" -4- %p\n", *temp);
		// }
		new->next = *temp;
		*temp = new;
		// printf(" -5- \n");
		
	}
}
// HIER WEITERMACHEN NORMALEN VEKTOREN DATSTELLEN
// draws a list of trigons.
void	draw_trigons(trigon *tri_lst, image *im)
{
	// double	normfact;
	point	*nvector;
	trigon	*temp;

	// normfact = 0;
	nvector = new_point(0, 0, 0);
	if (tri_lst != NULL)
	{
		printf("test\n");
		temp = tri_lst;
		while (temp != NULL)
		{
			set_line(*(temp->p0), *(temp->p1), im);
			set_line(*(temp->p1), *(temp->p2), im);
			set_line(*(temp->p2), *(temp->p0), im);
			// printf("Node to print %f %f %f\n", temp->n->x, temp->n->y, temp->n->z);
			// calc_point(*(temp->n), *(temp->p0), nvector, 1);
			// printf("normed n %f  %f  %f\n", temp->n->x, temp->n->y, temp->n->z);
			// normfact = 1 / sum_vektor(*(temp->n));
			// printf("sumed normfact 1 %f\n", normfact);
			// printf("unnormed vector %f  %f  %f\n", nvector->x, nvector->y, nvector->z);
			fact_vector(temp->n, 100);
			calc_point(*(temp->p0), *(temp->n), nvector, 1);
			// printf("normed vector 3 %f  %f  %f\n", temp->n->x, temp->n->y, temp->n->z);
			set_line(*(temp->p0), *nvector, im);	
			// printf("normfact 4 %f\n", normfact);		
			temp = temp->next;
		}
	free (nvector);
	}
}

// creates a square consting of four trigons. The center => cent,
// side length => s_len, algn=0 x-plane, algn=1 y-plane, algn=2 z-plane
void	new_sqare(double ctr[3], double angle[3], int l, image *im)
{
	point	*p[3];
	trigon	*node;

	p[0] = new_point(ctr[0], ctr[1], ctr[2]);
	p[1] = new_point(ctr[0] - (l / 2), ctr[1] - (l / 2), ctr[2]);
	p[2] = new_point(ctr[0] + (l / 2), ctr[1] - (l / 2), ctr[2]);
	node = new_trigon(p[0], p[1], p[2]);
	printf("%p\n", node);
	trans_op(node, &im->stat, angle);
	p[1] = new_point(ctr[0] + (l / 2), ctr[1] - (l / 2), ctr[2]);
	p[2] = new_point(ctr[0] + (l / 2), ctr[1] + (l / 2), ctr[2]);
	node = new_trigon(p[0], p[1], p[2]);
	printf("%p\n", node);
	trans_op(node, &im->stat, angle);
	p[1] = new_point(ctr[0] + (l / 2), ctr[1] + (l / 2), ctr[2]);
	p[2] = new_point(ctr[0] - (l / 2), ctr[1] + (l / 2), ctr[2]);
	node = new_trigon(p[0], p[1], p[2]);
	printf("%p\n", node);
	trans_op(node, &im->stat, angle);
	p[1] = new_point(ctr[0] - (l / 2), ctr[1] + (l / 2), ctr[2]);
	p[2] = new_point(ctr[0] - (l / 2), ctr[1] - (l / 2), ctr[2]);
	node = new_trigon(p[0], p[1], p[2]);
	printf("%p\n", node);
	trans_op(node, &im->stat, angle);
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
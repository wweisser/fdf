/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:21:35 by wendelin          #+#    #+#             */
/*   Updated: 2022/06/25 16:52:41 by wendelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

// a new point with xyz is allocated and returned
point	*new_p(double x, double y, double z)
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

// for op=1 adds two trippels, for op=-1 substracts two trippels
void	calc_p(point p1, point p2, point *result, int op)
{
	if (op == 1)
	{
		result->x = p1.x + p2.x;
		result->y = p1.y + p2.y;
		result->z = p1.z + p2.z;
	}
	if (op == -1)
	{
		result->x = p1.x - p2.x;
		result->y = p1.y - p2.y;
		result->z = p1.z - p2.z;
	}
}

// multiplies p1 times f
void	fact_v(point *p1, double f)
{

		p1->x = p1->x * f;
        printf("p1->x %f\n", p1->x);
		p1->y = p1->y * f;
        printf("p1->y %f\n", p1->y);
		p1->z = p1->z * f;
        printf("p1->z %f\n", p1->z);
}

// calculates p1xp2 an puts it to result
void	cross_p(point p1, point p2, point *result)
{
	result->x = round(p1.y * p2.z - p1.z * p2.y);
	result->y = round(p1.z * p2.x - p1.x * p2.z);
	result->z = round(p1.x * p2.y - p1.y * p2.x);
}
// returns the sum of a vector
double	sum_v(point p1)
{
	double  sum;
	sum = sqrt((p1.x * p1.x)+ (p1.y * p1.y) + (p1.z * p1.z));
	return (sum);
}
trigon	*new_t(point *p0, point *p1, point *p2)
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
	tri->p0 = new_p(p0->x, p0->y, p0->z);
	tri->p1 = new_p(p1->x, p1->y, p1->z);
	tri->p2 = new_p(p2->x, p2->y, p2->z);
	tri->n = new_p(0, 0, 0);
	calc_p(*p1, *p0, &d1, -1);
	calc_p(*p2, *p0, &d2, -1);
	cross_p(d1, d2, tri->n);
	
	fact = sum_v(*(tri->n));
	//HIER WEITER MACHEN, N NORMIEREN
	if (fact != 0)
		fact = 1 / fact;
    printf("fact %f\n", fact); 
	fact_v(tri->n, fact);
	printf("Node to print %f %f %f\n", tri->n->x, tri->n->y, tri->n->z);
	tri->next = NULL;
	return (tri);
}


#include "stdio.h"
int main(void)
{
    point *p1;
    point *p2;
    point *p0;
    trigon *test;

    p0 = new_p(0, 0, 0);

    
    p1 = new_p(11, 12, 3);


    p2 = new_p(15, 0, 0);

    
    test = new_t(p0, p1, p2);
    
    printf("n  %f %f %f\n", test->n->x, test->n->y, test->n->z);
    return (0);
}

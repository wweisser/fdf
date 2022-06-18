/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:23:40 by wendelin          #+#    #+#             */
/*   Updated: 2022/06/18 22:54:38 by wendelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "fdf.h"

double	*new_point(double x, double y, double z)
{
	double *point;
	point = malloc(sizeof(double) * 3);
    if (point == NULL)
        return (NULL);
	point[0] = x;
	point[1] = y;
	point[2] = z;
	return (point);
}

// takes a tree vertizes creates and returns a pointer to an new trigon
// calculates the dirtction vector d1 and d2 and the normale n by d2xd1
trigon  *new_trigon(double p0[3], double p1[3], double p2[3])
{
    trigon  *tri;
    double  d1[3];
    double  d2[3];
    
    tri = NULL;
    tri = malloc(sizeof(trigon));
    if (tri == NULL)
        return (NULL);
    tri->p0[0] = p0[0];
    tri->p0[1] = p0[1];
    tri->p0[2] = p0[2];
    tri->p1[0] = p1[0];
    tri->p1[1] = p1[1];
    tri->p1[2] = p1[2];
    tri->p2[0] = p2[0];
    tri->p2[1] = p2[1];
    tri->p2[2] = p2[2];
    calc_point(p1, p0, d1, -1);
    calc_point(p2, p0, d2, -1);
    cross_product(d1, d2, tri->n);
    return (tri);
}



// creates a square consting of four trigons. The center => cent, 
// side length => s_len, algn=0 x-plane, algn=1 y-plane, algn=2 z-plane
trigon	*new_sqare(double ctr[3], int algn, int l)
{
    
    trigon	*sqare;
	double	*p[3];

    sqare = malloc(4 * sizeof(trigon));
    if (sqare = NULL)
   		return (NULL);	
	p[0] = new_point(ctr[0] , ctr[1], ctr[2]);
	p[1] = new_point(ctr[0] - (l / 2), ctr[1] - (l / 2), ctr[2]);
	p[2] = new_point(ctr[0] + (l / 2), ctr[1] - (l / 2), ctr[2]);
	sqare[0] = *new_trigon(p[0], p[1], p[2]);
	p[1] = new_point(ctr[0] + (l / 2), ctr[1] - (l / 2), ctr[2]);
	p[2] = new_point(ctr[0] + (l / 2), ctr[1] + (l / 2), ctr[2]);
	sqare[1] = *new_trigon(p[0], p[2], p[1]);
	p[1] = new_point(ctr[0] + (l / 2), ctr[1] + (l / 2), ctr[2]);
	p[2] = new_point(ctr[0] - (l / 2), ctr[1] + (l / 2), ctr[2]);
	sqare[2] = *new_trigon(p[0], p[2], p[1]);
	p[1] = new_point(ctr[0] - (l / 2), ctr[1] + (l / 2), ctr[2]);
	p[2] = new_point(ctr[0] - (l / 2), ctr[1] - (l / 2), ctr[2]);
	sqare[3] = *new_trigon(p[0], p[2], p[1]);
    return (sqare);
}


// takes an array of trigons and the number of trigons in that array
// assigns them to an object and returns a pointer to the new object
object  *new_object(trigon *tri, int i)
{
    object  *obj;
    
    i = 1;
    obj = malloc(sizeof(object));
    if (obj == NULL)
        return (NULL);
    obj->stat = malloc(i * sizeof(trigon));
    if (obj == NULL)
        return (NULL);
    obj->draw = malloc(i * sizeof(trigon));
    if (obj == NULL)
        return (NULL);
    obj->stat = tri;
    obj->draw = tri;
    return(obj);
}

// draws the lines of a trigon.
void	draw_trigon(image *im, trigon *tri)
{
	// double	normfact;
	// double	nvector[3];
	set_line(tri->p0, tri->p1, im);
	set_line(tri->p1, tri->p2, im);
	set_line(tri->p2, tri->p0, im);
	// calc_point(tri->n, tri->p0, nvector, 1);
	// normfact = sum_vektor(nvector);
	// fact_vector(nvector, (1 / normfact) * 10);
	// set_line(tri->p0, nvector, im);
}

// draws an object
void    draw_object(object *obj, image *im)
{
    draw_trigon(im, &obj->draw[0]);
}


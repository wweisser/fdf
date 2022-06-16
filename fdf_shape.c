/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:23:40 by wendelin          #+#    #+#             */
/*   Updated: 2022/06/16 14:55:19 by wendelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "fdf.h"
#define PI 3.1415926

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



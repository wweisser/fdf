/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:21:35 by wendelin          #+#    #+#             */
/*   Updated: 2022/06/16 10:35:36 by wendelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:19:02 by wendelin          #+#    #+#             */
/*   Updated: 2022/06/15 18:53:59 by wendelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// for op=1 adds two trippels, for op=-1 substracts two trippels
void    calc_point(double p1[3], double p2[3], double result[3], int op)
{
    
    if (op == 1)
    {
        result[0] = p1[0] + p2[0];
        result[1] = p1[1] + p2[1];
        result[2] = p1[2] + p2[2];
    }
    if (op == -1)
    {
        result[0] = p1[0] - p2[0];
        result[1] = p1[1] - p2[1];
        result[2] = p1[2] - p2[2];
    }
}

void    cross_product(double p1[3], double p2[3], double result[3])
{
    result[0] = p1[1] * p2[2] - p1[2] * p2[1];
    result[1] = p1[2] * p2[0] - p1[0] * p2[2];
    result[2] = p1[0] * p2[1] - p1[1] * p2[0];
}

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
    tri->n[0] = d2[1] * d1[2] - d2[2] * d1[1];
    tri->n[1] = d2[2] * d1[0] - d2[0] * d1[2];
    tri->n[2] = d2[0] * d1[1] - d2[1] * d1[0];
    return (tri);
}

#include "stdio.h"
int main(void)
{
    double p1[3];
    double p2[3];
    double p0[3];
    trigon *test;

    p0[0] = 0;
    p1[1] = 0;
    p2[2] = 0;
    
    p1[0] = 2;
    p1[1] = 4;
    p1[2] = 6;

    p2[0] = 2;
    p2[1] = 2;
    p2[2] = 2;
    
    test = new_trigon(p0, p1, p2);
    
    printf("n  %f %f %f", test->n[0], test->n[1], test->n[2]);
    return (0);
}

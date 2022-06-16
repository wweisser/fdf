/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:19:02 by wendelin          #+#    #+#             */
/*   Updated: 2022/06/16 14:33:27 by wendelin         ###   ########.fr       */
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

// calculates p1xp2 an puts it to result
void    cross_product(double p1[3], double p2[3], double result[3])
{
    result[0] = p1[1] * p2[2] - p1[2] * p2[1];
    result[1] = p1[2] * p2[0] - p1[0] * p2[2];
    result[2] = p1[0] * p2[1] - p1[1] * p2[0];
}

// multiplies p1 times f
void    fact_vector(double p1[3], double f)
{
    if (p1[0] != 0.0)
    {
        p1[0] = p1[0] * f;
        p1[1] = p1[1] * f;
        p1[2] = p1[2] * f;        
    }
}

// returns the dotproct of p1 o p2
double    dot_product(double p1[3], double p2[3])
{
    double  dp;

    dp = (p1[0] * p2[0]) + (p1[1] * p2[1]) + (p1[2] * p2[2]);
    return (dp);
}

// returns the sum of a vector
double    sum_vektor(double p1[3])
{
    double  sum;
    sum = sqrt((p1[0] * p1[0])+ (p1[1] * p1[1]) + (p1[2] * p1[2]));
    return (sum);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_calc_vector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 13:48:36 by wendelin          #+#    #+#             */
/*   Updated: 2022/08/06 13:54:57 by wendelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// calculates the sacalarproduct
float	scalar_product(point *d1, point *d2)
{
	double	result;

	result = (d1->x * d2->x) + (d1->y * d2->y) + (d1->z * d2->z);
	return(result);
}

// calculates p1xp2 an puts it to result
void	cross_product(point *p1, point *p2, point *result)
{
	result->x = round(p1->y * p2->z - p1->z * p2->y);
	result->y = round(p1->z * p2->x - p1->x * p2->z);
	result->z = round(p1->x * p2->y - p1->y * p2->x);
}


// returns the dotproct of p1 o p2
float	dot_product(float p1[3], float p2[3])
{
	float  dp;

	dp = (p1[0] * p2[0]) + (p1[1] * p2[1]) + (p1[2] * p2[2]);
	return (dp);
}

float	sum_vector(point p1)
{
	float  sum;
	sum = sqrt((p1.x * p1.x)+ (p1.y * p1.y) + (p1.z * p1.z));
	return (sum);
}


// normates a directionvector
void	norm_vector(point *p1)
{
	float	fact;

	fact = 0.0;
	fact = sum_vector(*p1);
	if (fact != 0.0)
		fact = 1 / fact;
	fact_vector(p1, fact);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:19:02 by wendelin          #+#    #+#             */
/*   Updated: 2022/06/19 19:07:49 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// for op=1 adds two trippels, for op=-1 substracts two trippels
void	calc_point(point p1, point p2, point *result, int op)
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

// calculates p1xp2 an puts it to result
void	cross_product(point p1, point p2, point *result)
{
	result->x = p1.y * p2.z - p1.z * p2.y;
	result->y = p1.z * p2.x - p1.x * p2.z;
	result->z = p1.x * p2.y - p1.y * p2.x;
}

// multiplies p1 times f
void	fact_vector(point p1, double f)
{
	if (p1.x != 0.0)
	{
		p1.x = p1.x * f;
		p1.y = p1.y * f;
		p1.z = p1.z * f;
	}
}

// returns the dotproct of p1 o p2
double	dot_product(double p1[3], double p2[3])
{
	double  dp;

	dp = (p1[0] * p2[0]) + (p1[1] * p2[1]) + (p1[2] * p2[2]);
	return (dp);
}

// returns the sum of a vector
double	sum_vektor(point p1)
{
	double  sum;
	sum = sqrt((p1.x * p1.x)+ (p1.y * p1.y) + (p1.z * p1.z));
	return (sum);
}
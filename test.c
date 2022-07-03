/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:21:35 by wendelin          #+#    #+#             */
/*   Updated: 2022/07/03 20:58:15 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}			point;

point	*new_point(double x, double y, double z)
{
	point	*p;

	p = NULL;
	p = (point *)malloc(sizeof(point));
	if (p == NULL)
		return (NULL);
	p->x = x;
	p->y = y;
	p->z = z;
	return (p);
}

// returns the sum of a vector
double	sum_vector(point p1)
{
	double  sum;
	sum = sqrt((p1.x * p1.x)+ (p1.y * p1.y) + (p1.z * p1.z));
	return (sum);
}

// multiplies p1 times f
void	fact_vector(point *p1, double f)
{
		p1->x = p1->x * f;
		p1->y = p1->y * f;
		p1->z = p1->z * f;
}

// normates a directionvector
void	norm_vector(point *p1)
{
	double	temp[3];
	double	fact;

	fact = 0.0;
	fact = 1 / sum_vector(*p1);
	printf("fact %f\n", fact);
	fact_vector(p1, fact);
}

// calculates p1xp2 an puts it to result
void	cross_product(point p1, point p2, point *result)
{
	result->x = round(p1.y * p2.z - p1.z * p2.y);
	result->y = round(p1.z * p2.x - p1.x * p2.z);
	result->z = round(p1.x * p2.y - p1.y * p2.x);
}


int main(void)
{
	point *p1;
	point *p2;
	point *p3;

	p1 = new_point(56, 44, -8);
	p2 = new_point(32, 5, -9);
	p3 = new_point(0, 0, 0);

	cross_product(*p1, *p2, p3);
	// norm_vector(p1);

	printf(" %f %f %f", p3->x, p3->y, p3->z);
	return (0);
}

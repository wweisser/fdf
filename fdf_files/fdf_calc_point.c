/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_calc_point.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 13:47:05 by wendelin          #+#    #+#             */
/*   Updated: 2022/08/08 20:00:53 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// for op=1 adds two trippels, for op=-1 substracts two trippels
void	calc_point(t_point p1, t_point p2, t_point *result, int op)
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
void	fact_vector(t_point *p1, float f)
{
		p1->x = p1->x * f;
		p1->y = p1->y * f;
		p1->z = p1->z * f;
}

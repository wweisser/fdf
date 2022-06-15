/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:19:02 by wendelin          #+#    #+#             */
/*   Updated: 2022/06/15 18:54:28 by wendelin         ###   ########.fr       */
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

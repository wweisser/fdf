/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_calc_round.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 13:53:54 by wendelin          #+#    #+#             */
/*   Updated: 2022/08/11 15:15:43 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	rnd(double in, int places)
{
	int		i;
	int		j;
	double	temp;

	i = 1;
	while (places > 0)
	{
		i = i * 10;
		places--;
	}
	temp = (in * i);
	j = temp;
	if (in > 0 && (temp - j) >= 0.5)
		temp++;
	if (in < 0 && (temp + j) <= -0.5)
		temp--;
	temp = (int )temp;
	in = temp / i;
	return (in);
}

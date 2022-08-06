/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_calc_round.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 13:53:54 by wendelin          #+#    #+#             */
/*   Updated: 2022/08/06 13:54:10 by wendelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	rnd(float in, int places)
{
	int		i;
	int		j;
	float	temp;

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
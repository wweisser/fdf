/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_visual.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:00:31 by wendelin          #+#    #+#             */
/*   Updated: 2022/06/14 17:59:38 by wendelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	render(int x, int y, int color, image *im)
{
	int	pixel;

	pixel = y * im->width + x;
	im->addr[pixel] = color;
	return (0);
}


// enter values between 0 and 255
int	set_color(unsigned char trans, unsigned char red, unsigned char green, unsigned char blue)
{
	int	color;

	color = 0;
	color = (trans << 24 | red << 16 | green << 8 | blue);
	return (color);
}


int	color_shift(int dir, image *im)
{
	int	x;
	int	y;
	int blue;

	y = 0;
	blue = 0;
	while (y < im->length)
	{
		if ((y % (im->length / 200)) == 0)
			blue++;
		x = 0;
		while (x < im->width)
		{
			render(x, y, set_color(0, 40, dir, blue), im);
			x++;
		}
		y++;
	}
	return (0);
}


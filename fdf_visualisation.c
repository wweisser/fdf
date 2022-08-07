/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_visualisation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:00:31 by wendelin          #+#    #+#             */
/*   Updated: 2022/08/07 14:15:31 by wendelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// sets the pixelvalue at the coordinate x and y to color
int	render(int x, int y, int color, image im)
{
	int	pixel;

	pixel = y * im.win.x + x;
	im.addr[pixel] = color;
	return (0);
}


// assigns 4bit values (between 0 and 255) for transparency red, green and blue
// to an integer by bitshifting, considering endian 1
int	setcolor(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
	int	color;

	if (t < 0)
		t = 0;
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	if (t > 255)
		t = 255;
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	color = 0;
	color = (t << 24 | r << 16 | g << 8 | b);
	return (color);
}

// goes through y and x of the image and sets each pixel to a ceratain color
int	color_shift(image im)
{
	int	x;
	int	y;
	int	bright;

	y = 0;
	bright = 0;
	while (y < im.win.y)
	{
		if ((y % (im.win.y / 75)) == 0)
			bright++;
		x = 0;
		while (x < im.win.x)
		{
			render(x, y, setcolor(0, bright, bright, bright), im);
			x++;
		}
		y++;
	}
	return (0);
}


void	line(point p1, point p2, image im)
{
	point	np;
	int		color;

	color = (p2.color + p1.color) / 2;
	if ((p1.x == p2.x) && (p1.y == p2.y))
			return ;
	else if ((p1.x == p2.x + 1 || p1.x == p2.x - 1) && (p1.y == p2.y + 1 || p1.y == p2.y - 1))
		return ;
	else if ((p1.y == p2.y) && (p1.x == p2.x + 1 || p1.x == p2.x - 1))
		return ;
	else if ((p1.x == p2.x) && (p1.y == p2.y + 1 || p1.y == p2.y - 1))
		return ;
	np = new_point(round( p1.x + ((p2.x - p1.x) / 2)), round(p1.y + ((p2.y - p1.y) / 2)), 0, color );
	line(p1, np, im);
	line(np, p2, im);
	if ((np.x < im.x) && (np.y < im.y) &&
		(np.x > -im.x) && (np.y > -im.y))
		render((int )(np.x + im.x), (int )(np.y + im.y), color, im);
	return ;
}
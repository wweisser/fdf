/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_visual.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:00:31 by wendelin          #+#    #+#             */
/*   Updated: 2022/06/16 14:54:34 by wendelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// sets the pixelvalue at the coordinate x and y to color 
int	render(int x, int y, int color, image *im)
{
	int	pixel;

	pixel = y * im->x + x;
	im->addr[pixel] = color;
	return (0);
}


// assigns 4bit values (between 0 and 255) for transparency red, green and blue
// to an integer by bitshifting, considering endian 1
int	setcolor(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
	int	color;

	color = 0;
	color = (t << 24 | r << 16 | g << 8 | b);
	return (color);
}

// goes through y and x of the image and sets each pixel to a ceratain color
// the blue proortion increases each row
int	color_shift(int dir, image *im)
{
	int	x;
	int	y;
	int blue;

	y = 0;
	blue = 0;
	while (y < im->y)
	{
		if ((y % (im->y / 200)) == 0)
			blue++;
		x = 0;
		while (x < im->x)
		{
			render(x, y, setcolor(0, 40, dir, blue), im);
			x++;
		}
		y++;
	}
	return (0);
}

// draws the line via render 
void	draw_line(double p1[3], double p2[3], image *im)
{
	int		x;
	int		y;
	double	slope;
	int		clr;
	
	x = 0;
	y = 0;
	clr = setcolor(0, 255, 255, 255);
	if (p1[0] != p2[0])
	{		
		slope = (p2[1] - p1[1]) / (p2[0] - p1[0]);
		while (x < (p2[0] - p1[0]))
		{
			y = x * slope;
			render(x + (im->x / 2) + p1[0], y + (im->x / 2) + p1[1], clr, im);
			x++;
		}
	}
	else
	{
		while (y < (p2[1] - p1[1]))
		{
			render(p1[0] + (im->x / 2) + p1[0], y + (im->x / 2) + p1[1], clr, im);
			y++;
		}
	}
}

// checks if the two points have even x or y values and assigns
// them accordingly to draw_line
void	set_line(double p1[3], double p2[3], image *im)
{
	if (p1[0] < p2[0])
		draw_line(p1, p2, im);
	else if (p1[0] > p2[0])
		draw_line(p2, p1, im);
	else if (p1[0] == p2[0])
	{
		if (p1[1] >= p2[1])
			draw_line(p2, p1, im);
		if (p1[1] < p2[1])
			draw_line(p1, p2, im);
	}
}





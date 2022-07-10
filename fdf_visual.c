/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_visual.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:00:31 by wendelin          #+#    #+#             */
/*   Updated: 2022/07/10 21:49:21 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// sets the pixelvalue at the coordinate x and y to color
int	render(int x, int y, int color, image *im)
{
	int	pixel;

	pixel = y * im->win->x + x;
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
	while (y < im->win->y)
	{
		if ((y % (im->win->y / 200)) == 0)
			blue++;
		x = 0;
		while (x < im->win->x)
		{
			render(x, y, setcolor(0, 40, dir, blue), im);
			x++;
		}
		y++;
	}
	return (0);
}

void	line(point p1, point p2, int color, image *im)
{
	point	np;

	p1.x = (int )(p1.x);
	p1.y = (int )(p1.y);
	p2.x = (int )(p2.x);
	p2.y = (int )(p2.y);
	if ((p1.x == p2.x) && (p1.y == p2.y))
	{
		// printf("gleiches x und y x1:%f y1:%f | x2:%f y2:%f\n", p1.x, p1.y, p2.x, p2.y);
		return ;
	}
	else if ((p1.x == p2.x + 1 || p1.x == p2.x - 1) && (p1.y == p2.y + 1 || p1.y == p2.y - 1))
	{
		return ;
	}
	else if ((p1.y == p2.y) && (p1.x == p2.x + 1 || p1.x == p2.x - 1))
	{
		// printf("gleiches y, x1:%f y1:%f | x2:%f y2:%f\n", p1.x, p1.y, p2.x, p2.y);
		return ;
	}
	else if ((p1.x == p2.x) && (p1.y == p2.y + 1 || p1.y == p2.y - 1))
	{
		return ;
	}
	np = *(new_point((p1.x + ((p2.x - p1.x) / 2)), (p1.y + ((p2.y - p1.y) / 2)), 0));
	line(p1, np, color, im);
	line(p2, np, color, im);
	if ((np.x < im->x) && (np.y < im->y) &&
		(np.x > -im->x) && (np.y > -im->y))
		render((int )(np.x + im->x), (int )(np.y + im->y), color, im);
		// printf("print x1:%f y1:%f\n", (np.x + im->x / 2), (np.y + im->y / 2));
	return ;
}

// draws the line via render
void	draw_line(point p1, point p2, image *im)
{
	int		x;
	int		y1;
	int		y2;
	double	slope;
	int		clr;

	slope = (p2.y - p1.y) / (p2.x - p1.x);
	x = 0;
	y1 = 0;
	y2 = 0;
	clr = setcolor(0, 255, 255, 255);
	if ((int )p1.x != (int )p2.x)
	{
		while (x < (p2.x - p1.x))
		{
			y2 = round(x * slope) + (im->x / 2) + p1.y;
			render(x + (im->x / 2) + p1.x, y2, clr, im);
			// fill_segment(x + p1.x, y1, y2, im);
			y1 = y2;
			x++;
		}
	}
	else
	{
		while (y1 < (p2.y - p1.y))
		{
			// printf("test");
			render(p1.x + (im->x / 2), y1 + (im->x / 2) + p1.y, clr, im);
			y1++;
		}
	}
}

// checks if the two points have even x or y values and assigns
// them accordingly to draw_line
void	set_line(point p1, point p2, image *im)
{
	// printf("p1 x:%f y:%f ====> ", p1.x, p1.y);
	// printf("p2 x:%f y:%f \n", p2.x, p2.y);
	if (p1.x < p2.x)
		draw_line(p1, p2, im);
	else if (p1.x > p2.x)
		draw_line(p2, p1, im);
	else if (p1.x == p2.x)
	{
		if (p1.y >= p2.y)
			draw_line(p2, p1, im);
		if (p1.y < p2.y)
			draw_line(p1, p2, im);
	}
}

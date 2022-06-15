/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_visual.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:00:31 by wendelin          #+#    #+#             */
/*   Updated: 2022/06/15 17:47:07 by wendelin         ###   ########.fr       */
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



void show_line(image *im, double p1[3], double p2[3])
{
	
}

void	show_trigon(image *im, trigon tri)
{
	p1[3]
	p2[3]
	
	show_line(tri)
}

void    display_line(point p1, point p2, int offset, image *im)
{
    int     x;
    int     y;
	double	difx;
	double	dify;
    double  slope;
    point   temp;
    
    x = 0;
    y = 0;
    slope = 1;
    if (((p2.x - p1.x) == 0 && p1.y > p2.y) || p1.x > p2.x)
    {   
        temp = p1;
        p1 = p2;
        p2 = temp;
    }
    if ((p2.x - p1.x) == 0)
    {
        y = p1.y;
        while (y < p2.y)
        {
            render(p1.x + offset, y + offset, setcolor(0, 255, 255, 255), im);
            y++;
        }        
    }
    else
    {
		difx = (p2.x - p1.x);
		dify = (p2.y - p1.y);
        slope = (dify/difx) * slope;
        y = x * slope + p1.y;
        x = 0;
        
        printf("slope: %f | p1:%d:%d | p2:%d:%d \n", slope, p1.x, p1.y, p2.x, p2.y);
        
        while (x < (p2.x - p1.x))
        {
	        y = lround(x * slope);
            // printf("x: %d, y: %d\n", (x+offset), (y+offset));
	        render(x + offset +p1.x, y + offset + p1.y, setcolor(0, 255, 255, 255), im);
	        x++;
        }
    }
}



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_visualisation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:00:31 by wendelin          #+#    #+#             */
/*   Updated: 2022/08/11 14:50:22 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// sets the pixelvalue at the coordinate x and y to color
int	render(int x, int y, int color, t_image im)
{
	int	pixel;

	pixel = y * im.win.x + x;
	im.addr[pixel] = color;
	return (0);
}

// assigns 4bit values (between 0 and 255) for transparency red, green and blue
// to an integer by bitshifting, considering endian 1
int	setc(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
	int	color;

	color = 0;
	color = (t << 24 | r << 16 | g << 8 | b);
	return (color);
}

// goes through y and x of the image and sets each pixel to a ceratain color
int	color_shift(t_image im)
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
			render(x, y, setc(0, bright, bright, bright), im);
			x++;
		}
		y++;
	}
	return (0);
}

void	line(t_point p1, t_point p2, t_image im)
{
	t_point	np;
	int		color;

	color = (p2.color + p1.color) / 2;
	if ((p1.x == p2.x) && (p1.y == p2.y))
		return ;
	else if ((p1.x == p2.x + 1 || p1.x == p2.x - 1) && (p1.y == p2.y + 1
			|| p1.y == p2.y - 1))
		return ;
	else if ((p1.y == p2.y) && (p1.x == p2.x + 1 || p1.x == p2.x - 1))
		return ;
	else if ((p1.x == p2.x) && (p1.y == p2.y + 1 || p1.y == p2.y - 1))
		return ;
	np = value_to_point(round (p1.x + ((p2.x - p1.x) / 2)),
			round (p1.y + ((p2.y - p1.y) / 2)), 0, color);
	line(p1, np, im);
	line(np, p2, im);
	if ((np.x < im.x) && (np.y < im.y)
		&& (np.x > -im.x) && (np.y > -im.y))
		render((int )(np.x + im.x), (int )(np.y + im.y), color, im);
	return ;
}

void	build_scene(t_image im, t_window win)
{
	color_shift(im);
	trans_op(im);
	mlx_put_image_to_window(win.mlx, win.win, im.grid, 0, 0);
}

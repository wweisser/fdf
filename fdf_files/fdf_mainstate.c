/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mainstate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 13:58:55 by wendelin          #+#    #+#             */
/*   Updated: 2022/08/12 00:26:35 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// creates a pointer to a window, asigns memory, creates mlx-state and new 
// window with dimensions x and y, returns pointer to a window
t_window	new_window(t_window *win, int width, int hight)
{
	win->mlx = mlx_init();
	win->x = width;
	win->y = hight;
	win->win = mlx_new_window(win->mlx, width, hight, "fdf");
	win->size = 0;
	win->mouse_state[0] = 0;
	win->mouse_state[1] = 0;
	win->mouse_state[2] = 0;
	return (*win);
}

// creates image of size of the window, assigns bit/pixel and bytes/line,
// endian, color, returns pointer to an image
t_image	new_image(t_image *im, t_window win)
{
	im->win = win;
	im->bits_per_pixel = 32;
	im->bytes_per_line = 4;
	im->endian = 1;
	im->offsetx = 0;
	im->x = win.x / 2;
	im->y = win.y / 2;
	im->grid = NULL;
	im->addr = NULL;
	im->grid = mlx_new_image(win.mlx, win.y, win.x);
	im->addr = (int *)mlx_get_data_addr(im->grid, &im->bits_per_pixel,
			&im->bytes_per_line, &im->endian);
	im->stat = NULL;
	return (*im);
}

void	new_grid(int fd, t_image *im)
{
	char	*input;
	double	**topmap;

	input = NULL;
	topmap = NULL;
	input = read_lines(fd);
	topmap = alloc_lines(topmap, input);
	topmap = alloc_dim(topmap, input, im);
	topmap = fill_topmap(topmap, input, im);
	set_orientation(im, input);
	set_hight(&(im->top_hight), topmap, im->lines);
	translate_topmap(topmap, im->lines, im);
	set_angle(im);
	topmap = free_mem(topmap, im->lines);
	free (input);
}

int	close_state(t_image *im)
{
	if (im->stat != NULL)
		im->stat = free_lst(&(im->stat));
	exit(0);
	return (0);
}

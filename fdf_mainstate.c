/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mainstate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 13:58:55 by wendelin          #+#    #+#             */
/*   Updated: 2022/08/06 14:46:23 by wendelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

// creates a pointer to a window, asigns memory, creates mlx-state and new window
// with dimensions x and y, returns pointer to a window
window	*new_window(int width, int hight)
{
	window	*win;

	win = NULL;
	win = (window *)malloc(sizeof(window));
	win->mlx = mlx_init();
	if (win->mlx == NULL)
		return (NULL);
	// win->win = (void *)mlx_new_window(win->mlx, width, hight, (char *)"fdf");
	if (win->win == NULL)
	{
		free(win->win);
		return (NULL);
	}
	win->x = width;
	win->y = hight;
	win->size = 0;
	return (win);
}

// creates image of size of the window, assigns bit/pixel and bytes/line,
// endian, color, returns pointer to an image
image	*new_image(window *win)
{
	image	*im;

	im = NULL;
	im = (image *)malloc(sizeof(image));
	if (im == NULL)
		return (NULL);
	im->win = win;
	im->bits_per_pixel = 32;
	im->bytes_per_line = 4;
	im->endian = 1;
	im->offsetx = 0;
	im->offsetx = 0;
	im->x = win->x / 2;
	im->y = win->y / 2;
	im->grid = NULL;
	im->addr = NULL;
	im->grid = mlx_new_image(win->mlx, win->y, win->x);
	im->addr = (int *)mlx_get_data_addr(im->grid, &im->bits_per_pixel,
		&im->bytes_per_line, &im->endian);
	im->stat = NULL;
	im->disp = NULL;
	if (im->grid == NULL || im->addr == NULL)
		return (NULL);
	return (im);
}

void	new_grid(int fd, image *im)
{
	char	*input;
	double	**topmap;

	input = NULL;
	topmap = NULL;
	input = read_lines(fd);
	topmap = alloc_lines(topmap, input);
	topmap = alloc_dim(topmap, input, im);
	topmap = fill_topmap(topmap, input, im);
	printf("tophight %f\n", im->top_hight);
	topmap = (double **)free_mem((void **)topmap, im->lines);
	free (input);
}

void	create_grid(image *im, int fd)
{
	new_grid(fd, im);
	set_default(im);
}

void	build_scene(image *im)
{
	color_shift(im);
	trans_op(im);
	mlx_put_image_to_window(im->win->mlx, im->win->win, im->grid, 0, 0);
}


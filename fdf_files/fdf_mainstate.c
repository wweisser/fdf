/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mainstate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 13:58:55 by wendelin          #+#    #+#             */
/*   Updated: 2022/08/08 20:19:07 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// creates a pointer to a window, asigns memory, creates mlx-state and new 
// window with dimensions x and y, returns pointer to a window
t_window	new_window(t_window *win, int width, int hight)
{
	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, width, hight, "fdf");
	win->x = width;
	win->y = hight;
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

// void	check_topmap(double **topmap, int lines)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (j < lines)
// 	{
// 		i = 0;
// 		while (1)
// 		{
// 			if (topmap[j][i] == 2147483647)
// 			{
// 				printf("\n");
// 				break ;
// 			}
// 			else
// 			printf("%f ", topmap[j][i]);
// 			i++;
// 		}
// 		j++;
// 	}
// }

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
	topmap = (double **)free_mem((void **)topmap, im->lines);
	free (input);
}

void	create_grid(t_image *im, int fd)
{
	new_grid(fd, im);
	set_default(im);
}

int	close_state(t_image *im)
{
	mlx_destroy_window(im->win.mlx, im->win.win);
	free_lst(&im->stat);
	exit(0);
	return (0);
}

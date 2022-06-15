/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 10:51:16 by wendelin          #+#    #+#             */
/*   Updated: 2022/06/15 14:28:55 by wendelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// creates a pointer to a window, asigns memory, creates mlx-state and new window
// with dimensions x and y, returns pointer to a window
window    *new_window(int width, int hight)
{
    window   *win;
    
    win = NULL;
	win = malloc(sizeof(window));
	win->mlx = mlx_init();
	if (win->mlx == NULL)
		return (NULL);
    win->win = mlx_new_window(win->mlx, width, hight, "fdf");
    if (win->win == NULL)
	{
		free(win->win);
		return (NULL);
	}
    win->x = width;
    win->y = hight;
    return (win);
}

// creates image of size of the window, assigns bit/pixel and bytes/line,
// endian, color, returns pointer to an image
image    *new_image(window *win)
{
    image   *im;
    
    im = NULL;
    im = malloc(sizeof(image));
    if (im == NULL)
        return (NULL);
    im->win = win;
	im->bits_per_pixel = 32;
	im->bytes_per_line = 4;
	im->endian = 1;
	im->color = 1;
    im->x = win->x;
    im->y = win->y;
    im->grid = NULL;
    im->addr = NULL;
    im->grid = mlx_new_image(win->mlx, win->y, win->x);
    im->addr = (int *)mlx_get_data_addr(im->grid, &im->bits_per_pixel,
        &im->bytes_per_line, &im->endian);
    if (im->grid == NULL || im->addr == NULL)
        return (NULL);
    return (im);
}


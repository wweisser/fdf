/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:38:02 by wendelin          #+#    #+#             */
/*   Updated: 2022/06/14 18:04:43 by wendelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "fdf.h"


#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

#define MLX_ERROR 1

int	mouse_hook(int key, int x, int y, image *im)
{
	y = x + y;
	color_shift(50, im);
	if 	(key == 4)
	{
		rotate_object(0, 10, 0, &im->obj);
		display_object(&im->obj, 400, im);
	}
	if (key == 5)
	{
		rotate_object(0, -10, 0, &im->obj);
		display_object(&im->obj, 400, im);
	}
	mlx_put_image_to_window(im->mlx, im->win, im->grid, 0, 0);
	return (0);
}

void fdf_main(void)
{
	image	*im1;
	object	obj;
	obj = build_object();

	im1 = malloc(sizeof(image));
	im1->mlx = mlx_init();
	if (im1->mlx == NULL)
		return ;
	im1->win = mlx_new_window(im1->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
								"my window");
	if (im1->win == NULL)
	{
		free(im1->win);
		return ;
	}
	im1->length = WINDOW_HEIGHT;
	im1->width = WINDOW_WIDTH;
	im1->bits_per_pixel = 32;
	im1->bytes_per_line = 4;
	im1->endian = 1;
	im1->color = 1;
	im1->mousex = 1;
	im1->mousey = 1;
	im1->grid = mlx_new_image(im1->mlx, WINDOW_HEIGHT, WINDOW_WIDTH);
	im1->addr = (int *)mlx_get_data_addr(im1->grid, &im1->bits_per_pixel, &im1->bytes_per_line, &im1->endian);
	im1->obj = obj;
	
	if (im1->addr == NULL)
	{
		free(im1->addr);
		return ;
	}
	mlx_mouse_hook(im1->win, mouse_hook, im1);
	mlx_loop(im1->mlx);
	free(im1->mlx);
}

int	main(void)
{
	fdf_main();
	return (0);
}


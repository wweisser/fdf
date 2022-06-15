/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:38:02 by wendelin          #+#    #+#             */
/*   Updated: 2022/06/15 18:10:37 by wendelin         ###   ########.fr       */
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
	
	// if 	(key == 4)
	// {
	// 	rotate_object(0, 10, 0, &im->obj);
	// 	display_object(&im->obj, 400, im);
	// }
	// if (key == 5)
	// {
	// 	rotate_object(0, -10, 0, &im->obj);
	// 	display_object(&im->obj, 400, im);
	// }
	if (key == 1)
		mlx_put_image_to_window(im->win->mlx, im->win->win, im->grid, 0, 0);
	return (0);
}

char *fdf_main(void)
{
	window	*win;
	image	*im;
	
	win = NULL;
	im = NULL;
	win = new_window(1000, 1000);
	if (win == NULL)
		return ("on window creation");
	im = new_image(win);
	if (win == NULL)
		return ("on image creation");
	mlx_mouse_hook(win->win, mouse_hook, im);
	mlx_loop(win->mlx);
	free(im->mlx);
	free(win);
	return (0);
}

int	main(void)
{
	fdf_main();
	return (0);
}


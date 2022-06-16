/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:38:02 by wendelin          #+#    #+#             */
/*   Updated: 2022/06/16 14:59:45 by wendelin         ###   ########.fr       */
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
	
	double p0[3];
	double p1[3];
    double p2[3];
	double p3[3];
	double p4[3];
	double p5[3];
	double p6[3];
	double p7[3];
	
	
    trigon *test;

    p0[0] = 0;
    p0[1] = 0;
    p0[2] = 0;
    
    p1[0] = 10;
    p1[1] = 0;
    p1[2] = 0;

    p2[0] = 10;
    p2[1] = 10;
    p2[2] = 0;

	p3[0] = 0;
    p3[1] = 10;
    p3[2] = 0;

	p4[0] = 0;
    p4[1] = 0;
    p4[2] = 10;
	
	p5[0] = 10;
    p5[1] = 0;
    p5[2] = 10;

	p6[0] = 10;
    p6[1] = 10;
    p6[2] = 10;

	p7[0] = 0;
    p7[1] = 10;
    p7[2] = 10;


	set_line(p0, p1, im);
	set_line(p2, p3, im);

	test = new_trigon(p0, p1, p2);
	test = new_trigon(p0, p2, p3);
	test = new_trigon(p4, p5, p6);
	test = new_trigon(p4, p5, p6);
	test = new_trigon(p4, p5, p6);

	draw_trigon(im, test);
	free(test);
	
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


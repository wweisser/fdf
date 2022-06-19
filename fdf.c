/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:38:02 by wendelin          #+#    #+#             */
/*   Updated: 2022/06/19 20:52:43 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "fdf.h"


int	mouse_hook(int key, int x, int y, image *im)
{
	y = x + y;
	color_shift(50, im);

	if (key == 4)
		im->angle[2] = im->angle[2] + 10;
	if (key == 5)
		im->angle[2] = im->angle[2] - 10;
	point *p0;
	point *p1;
	point *p2;
	point *p3;
	point *p4;
	point *p5;


	double cent[3];
	cent[0] = 100;
	cent[1] = 100;
	cent[2] = 0;
	trigon	*test;

	// object	*obj;


	p0 = new_point(400, 0, 0);
	p1 = new_point(-400, 0, 0);
	p2 = new_point(0, 400, 0);
	p3 = new_point(0, -400, 0);

	p4 = new_point(100, 100, 0);
	p5 = new_point(0, 0, 0);



	set_line(*p0, *p1, im);
	set_line(*p2, *p3, im);
	rotmtx(im->angle[0], im->angle[1], im->angle[2], *p5, p4);
	set_line(*p4, *p5, im);

	test = new_sqare(cent, 100);
	// test = new_trigon(p0, p2, p3);
	// test = new_trigon(p4, p5, p6);
	// test = new_trigon(p4, p5, p6);
	// test = new_trigon(p4, p5, p6);

	// draw_trigon(im, test);
	// draw_trigon(im, test + 1);
	// draw_trigon(im, test + 2);
	// draw_trigon(im, test + 3);

	// obj = new_object(test);
	// draw_object(obj, im);
	// free(test);
	// free(obj);

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
	im->angle[0] = 0;
	im->angle[1] = 0;
	im->angle[2] = 0;
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


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:38:02 by wendelin          #+#    #+#             */
/*   Updated: 2022/06/21 18:59:26 by wweisser         ###   ########.fr       */
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
		im->angle[2] = (im->angle[2] + 90 *(M_PI/180));
	if (key == 5)
		im->angle[2] = (im->angle[2] - 90 *(M_PI/180));
	point *p0;
	point *p1;
	point *p2;
	point *p3;
	// point *p4;
	double ctr[3];

	ctr[0] = 100;
	ctr[1] = 100;
	ctr[2] = 0;
	p0 = new_point(400, 0, 0);
	p1 = new_point(-400, 0, 0);
	p2 = new_point(0, 400, 0);
	p3 = new_point(0, -400, 0);
	// p4 = new_point(100, 100, 0);
	// p5 = new_point(0, 0, 0);

	set_line(*p0, *p1, im);
	set_line(*p2, *p3, im);

	new_sqare(ctr, 100, &im->stat);
	// im->p = trans_op(*p4, im);
	// set_line(*(im->p), *p5, im);

	free(p0);
	free(p1);
	free(p2);
	free(p3);
	// free(p4);



	// draw_trigon(im, test);
	// draw_trigon(im, test + 1);
	// draw_trigon(im, test + 2);
	// draw_trigon(im, test + 3);

	// obj = new_object(test);
	// draw_object(obj, im);
	// free(test);
	// free(obj);

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


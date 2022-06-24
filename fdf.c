/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:38:02 by wendelin          #+#    #+#             */
/*   Updated: 2022/06/24 16:44:58 by wendelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "fdf.h"


int	mouse_hook(int key, int x, int y, image *im)
{
	double ctr[3];
	double angle[3];

	point *p0;
	point *p1;
	point *p2;
	point *p3;
	ctr[0] = 0;
	ctr[1] = 0;
	ctr[2] = 50;
	angle[0] = 0;
	angle[1] = 0;
	angle[2] = 0;


	p0 = new_point(400, 0, 0);
	p1 = new_point(-400, 0, 0);
	p2 = new_point(0, 400, 0);
	p3 = new_point(0, -400, 0);
	y = x + y;
	color_shift(50, im);

	if (key == 1)
	{
		new_sqare(ctr, angle, 100, im);
		angle[1] = 90 *(M_PI/180);
		new_sqare(ctr, angle, 100, im);
		angle[1] = -90 *(M_PI/180);
		new_sqare(ctr, angle, 100, im);
		angle[1] = -180 *(M_PI/180);
		new_sqare(ctr, angle, 100, im);
		angle[1] = 0;
		angle[0] = -90 *(M_PI/180);
		new_sqare(ctr, angle, 100, im);
		angle[0] = 90 *(M_PI/180);
		new_sqare(ctr, angle, 100, im);
	}
	if (key == 4)
	{		
		im->angle[0] = (im->angle[0] + 5 *(M_PI/360));
		im->angle[1] = (im->angle[1] + 5 *(M_PI/360));
		im->angle[2] = (im->angle[2] + 5 *(M_PI/360));
		printf("angles %f %f %f\n", im->angle[0], im->angle[1], im->angle[2]);
		
	}
	if (key == 5)
	{
		im->angle[0] = (im->angle[0] - 5 *(M_PI/360));
		im->angle[1] = (im->angle[1] - 5 *(M_PI/360));
		im->angle[2] = (im->angle[2] - 5 *(M_PI/360));
		printf("angles %f %f %f\n", im->angle[0], im->angle[1], im->angle[2]);
	}
	trans_op(im->stat, &im->disp, im->angle);
	draw_trigons(im->disp, im);
	// free_lst(&im->stat);
	free_lst(&im->disp);
	printf("after free %p\n", im->stat);
	// im->p = trans_op(*p4, im);
	// set_line(*(im->p), *p5, im);
	// free(p4);
	set_line(*p0, *p1, im);
	set_line(*p2, *p3, im);
	mlx_put_image_to_window(im->win->mlx, im->win->win, im->grid, 0, 0);
	free(p0);
	free(p1);
	free(p2);
	free(p3);
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


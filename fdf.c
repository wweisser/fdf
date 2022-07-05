/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:38:02 by wendelin          #+#    #+#             */
/*   Updated: 2022/07/05 21:04:22 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "fdf.h"


int	mouse_hook(int key, int x, int y, image *im)
{
	double ctr[3];
	double angle[3];

	point	*p0;
	point	*p1;
	point	*p2;
	point	*p3;
	point	*p4;
	point	*p5;
	point	*p6;
	point	*p7;
	trigon	*temp;

	ctr[0] = 0;
	ctr[1] = 0;
	ctr[2] = 0;
	angle[0] = 0;
	angle[1] = 0;
	angle[2] = 0;


	p0 = new_point(0, 0, 0);
	p1 = new_point(1, 0, 0);
	p2 = new_point(1, 1, 0);
	p3 = new_point(0, 1, 0);
	p4 = new_point(0, 0, -1);
	p5 = new_point(1, 0, -1);
	p6 = new_point(1, 1, -1);
	p7 = new_point(0, 1, -1);

	y = x + y;
	color_shift(50, im);

	if (key == 1)
	{
		free_lst(&im->stat);
		// temp = new_trigon(p1, p2, p3);
		// addtrigon(&im->stat, temp);
		temp = new_trigon(p0, p1, p3);
		addtrigon(&im->stat, temp);
		temp = new_trigon(p0, p4, p1);
		addtrigon(&im->stat, temp);
		// temp = new_trigon(p5, p1, p4);
		// addtrigon(&im->stat, temp);
		// temp = new_trigon(p5, p1, p2);
		// addtrigon(&im->stat, temp);
		// temp = new_trigon(p2, p5, p6);
		// addtrigon(&im->stat, temp);
		temp = new_trigon(p0, p3, p4);
		addtrigon(&im->stat, temp);
		// temp = new_trigon(p4, p3, p7);
		// addtrigon(&im->stat, temp);
		// temp = new_trigon(p3, p7, p2);
		// addtrigon(&im->stat, temp);
		// temp = new_trigon(p7, p6, p2);
		// addtrigon(&im->stat, temp);
		// temp = new_trigon(p4, p5, p6);
		// addtrigon(&im->stat, temp);
		// temp = new_trigon(p4, p6, p7);
		// addtrigon(&im->stat, temp);
	}

	if (key == 4)
	{
		im->angle[0] = (im->angle[0] + 5 *(M_PI/360));
		if (im->angle[0] > (2*M_PI) || im->angle[0] < 0)
			im->angle[0] = 0;
		// im->angle[1] = (im->angle[1] + 5 *(M_PI/360));
		// if (im->angle[1] > (2*M_PI) || im->angle[1] < 0)
		// 	im->angle[1] = 0;
		im->angle[2] = (im->angle[2] + 5 *(M_PI/360));
		if (im->angle[2] > (2*M_PI) || im->angle[2] < 0)
			im->angle[2] = 0;
		printf("angles %f %f %f\n", im->angle[0], im->angle[1], im->angle[2]);
	}

	if (key == 5)
	{
		im->angle[0] = (im->angle[0] - 5 *(M_PI/360));
		if (im->angle[0] > (2*M_PI) || im->angle[0] < 0)
			im->angle[0] = 0;
		// im->angle[1] = (im->angle[1] - 5 *(M_PI/360));
		// if (im->angle[1] > (2*M_PI) || im->angle[1] < 0)
		// 	im->angle[1] = 0;
		im->angle[2] = (im->angle[2] - 5 *(M_PI/360));
		if (im->angle[2] > (2*M_PI) || im->angle[2] < 0)
			im->angle[2] = 0;
		printf("angles %f %f %f\n", im->angle[0], im->angle[1], im->angle[2]);
	}

	trans_op(im->stat, &im->disp, im->angle, im);
	draw_trigons(im->disp, im);

	free_lst(&im->disp);
	// printf("after free %p\n", im->stat);
	// im->p = trans_op(*p4, im);
	// set_line(*(im->p), *p5, im);
	// free(p4);
	// set_line(*p0, *p1, im);
	// set_line(*p2, *p3, im);

	// orthomtx = create_othromtx(im->win);
	// mxp(*orthomtx, *p6, p0, 1);
	// mxp(*orthomtx, *p7, p1, 1);
	// mxp(*orthomtx, *p8, p2, 1);
	// mxp(*orthomtx, *p9, p3, 1);

	// fact_vector(p0, 10);
	// fact_vector(p1, 10);
	// fact_vector(p2, 10);
	// fact_vector(p3, 10);

	// set_line(*p6, *p7, im);
	// set_line(*p7, *p8, im);
	// set_line(*p8, *p9, im);
	// set_line(*p9, *p6, im);

	// set_line(*p0, *p1, im);
	// set_line(*p1, *p2, im);
	// set_line(*p2, *p3, im);
	// set_line(*p3, *p0, im);

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
	im->win->view = new_point(0, 0, -100);
	im->win->open_angle = 1;
	mlx_mouse_hook(win->win, mouse_hook, im);
	mlx_loop(win->mlx);
	free(im->mlx);
	free(win);
	free_lst(&im->stat);
	return (0);
}

int	main(void)
{
	fdf_main();
	return (0);
}

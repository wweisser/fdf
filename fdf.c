/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:38:02 by wendelin          #+#    #+#             */
/*   Updated: 2022/07/13 22:08:38 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "fdf.h"


// int	mouse_hook(int key, int x, int y, image *im)
// {

// 	key = x + y;
// 	color_shift(50, im);
// 	// printf("after free %p\n", im->stat);
// 	// im->p = trans_op(*p4, im);
// 	// set_line(*(im->p), *p5, im);
// 	// free(p4);
// 	// set_line(*p0, *p1, im);
// 	// set_line(*p2, *p3, im);
// 	return (0);
// }

void	create_grid(image *im, int fd)
{
	new_grid(fd , im);
	// point	*p0;
	// point	*p1;
	// point	*p2;
	// point	*p3;
	// point	*p4;
	// point	*p5;
	// point	*p6;
	// point	*p7;
	// trigon	*temp;

	// p0 = new_point(0, 0, 0);
	// p1 = new_point(1, 0, 0);
	// p2 = new_point(1, 1, 0);
	// p3 = new_point(0, 1, 0);
	// p4 = new_point(0, 0, 1);
	// p5 = new_point(1, 0, 1);
	// p6 = new_point(1, 1, 1);
	// p7 = new_point(0, 1, 1);

	// free_lst(&im->stat);
	// temp = new_trigon(p1, p2, p3);
	// addtrigon(&im->stat, temp);
	// temp = new_trigon(p0, p1, p3);
	// addtrigon(&im->stat, temp);
	// temp = new_trigon(p0, p4, p1);
	// addtrigon(&im->stat, temp);
	// temp = new_trigon(p5, p1, p4);
	// addtrigon(&im->stat, temp);
	// temp = new_trigon(p5, p1, p2);
	// addtrigon(&im->stat, temp);
	// temp = new_trigon(p2, p5, p6);
	// addtrigon(&im->stat, temp);
	// temp = new_trigon(p0, p3, p4);
	// addtrigon(&im->stat, temp);
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

void	build_scene(image *im)
{
	// int		color = setcolor(0, 255, 255, 255);
	// point	*p1 = new_point(100.3543435, 0, 0);
	// point	*p2	= new_point(0, 0, 0);
	color_shift(50, im);

	trans_op(im->stat, &im->disp, im->angle, im);
	// printf("----6----\n");
	draw_trigons(im->disp, im);
	printf("----7----\n");
	// line (*p1, *p2, color, im);
	mlx_put_image_to_window(im->win->mlx, im->win->win, im->grid, 0, 0);
	printf("----8----\n");
	free_lst(&im->disp);
}

int	keydown(int key, image *im)
{
	if (key == 13)
		im->angle[0] = (im->angle[0] + 10) % 720;
	if (key == 1)
		im->angle[0] = (im->angle[0] - 10) % 720;
	if (key == 0)
		im->angle[1] = (im->angle[1] + 10) % 720;
	if (key == 2)
		im->angle[1] = (im->angle[1] - 10) % 720;
	if (key == 126)
		im->win->open_angle++;
	if (key == 125)
		im->win->open_angle--;
	build_scene(im);
	if (key == 53)
		mlx_destroy_window(im->win->mlx, im->win->win);
	return (0);
}

char *fdf_main(int fd)
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
	im->win->open_angle = 30;
	create_grid(im, fd);
	win->win = (void *)mlx_new_window(win->mlx, 1000, 1000, (char *)"fdf");
	build_scene(im);
	// mlx_mouse_hook(win->win, mouse_hook, im);
	mlx_hook(win->win, 2, 1L<<0, keydown, im);
	printf("----1----\n");
	mlx_loop(win->mlx);
	printf("----2----\n");
	free_lst(&im->stat);
	printf("----3----\n");
	free(im->mlx);
	printf("----4----\n");
	free(win);
	printf("----5----\n");
	free_lst(&im->stat);
	return (0);
}

int	main(void)
{
	int	fd;

	fd = open("42.fdf", O_RDONLY);
	printf("filedescriptor %d\n", fd);
	// system("leaks a.out");
	fdf_main(fd);
	return (0);
}

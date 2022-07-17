/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:38:02 by wendelin          #+#    #+#             */
/*   Updated: 2022/07/17 22:43:04 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "fdf.h"

void	build_scene(image *im)
{
	color_shift(im);

	trans_op(im->stat, &im->disp, im->angle, im);
	draw_trigons(im->disp, im);
	mlx_put_image_to_window(im->win->mlx, im->win->win, im->grid, 0, 0);
	free_lst(&im->disp);
}

int	mouse_hook(int key, int x, int y, image *im)
{
	if (key == 4)
		im->win->size++;
	if (key == 5)
		im->win->size--;
	if (key == 1 && x > 800)
		im->angle[1] = (im->angle[1] - 15) % 720;
	if (key == 1 && x < 200)
		im->angle[1] = (im->angle[1] + 15) % 720;
	if (key == 1 && y > 800)
		im->angle[0] = (im->angle[0] - 15) % 720;
	if (key == 1 && y < 200)
		im->angle[0] = (im->angle[0] + 15) % 720;
	printf("angle 0 %d angle 1 %d\n", im->angle[0], im->angle[1]);
	build_scene(im);
	return (0);
}

void	create_grid(image *im, int fd)
{
	new_grid(fd, im);
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
		adjst_hight(im->stat, 1);
	if (key == 125)
		adjst_hight(im->stat, -1);
	if (key == 123)
		im->offset--;
	if (key == 124)
		im->offset++;
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
	create_grid(im, fd);
	win->win = (void *)mlx_new_window(win->mlx, 1000, 1000, (char *)"fdf");
	build_scene(im);
	mlx_mouse_hook(win->win, mouse_hook, im);
	mlx_hook(win->win, 2, 1L<<0, keydown, im);
	mlx_loop(win->mlx);
	free_lst(&im->stat);
	free(im->mlx);
	free(win);
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

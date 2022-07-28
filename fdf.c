/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:38:02 by wendelin          #+#    #+#             */
/*   Updated: 2022/07/28 16:38:09 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "fdf.h"

void	build_scene(image *im)
{
	color_shift(im);
	trans_op(im);
	mlx_put_image_to_window(im->win->mlx, im->win->win, im->grid, 0, 0);
}

int	adjust_mousestate(int x, int y, image *im)
{
	if (x > im->win->mouse_state[0])
		im->offsetx += 10;

	if (x < im->win->mouse_state[0])
		im->offsetx -= 10;

	if (y > im->win->mouse_state[1])
		im->offsety += 10;

	if (y < im->win->mouse_state[1])
		im->offsety -= 10;

	im->win->mouse_state[0] = x;
	im->win->mouse_state[1] = y;
	build_scene(im);
	return (0);
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
	set_default(im);
}

int	mouse_down(int key, int x, int y, image *im)
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
	if (key == 1)
		im->win->mouse_state[2] = 1;
	build_scene(im);
	return (x + y);
}

int	mouse_up(int key, int x, int y, image *im)
{
	if (key == 1)
		im->win->mouse_state[2] = 0;
	printf("%d \n", im->win->mouse_state[2]);
	return (x + y);
}

int	move_obj(int x, int y, image *im)
{
	if (im->win->mouse_state[2] == 1)
		adjust_mousestate(x, y, im);
	return (0);
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
	if (key == 126 && im->top_hight < 10)
		im->top_hight += 0.1;
	if (key == 125 && im->top_hight > 0.1)
		im->top_hight -= 0.1;
	if (key == 49)
		set_default(im);
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
	// mlx_mouse_hook(win->win, mouse_hook, im);
	mlx_hook(win->win, 2, 1L<<0, keydown, im);
	mlx_hook(win->win, 4, 1L<<0, mouse_down, im);
	mlx_hook(win->win, 6, 1L<<0, move_obj, im);
	mlx_hook(win->win, 5, 1L<<0, mouse_up, im);



	mlx_loop(win->mlx);
	free_lst(&im->stat);
	free(im->mlx);
	free(win);
	free_lst(&im->stat);
	return (0);
}

int	main(int argc, char *argv[])
{
	int	fd;

	if (argc == 1)
		return (0);
	else
	{
		fd = open(argv[1], O_RDONLY);
		fdf_main(fd);
	}
		// system("leaks a.out");
	return (0);
}

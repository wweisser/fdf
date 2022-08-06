/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:38:02 by wendelin          #+#    #+#             */
/*   Updated: 2022/08/06 15:19:08 by wendelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char *fdf_bonus(int fd)
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
	mlx_hook(win->win, 2, 1L<<0, keydown, im);
	mlx_hook(win->win, 4, 1L<<0, mouse_down, im);
	mlx_hook(win->win, 6, 1L<<0, move_obj, im);
	mlx_hook(win->win, 5, 1L<<0, mouse_up, im);
	mlx_loop(win->mlx);
	free_lst(&im->stat);
	free(im->mlx);
	free(win);
    free (im);
	return (0);
}

char *fdf_mandatory(int fd)
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
	mlx_loop(win->mlx);
	free_lst(&im->stat);
	free(im->mlx);
	free(win);
    free (im);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:38:02 by wendelin          #+#    #+#             */
/*   Updated: 2022/08/07 19:43:33 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int fdf_bonus(int fd)
{
	window	win;
	image	im;

	win.win = NULL;
	win.mlx = NULL;
	im.addr = NULL;
	win = new_window(&win, 1000, 1000);
	im = new_image(&im, win);
	create_grid(&im, fd);
	build_scene(im, win);
	mlx_hook(win.win, 2, 1L<<0, keydown, &im);
	mlx_hook(win.win, 4, 1L<<0, mouse_down, &im);
	mlx_hook(win.win, 6, 1L<<0, move_obj, &im);
	mlx_hook(win.win, 5, 1L<<0, mouse_up, &im);
	mlx_loop(win.mlx);
	free_lst(&im.stat);
	free(im.mlx);
	free(win.win);
	free(win.mlx);
	return (0);
}

int fdf_mandatory(int fd)
{
	window	win;
	image	im;

	win.win = NULL;
	win.mlx = NULL;
	im.addr = NULL;
	win = new_window(&win, 1000, 1000);
	im = new_image(&im, win);
	create_grid(&im, fd);
	build_scene(im, win);
	mlx_loop(win.mlx);
	free_lst(&im.stat);
	free(im.mlx);
	free(win.win);
	free(win.mlx);
	return (fd);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:38:02 by wendelin          #+#    #+#             */
/*   Updated: 2022/08/11 04:41:10 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fdf_bonus(int fd)
{
	t_window	win;
	t_image		im;

	win.win = NULL;
	win.mlx = NULL;
	im.addr = NULL;
	win = new_window(&win, 1000, 1000);
	im = new_image(&im, win);
	new_grid(fd, &im);
	build_scene(im, win);
	mlx_hook(win.win, 2, 1L << 0, keydown_bonus, &im);
	mlx_hook(win.win, 4, 1L << 0, mouse_down, &im);
	mlx_hook(win.win, 6, 1L << 0, move_obj, &im);
	mlx_hook(win.win, 5, 1L << 0, mouse_up, &im);
	mlx_hook(win.win, 5, 1L << 0, mouse_up, &im);
	mlx_hook(win.win, 17, 1L << 0, close_state, &im);
	mlx_loop(win.mlx);
	close_state(&im);
	return (0);
}

int	fdf_mandatory(int fd)
{
	t_window	win;
	t_image		im;

	win.win = NULL;
	win.mlx = NULL;
	im.addr = NULL;
	win = new_window(&win, 1000, 1000);
	im = new_image(&im, win);
	new_grid(fd, &im);
	build_scene(im, win);
	mlx_hook(win.win, 2, 1L << 0, keydown_mandatory, &im);
	mlx_hook(win.win, 17, 0, close_state, &im);
	mlx_loop(win.mlx);
	close_state(&im);
	return (fd);
}

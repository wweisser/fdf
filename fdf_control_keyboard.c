/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_control_keyboard.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:13:20 by wendelin          #+#    #+#             */
/*   Updated: 2022/08/06 14:15:19 by wendelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

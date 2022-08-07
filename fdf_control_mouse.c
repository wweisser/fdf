/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_control_mouse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:11:26 by wendelin          #+#    #+#             */
/*   Updated: 2022/08/07 14:38:04 by wendelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	adjust_mousestate(int x, int y, image *im)
{
	if (x > im->win.mouse_state[0])
		im->offsetx += 10;

	if (x < im->win.mouse_state[0])
		im->offsetx -= 10;

	if (y > im->win.mouse_state[1])
		im->offsety += 10;

	if (y < im->win.mouse_state[1])
		im->offsety -= 10;

	im->win.mouse_state[0] = x;
	im->win.mouse_state[1] = y;
	build_scene(*im);
	return (0);
}

int	mouse_down(int key, int x, int y, image *im)
{
	if (key == 4)
		im->win.size++;
	if (key == 5)
		im->win.size--;
	if (key == 1 && x > 800)
		im->angle[1] = (im->angle[1] - 15) % 720;
	if (key == 1 && x < 200)
		im->angle[1] = (im->angle[1] + 15) % 720;
	if (key == 1 && y > 800)
		im->angle[0] = (im->angle[0] - 15) % 720;
	if (key == 1 && y < 200)
		im->angle[0] = (im->angle[0] + 15) % 720;
	if (key == 1)
		im->win.mouse_state[2] = 1;
	build_scene(*im);
	return (x + y);
}

int	mouse_up(int key, int x, int y, image *im)
{
	if (key == 1)
		im->win.mouse_state[2] = 0;
	return (x + y);
}

int	move_obj(int x, int y, image *im)
{
	if (im->win.mouse_state[2] == 1)
		adjust_mousestate(x, y, im);
	return (0);
}
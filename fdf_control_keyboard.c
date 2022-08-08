/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_control_keyboard.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:13:20 by wendelin          #+#    #+#             */
/*   Updated: 2022/08/08 17:07:14 by wweisser         ###   ########.fr       */
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
	build_scene(*im, im->win);
	if (key == 53)
		close_state(im);
	return (0);
}

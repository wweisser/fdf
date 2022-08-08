/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_perspective.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 09:32:35 by wweisser          #+#    #+#             */
/*   Updated: 2022/08/08 20:25:16 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	default_image(t_image *im)
{
	im->angle[0] = 490;
	im->angle[1] = 15;
	im->angle[2] = 45;
	im->offsetx = 0;
	im->offsety = 0;
}

void	set_default(t_image *im)
{
	float		vert_hight;
	float		vert_low;
	float		temp1;
	t_trigon	*temp;

	vert_hight = 0;
	vert_low = 0;
	temp = im->stat;
	im->win.size = 1;
	while (temp)
	{
		if (temp->p2.y > vert_hight)
			vert_hight = temp->p2.y;
		if (temp->p2.y < vert_low)
			vert_low = temp->p2.y;
		temp = temp->next;
	}
	temp1 = im->column;
		temp1 = (im->lines + im->column) / 2;
	if ((im->x / temp1) > 1)
		im->win.size = im->x / temp1;
	im->top_hight = temp1 / (temp1 + (vert_hight + vert_low));
	default_image(im);
}

// transformas all objects in an image to the current angle
void	trans_op(t_image im)
{
	t_mtx		*rotmtx;
	t_trigon	*temps;
	t_trigon	tempd;

	rotmtx = create_rotmtx(im.angle[0], im.angle[1], im.angle[2]);
	temps = im.stat;
	while (temps)
	{
		mxt(*rotmtx, *temps, &tempd, im.top_hight);
		scale(&tempd, im.win.size);
		translate(&tempd, im.offsetx, im.offsety);
		if (tempd.p1.x < 600 && tempd.p1.x > -600
			&& tempd.p1.y < 600 && tempd.p1.y > -600)
		{
			line(tempd.p1, tempd.p2, im);
			line(tempd.p2, tempd.p0, im);
		}
		temps = temps->next;
	}
	free (rotmtx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_perspective.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 09:32:35 by wweisser          #+#    #+#             */
/*   Updated: 2022/08/12 00:35:01 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_angle(t_image *im)
{
	im->angle[0] = 490;
	im->angle[1] = 15;
	im->angle[2] = 45;
}

void	set_orientation(t_image *im, char *in)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (in[i] != '\0')
	{
		if (in[i] == ' ' && ((in[i + 1] > 47 && in[i + 1] < 58)
				|| in[i + 1] == '-'))
			j++;
		if (in[i] == '\n')
			k++;
		i++;
	}
	im->offsetx = (j / k) / -2;
	im->offsety = -(k / 2);
	if (im->offsety < im->offsetx && im->offsety != 0)
		im->win.size = 100 / (im->offsety * -1);
	else if (im->offsetx != 0)
		im->win.size = 100 / (im->offsetx * -1);
	if (im->win.size < 2)
		im->win.size = 2;
}

void	set_hight(double *top_hight, double **topmap, int lines)
{
	int		i;
	int		j;
	double	hight;
	double	low;

	j = 0;
	hight = 0;
	low = 0;
	while (j < lines)
	{
		i = 0;
		while (topmap[j][i] != 2147483647)
		{
			if (topmap[j][i] > hight)
				hight = topmap[j][i];
			if (topmap[j][i] < low)
				low = topmap[j][i];
			i++;
		}
		j++;
	}
	if ((hight - low) != 0 || ((hight - low) < 1 && (hight - low) > -1))
		*top_hight = 1;
	else
		*top_hight = 100 / ((hight - low) * 2);
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

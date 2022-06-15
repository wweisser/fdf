/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:23:40 by wendelin          #+#    #+#             */
/*   Updated: 2022/06/15 18:52:23 by wendelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "fdf.h"
#define PI 3.1415926

// takes a tree vertizes creates and returns a pointer to an new trigon
// calculates the dirtction vector d1 and d2 and the normale n by d2xd1
trigon  *new_trigon(double p0[3], double p1[3], double p2[3])
{
    trigon  *tri;

    tri = NULL;
    tri = malloc(sizeof(trigon));
    if (tri == NULL)
        return (NULL);
    tri->p[0] = p0[0];
    tri->p[1] = p0[1];
    tri->p[2] = p0[2];
    calc_point(p1, p0, tri->d1, -1);
    calc_point(p2, p0, tri->d2, -1);
    tri->n[0] = tri->d2[1] * tri->d1[2] - tri->d2[2] * tri->d1[1];
    tri->n[1] = tri->d2[2] * tri->d1[0] - tri->d2[0] * tri->d1[2];
    tri->n[2] = tri->d2[0] * tri->d1[1] - tri->d2[1] * tri->d1[0];
    return (tri);
}


point create_point(int x, int y, int z)
{
    point   point;
    
    point.x = x;
    point.y = y;
    point.z = z;
    return (point);
}

point	**allocarray()
{
    int i;
	point **array;

	i = 0;
	array = malloc(2 * sizeof(point *));
	while (i < 2)
	{
        array[i] = malloc(2 * sizeof(point));
        i++;
    }
	return (array);
}

object	build_object(void)
{
    object  shape;

    shape.pointarray = allocarray(2, 2);
    shape.displyarray = allocarray(2, 2);
    shape.pointarray[0][0] = create_point(100, 0, 0);
    shape.pointarray[0][1] = create_point(200, 0, 0);
    shape.pointarray[1][0] = create_point(200, 300, 0);
    shape.pointarray[1][1] = create_point(0, 50, 0);
    shape.displyarray[0][0] = create_point(0, 0, 0);
    shape.displyarray[0][1] = create_point(0, 0, 0);
    shape.displyarray[1][0] = create_point(0, 0, 0);
    shape.displyarray[1][1] = create_point(0, 0, 0);
    shape.xangle = 0;
    shape.yangle = 0;
    shape.zangle = 0;
    shape.xsize = 2;
    shape.ysize = 2;
    shape.color = setcolor(0, 250, 250, 250);
    return (shape);
}

point    rotate(double y, double ß, double a, point *p)
{
    point	np;
    
    a = (a / 180) * PI;
    ß = (ß / 180) * PI;
    y = (y / 180) * PI;
	
	np.x = p->x * (cos(a) * cos(ß)) + 
		p->y * (cos(a) * sin(ß) * sin(y) - sin(a) * cos(y)) + 
		p->z * (cos(a) * sin(ß) * cos(y) + cos(a) * sin(y));
	np.y = p->x * (sin(a) * cos(ß)) + 
		p->y * (sin(a) * sin(ß) * sin(y) + cos(a) * cos(y)) + 
		p->z * (sin(a) * sin(ß) * cos(y) - cos(a) * sin(y));
    np.z = p->x * (-sin(ß)) + p->y * (sin(a) * cos(ß)) + p->z *(cos(a * cos(ß)));
	return (np);
}

void    rotate_object(int xangle, int yangle, int zangle, object *obj)
{
    int i;
    int j;

    j = 0;
	obj->xangle = obj->xangle + xangle;
    obj->yangle = obj->yangle + yangle;
    obj->zangle = obj->zangle + zangle;
    while (j < obj->ysize)
    {
        i = 0;
        while (i < obj->xsize)
        {
            obj->displyarray[j][i] = rotate(obj->xangle, obj->yangle, obj->zangle,  &obj->pointarray[j][i]);
            i++;
        }
        j++;
    }
}


void	display_object(object *obj, int offset, image *im)
{
    display_line(obj->displyarray[0][0], obj->displyarray[0][1], offset, im);
    display_line(obj->displyarray[0][1], obj->displyarray[1][0], offset, im);
    display_line(obj->displyarray[1][0], obj->displyarray[1][1], offset, im);
    display_line(obj->displyarray[1][1], obj->displyarray[0][0], offset, im);
}

// int	main(void)
// {
// 	object *test;
// 	test = build_object();
// 	return (0);
// }
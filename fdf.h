/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:33:09 by wendelin          #+#    #+#             */
/*   Updated: 2022/06/14 18:18:27 by wendelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../mlx_Linux/mlx.h"
# include "../mlx_Linux/mlx_int.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>

#define RED_PIXEL 0xFFAABB

typedef struct s_point
{
	int	x;
	int y;
	int z;
}			point;

typedef struct s_object
{
	point	**pointarray;
	point	**displyarray;
	int		xangle;
	int		yangle;
	int		zangle;
	int		xsize;
	int		ysize;
	int		color;
}			object;

typedef struct	s_image
{
	int		color;
	object	obj;
	void	*mlx;
	void	*win;
	void	*grid;
	int		*addr;
	int		width;
	int		length;
	int		endian;
	int		bytes_per_line;
	int		bits_per_pixel;
	int		mousex;
	int		mousey;
}			image;

point 	create_point(int x, int y, int z);
point   rotate(double xangle, double yangle, double zangle, point *point);
object	build_object();
void    rotate_object( int x, int y, int z, object *obj);
void	display_object(object *obj, int color, image *im);
void	ft_bzero(void *buf, size_t n);
void 	fdf_main(void);
int		render(int x, int y, int color, image *im);
int		set_color(unsigned char trans, unsigned char red, unsigned char green, unsigned char blue);
int		color_shift(int dir, image *im);
int		create_line(int x1, int y1, int x2, int y2, image *im);
int		mouse_hook(int key, int x, int y, image *im);

#endif
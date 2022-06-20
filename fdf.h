/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:33:09 by wendelin          #+#    #+#             */
/*   Updated: 2022/06/20 22:36:17 by wendelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../mlx/mlx.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>

#define RED_PIXEL 0xFFAABB


//first instance rows, second instance collums
typedef struct matrix
{
	double	m[4][4];
}			mtx;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}			point;

// holds the anchor point p, direction vectors d1 and d2 and the normal vector n
// it represents a trigon of three points p, p+d1, p+d2
typedef struct s_trigon
{
	point	*p0;
	point	*p1;
	point	*p2;
	point	*n;
}			trigon;

// holds a poiner to two arrays of trigons, static hold the original vertices
// of the object, draw holds the vertices after perspective transformation
typedef struct s_object
{
	trigon *stat;
	trigon *draw;
}			object;

// contains the state of a window
typedef struct s_window
{
	void	*mlx;
	void	*win;
	int		x;
	int		y;
}			window;

// contains the state of an image of size x and y
typedef struct	s_image
{
	window	*win;
	void	*mlx;
	void	*grid;
	int		*addr;
	int		x;
	int		y;
	int		endian;
	int		bytes_per_line;
	int		bits_per_pixel;
	int		color;
	double	angle[3];
}			image;

window	*new_window(int width, int hight);
image	*new_image(window *win);
mtx		*new_mtx(void);
point	*new_point(double x, double y, double z);
trigon	*new_trigon(point *p0, point *p1, point *p2);
trigon	*new_sqare(double ctr[3], int l);
// object	*new_object(trigon *tri);
void	draw_trigon(image *im, trigon *tri);
void	draw_line(point p1, point p2, image *im);
// void	draw_object(object *obj, image *im);
void	set_line(point p1, point p2, image *im);
void	calc_point(point p1, point p2, point *result, int op);
void	fact_vector(point p1, double f);
void	cross_product(point p1, point p2, point *result);
mtx		*create_rotmtx(double y, double ß, double a);
void	mxp(mtx *c, point in, point *out, int ortho);
void	trans_op(point in, point *out, image *im);
int		render(int x, int y, int color, image *im);
int		setcolor(unsigned char t, unsigned char r, unsigned char g, unsigned char b);
int		color_shift(int dir, image *im);
int		create_line(int x1, int y1, int x2, int y2, image *im);
int		mouse_hook(int key, int x, int y, image *im);
double	sum_vektor(point p1);
double	dot_product(double p1[3], double p2[3]);
char	*fdf_main(void);

#endif
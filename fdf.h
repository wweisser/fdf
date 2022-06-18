/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:33:09 by wendelin          #+#    #+#             */
/*   Updated: 2022/06/16 20:05:40 by wendelin         ###   ########.fr       */
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


//first instance rows, second instance collums
typedef struct matrix
{
	double	m[4][4];
}			mtx;

// holds the anchor point p, direction vectors d1 and d2 and the normal vector n
// it represents a trigon of three points p, p+d1, p+d2
typedef struct s_trigon
{
	double	p0[3];
	double	p1[3];
	double	p2[3];
	double	n[3];
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
}			image;

window  *new_window(int width, int hight);
image   *new_image(window *win);
trigon  *new_trigon(double p0[3], double p1[3], double p2[3]);
object  *new_object(trigon *tri);
void	draw_trigon(image *im, trigon *tri);
void	draw_line(double p1[3], double p2[3], image *im);
void	set_line(double p1[3], double p2[3], image *im);
void	calc_point(double p1[3], double p2[3], double result[3], int op);
void    fact_vector(double p1[3], double f);
void    cross_product(double p1[3], double p2[3], double result[3]);
char 	*fdf_main(void);
int		render(int x, int y, int color, image *im);
int		setcolor(unsigned char t, unsigned char r, unsigned char g, unsigned char b);
int		color_shift(int dir, image *im);
int		create_line(int x1, int y1, int x2, int y2, image *im);
int		mouse_hook(int key, int x, int y, image *im);
double	sum_vektor(double p1[3]);
double	dot_product(double p1[3], double p2[3]);


#endif
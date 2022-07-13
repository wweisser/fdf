/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:33:09 by wendelin          #+#    #+#             */
/*   Updated: 2022/07/13 22:04:13 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../mlx/mlx.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "get_next_line.h"

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
struct s_trigon
{
	point			*p0;
	point			*p1;
	point			*p2;
	point			*n;
	struct s_trigon	*next;
};
typedef struct s_trigon	trigon;

// contains the state of a window
typedef struct s_window
{
	void	*mlx;
	void	*win;
	int		x;
	int		y;
	point	*viewer;
	double	open_angle;
}			window;

// contains the state of an image of size x and y
typedef struct	s_image
{
	window	*win;
	trigon	*stat;
	trigon	*disp;
	int		angle[3];
	int		*addr;
	int		x;
	int		y;
	int		endian;
	int		bytes_per_line;
	int		bits_per_pixel;
	int		color;
	void	*mlx;
	void	*grid;
}			image;

int		mouse_hook(int key, int x, int y, image *im);
window	*new_window(int width, int hight);

image	*new_image(window *win);
point	*new_point(double x, double y, double z);
mtx		*new_mtx(void);
trigon	*new_trigon(point *p0, point *p1, point *p2);
void	addtrigon(trigon **head, trigon *new);
void	new_sqare(double ctr[3], int l, image *im);

void	rottrigon(trigon in, trigon *out, mtx rotmtx);
void	mxp(mtx c, point in, point *out, int ortho);
void	mxt(mtx c, trigon in, trigon *out, int ortho);
mtx		*create_rotmtx(double y, double ß, double a);
mtx		*create_othromtx(window *win);
void	trans_op(trigon *stat, trigon **disp, int angle[3], image *im);
void	translate(trigon *tri, int zoffset);
void	scale(trigon *tri, int fact);

void	draw_trigons(trigon *tri_lst, image *im);
int		setcolor(unsigned char t, unsigned char r, unsigned char g, unsigned char b);
void	set_line(point p1, point p2, image *im);
void	line(point p1, point p2, int color, image *im);
void	draw_line(point p1, point p2, int color , image *im);
int		create_line(int x1, int y1, int x2, int y2, image *im);
int		render(int x, int y, int color, image *im);
int		color_shift(int dir, image *im);

void	cross_product(point *p1, point *p2, point *result);
void	fact_vector(point *p1, double f);
void	norm_vector(point *p1);
void	calc_point(point p1, point p2, point *result, int op);
double	sum_vector(point p1);
double	dot_product(double p1[3], double p2[3]);
double	scalar_product(point *d1, point *d2);
double	rnd(double in, int places);

int		read_lines(char **input, int fd);
void	new_grid(int fd, image *im);
void	built_grid(int **top_map, image *im, int lines, int rows);
void	create_grid(image *im, int fd);

void	free_lst(trigon **head);
char 	*fdf_main(int fd);

// libft
int		ft_strlen(const char *c);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
int		ft_strlen(const char *c);
size_t	ft_strlcpy(char *dst, const char *src, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_atoi(const char *str);

# endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:33:09 by wendelin          #+#    #+#             */
/*   Updated: 2022/08/06 15:24:29 by wendelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "mlx/mlx.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft/libft.h"
# include "fdf_input/fdf_input.h"

//first instance rows, second instance collums
typedef struct matrix
{
	float	m[4][4];
}			mtx;

// HIER WEITERMACHEN:	1. GESAMTE BERECHNUNG UNF SPEICHERUNG AUF INT UMSTELLEN

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	int	color;
}		point;

// holds the anchor point p, direction vectors d1 and d2 and the normal vector n
// it represents a trigon of three points p, p+d1, p+d2
struct s_trigon
{
	point			p0;
	point			p1;
	point			p2;
	point			n;
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
	float	size;
	int		mouse_state[3];
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
	int		offsetx;
	int		offsety;
	float	top_hight;
	int		lines;
	int		column;
	void	*mlx;
	void	*grid;
}			image;

// fdf_calc_mtx.c
mtx		*new_mtx(void);
mtx 	*create_rotmtx(float y, float ß, float a);
void	mxp(mtx c, point in, point *out);

// fdf_calc_point.c 
void	calc_point(point p1, point p2, point *result, int op);
void	fact_vector(point *p1, float f);
void	fact_vector(point *p1, float f);

// fdf_calc_round.c
float	rnd(float in, int places);

// fdf_calc_trigon.c
void	rottrigon(trigon in, trigon *out, mtx rotmtx);
void	adjst_top(trigon *temp, float top_hight);
void	mxt(mtx c, trigon in, trigon *out, float top_hight);
void	translate(trigon *tri, int offsetx, int offsety);
void	scale(trigon *tri, int fact);

// fdf_calc_vector.c
float	scalar_product(point *d1, point *d2);
void	cross_product(point *p1, point *p2, point *result);
float	dot_product(float p1[3], float p2[3]);
float	sum_vector(point p1);
void	norm_vector(point *p1);

// fdf_control_keyboard.c
int	keydown(int key, image *im);

// fdf_control_mouse.c
int	adjust_mousestate(int x, int y, image *im);
int	mouse_down(int key, int x, int y, image *im);
int	mouse_up(int key, int x, int y, image *im);
int	move_obj(int x, int y, image *im);

// fdf_input_main.c
double	transfer_numb(const char *in, image * im);
double	**fill_topmap(double **topmap, char *in, image *im);

// fdf_input_mem.c
void	**free_mem(void **input, int size);
double	**new_topmap(char **input, double **top_map, int lines);
double	**alloc_lines(double **topmap, char *in);
double	**alloc_dim(double **topmap, char *in, image *im);

// fdf_input_read.c
int	decodehex(char c);
double	read_hexdec(const char *in);
char	*read_lines(int fd);

// fdf_mainstate.c
window	*new_window(int width, int hight);
image	*new_image(window *win);
void	new_grid(int fd, image *im);
void	create_grid(image *im, int fd);
void	build_scene(image *im);

// fdf_perspective.c
void	set_default(image *im);
void	trans_op(image *im);

// fdf_structure_mem.c
void	addtrigon(trigon **head, trigon *new);
void	free_lst(trigon **head);

// fdf_structure.c
point	new_point(float x, float y, float z, int color);
trigon	*new_trigon(point p0, point p1, point p2);
void	build_square(double **tp, int i[4], image *im);

// fdf_visualisation.c
int	render(int x, int y, int color, image *im);
int	setcolor(unsigned char t, unsigned char r, unsigned char g, unsigned char b);
int	color_shift(image *im);
void	line(point p1, point p2, image *im);

// fdf.c
char *fdf_mandatory(int fd);
char *fdf_bonus(int fd);

# endif
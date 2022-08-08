/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:33:09 by wendelin          #+#    #+#             */
/*   Updated: 2022/08/08 20:29:48 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"

//first instance rows, second instance collums
struct	s_matrix
{
	float		m[4][4];
};
typedef struct s_matrix	t_mtx;

struct	s_point
{
	float	x;
	float	y;
	float	z;
	int		color;
};
typedef struct s_point	t_point;
// holds the anchor point p, direction vectors d1 and d2 and the normal vector n
// it represents a trigon of three points p, p+d1, p+d2
struct	s_trigon
{
	t_point			p0;
	t_point			p1;
	t_point			p2;
	t_point			n;
	struct s_trigon	*next;
};
typedef struct s_trigon	t_trigon;

// contains the state of a window
struct	s_window
{
	void	*mlx;
	void	*win;
	int		x;
	int		y;
	float	size;
	int		mouse_state[3];
};
typedef struct s_window	t_window;

// contains the state of an image of size x and y
struct	s_image
{
	t_trigon	*stat;
	t_window	win;
	int			angle[3];
	int			*addr;
	int			x;
	int			y;
	int			endian;
	int			bytes_per_line;
	int			bits_per_pixel;
	int			offsetx;
	int			offsety;
	float		top_hight;
	int			lines;
	int			column;
	void		*grid;
};
typedef struct s_image	t_image;

// fdf_calc_mtx.c
t_mtx		*new_mtx(void);
t_mtx		*create_rotmtx(float y, float b, float a);
void		mxp(t_mtx c, t_point in, t_point *out);

// fdf_calc_point.c 
void		calc_point(t_point p1, t_point p2, t_point *result, int op);
void		fact_vector(t_point *p1, float f);
void		fact_vector(t_point *p1, float f);

// fdf_calc_round.c
float		rnd(float in, int places);

// fdf_calc_trigon.c
void		rottrigon(t_trigon in, t_trigon *out, t_mtx rotmtx);
void		adjst_top(t_trigon *temp, float top_hight);
void		mxt(t_mtx c, t_trigon in, t_trigon *out, float top_hight);
void		translate(t_trigon *tri, int offsetx, int offsety);
void		scale(t_trigon *tri, int fact);

// fdf_calc_vector.c
float		scalar_product(t_point *d1, t_point *d2);
void		cross_product(t_point *p1, t_point *p2, t_point *result);
float		dot_product(float p1[3], float p2[3]);
float		sum_vector(t_point p1);
void		norm_vector(t_point *p1);

// fdf_control_keyboard.c
int			keydown_bonus(int key, t_image *im);
int			keydown_mandatory(int key, t_image *im);

// fdf_control_mouse.c
int			adjust_mousestate(int x, int y, t_image *im);
int			mouse_down(int key, int x, int y, t_image *im);
int			mouse_up(int key, int x, int y, t_image *im);
int			move_obj(int x, int y, t_image *im);

// fdf_input_main.c
double		transfer_numb(const char *in, t_image *im);
double		**fill_topmap(double **topmap, char *in, t_image *im);

// fdf_input_mem.c
void		**free_mem(void **input, int size);
double		**new_topmap(char **input, double **top_map, int lines);
double		**alloc_lines(double **topmap, char *in);
double		**alloc_dim(double **topmap, char *in, t_image *im);

// fdf_input_read.c
int			decodehex(char c);
double		read_hexdec(const char *in);
char		*read_lines(int fd);

// fdf_mainstate.c
t_window	new_window(t_window *win, int width, int hight);
t_image		new_image(t_image *im, t_window win);
void		new_grid(int fd, t_image *im);
void		create_grid(t_image *im, int fd);
int			close_state(t_image *im);

// fdf_perspective.c
void		set_default(t_image *im);
void		trans_op(t_image im);

// fdf_structure_mem.c
void		addtrigon(t_trigon **head, t_trigon *new);
void		free_lst(t_trigon **head);

// fdf_structure.c
t_point		new_point(float x, float y, float z, int color);
t_trigon	*new_trigon(t_point p0, t_point p1, t_point p2);
void		build_square(double **tp, int i[4], t_image *im);

// fdf_visualisation.c
int			render(int x, int y, int color, t_image im);
int			color_shift(t_image im);
void		line(t_point p1, t_point p2, t_image im);
void		build_scene(t_image im, t_window win);
int			setc(unsigned char t, unsigned char r,
				unsigned char g, unsigned char b);

// fdf.c
int			fdf_mandatory(int fd);
int			fdf_bonus(int fd);

#endif
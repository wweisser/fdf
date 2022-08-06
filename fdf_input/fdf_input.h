/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_input.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 11:31:44 by wendelin          #+#    #+#             */
/*   Updated: 2022/08/06 12:42:57 by wendelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_INPUT_H
# define FDF_INPUT_H

# include "../fdf.h"
# include "../libft/libft.h"

// fdf_input_read.c
int	    decodehex(char c);
double	read_hexdec(const char *in);
char	*read_lines(int fd);

// fdf_input_mem.c
void	**free_mem(void **input, int size);
double	**new_topmap(char **input, double **top_map, int lines);
double	**alloc_lines(double **topmap, char *in);


#endif
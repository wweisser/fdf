/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_input_mem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:08:23 by wendelin          #+#    #+#             */
/*   Updated: 2022/08/11 23:29:27 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	**free_mem(double **input, int size)
{
	while (size >= 0)
	{
		free (input[size]);
		size--;
	}
	free (input);
	input = NULL;
	return (input);
}

double	**alloc_lines(double **topmap, char *in)
{
	int	i;
	int	lines;

	i = 0;
	lines = 0;
	topmap = NULL;
	if (in == NULL)
		return (NULL);
	while (1)
	{
		if (in[i] == '\n' || in[i] == '\0')
			lines++;
		if (in[i] == '\0')
			break ;
		i++;
	}
	topmap = (double **)malloc((lines + 1) * sizeof(int *));
	if (topmap == NULL)
		return (NULL);
	topmap[lines] = NULL;
	return (topmap);
}

double	*alloc_row(double **topmap, double *line, int len, int row)
{
	line = NULL;
	line = (double *)ft_calloc(len + 1, sizeof(double));
	if (line == NULL)
	{
		topmap = free_mem(topmap, row);
		return (NULL);
	}
	else
		line[len] = 2147483647;
	return (line);
}

double	**alloc_dim(double **topmap, char *in, t_image *im)
{
	int		i;

	i = 0;
	im->lines = 0;
	im->column = 1;
	if (topmap == NULL)
		return (NULL);
	while (1)
	{
		if (in[i] == ' ' && ((in[i + 1] > 47 && in[i + 1] < 58)
				|| in[i + 1] == '-'))
			im->column++;
		if (in[i] == '\n' || in[i] == '\0')
		{
			topmap[im->lines] = alloc_row(topmap, topmap[im->lines],
					im->column, im->lines);
			im->column = 1;
			im->lines++;
		}
		if (in[i] == '\0')
			break ;
		i++;
	}
	return (topmap);
}

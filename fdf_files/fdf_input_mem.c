/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_input_mem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:08:23 by wendelin          #+#    #+#             */
/*   Updated: 2022/08/08 20:18:35 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	**free_mem(void **input, int size)
{
	while (size <= 0)
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
		return (0);
	while (in[i] != '\0')
	{
		if (in[i] == '\n')
			lines++;
		i++;
	}
	topmap = (double **)malloc((lines + 1) * sizeof(int *));
	if (topmap == NULL)
		return (NULL);
	topmap[lines] = NULL;
	return (topmap);
}

double	**alloc_dim(double **topmap, char *in, t_image *im)
{
	int		i;
	double	*temp;

	i = 0;
	im->lines = 0;
	im->column = 1;
	while (in[i] != '\0')
	{
		if (in[i] == ' ' && ((in[i + 1] > 47 && in[i + 1] < 58)
				|| in[i + 1] == '-'))
			im->column++;
		if (in[i] == '\n')
		{
			temp = ft_calloc(im->column + 1, sizeof(double));
			if (temp == NULL)
				return (0);
			topmap[im->lines] = temp;
			topmap[im->lines][im->column] = 2147483647;
			if (in[i + 1] != '\0')
				im->column = 1;
			im->lines++;
		}
		i++;
	}
	return (topmap);
}

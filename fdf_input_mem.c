/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_input_mem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:08:23 by wendelin          #+#    #+#             */
/*   Updated: 2022/08/07 23:51:37 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

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

// allocates memory for the topogrphical map.
double	**new_topmap(char **input, double **top_map, int lines)
{
	int	i;
	int	j;
	int	numb_of_digets;

	j = 0;
	top_map = malloc(lines * sizeof(double *));
	if (top_map ==  NULL)
		return (NULL);
	while (lines != 0 && j <= lines)
	{
		i = 0;
		numb_of_digets = 1;
		while (input[j][i] != '\0')
		{
			if (input[j][i] == ' ' && ((input[j][i + 1] > 47 && input[j][i + 1] < 58) || input[j][i + 1] == '-'))
				numb_of_digets++;
			i++;
		}
		top_map[j] = ft_calloc(numb_of_digets + 1, sizeof(double));
		top_map[j][numb_of_digets] = 2147483647;
		j++;
	}
	return (top_map);
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

double	**alloc_dim(double **topmap, char *in, image *im)
{
	int		i;
	double	*temp;

	i = 0;
	im->lines = 0;
	im->column = 0;
	temp = NULL;
	while (in[i] != '\0')
	{
		if (in[i] == ' ' && ((in[i + 1] > 47 && in[i + 1] < 58) || in[i + 1] == '-'))
			im->column++;
		if (in[i] == '\n')
		{
			temp = ft_calloc(im->column + 1, sizeof(double));
			if (temp == NULL)
				return (0);
			topmap[im->lines] = temp;
			topmap[im->lines][im->column] = 2147483647;
			if (in[i + 1] != '\0')
				im->column = 0;
			im->lines++;
		}
		i++;
	}
	return (topmap);
}

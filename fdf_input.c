/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 10:15:18 by wweisser          #+#    #+#             */
/*   Updated: 2022/07/28 16:36:29 by wweisser         ###   ########.fr       */
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

int	decodehex(char c)
{
	int	i;

	i = 0;
	if (c >= 48 && c <= 57)
		return (c - 48);
	else
	{
		while (i <= 7)
		{
			if (c == i + 65 || c == i + 97)
				return (i + 10);
			i++;
		}
	}
	return (0);
}

double	read_hexdec(const char *in)
{
	int		i;
	double		numb;
	int		factor;

	if (in == NULL)
		return (0);
	numb = 0;
	i = 0;
	factor = 1;
	while (in[i] != ' ' && in[i] != '\n' && in[i] != '\0')
		i++;
	while (in[i] != 'x' && i > 0)
	{
		i--;
		numb = numb + (decodehex(in[i]) * factor);
		factor = factor * 16;
	}
	while (numb > 1)
		numb = numb / 10;
	return (numb);
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

//###################################################
// void	TOPMAPTESTER(double **top_map)
// {
// 	int	i;
// 	int	j;

// 	j = 0;
// 	while (top_map[j] != NULL)
// 	{
// 		i = 0;
// 		while (top_map[j][i] != 2147483647)
// 		{
// 			printf("%f ", top_map[j][i]);
// 			i++;
// 		}
// 		printf("\n");
// 		j++;
// 	}
// }
//####################################################

// reads a text into input and returns the number of lines
char	*read_lines(int fd)
{
	char	buffer[5101];
	char	*temp;
	char	*input;
	int		read_chars;

	read_chars = read(fd, buffer, 5100);
	if (read_chars < 5100)
		buffer[read_chars] = '\0';
	input = malloc(5101 * sizeof(char));
	if (input != NULL)
		input = (char *)ft_memmove(input, buffer, 5101);
	while (read_chars == 5100 && input != NULL)
	{
		temp = input;
		read_chars = read(fd, buffer, 5100);
		if (read_chars < 5100)
			buffer[read_chars] = '\0';
		input = ft_strjoin(temp, buffer);
		free (temp);
	}
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
	if (*topmap == NULL)
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

double	transfer_numb(const char *in, image * im)
{
	int		i;
	double	numb;

	i = 1;
	numb = 0;
	numb = atoi(in);
	if (numb > im->top_hight && numb < 2147483646.000000)
		im->top_hight = numb;
	while (in[i] != ' ' && in[i] != '\0')
	{
		if (in[i] == ',')
	// printf("numb %c, \n", in[i]);
			numb = numb + read_hexdec(in + i + 1);
		i++;
	}
	return (numb);
}

double	**fill_topmap(double **topmap, char *in, image *im)
{
	int		i[4];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	while (in[i[0]] != '\0')
	{
		if (in[i[0]] == ' ' && ((in[i[0] + 1] > 47 && in[i[0] + 1] < 58) || in[i[0] + 1] == '-'))
		{
			topmap[i[2]][i[1]] = transfer_numb(in + i[0], im);
			if (i[1] > 0 && i[2] > 0 && i[1] < i[3])
				build_square(topmap, i, im);
			i[1]++;
		}
		else if (in[i[0]] == '\n')
		{
			i[3] = i[1];
			i[1] = 0;
			i[2]++;
		}
		i[0]++;
	}
	return (topmap);
}

void	new_grid(int fd, image *im)
{
	char	*input;
	double	**topmap;

	input = NULL;
	topmap = NULL;
	input = read_lines(fd);
	topmap = alloc_lines(topmap, input);
	topmap = alloc_dim(topmap, input, im);
	topmap = fill_topmap(topmap, input, im);
	printf("tophight %f\n", im->top_hight);
	topmap = (double **)free_mem((void **)topmap, im->lines);
	free (input);
}

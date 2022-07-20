/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 10:15:18 by wweisser          #+#    #+#             */
/*   Updated: 2022/07/20 15:01:46 by wweisser         ###   ########.fr       */
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



int	decodehex(char c, char key[17])
{
	int	i;

	i = 0;
	while (key[i] != '\0')
	{
		if (c == key[i])
			return (i);
		i++;
	}
	return (-1);
}

int	read_hexdec(const char *in)
{
	int		i;
	int		numb;
	int		factor;

	if (in == NULL)
		return (0);
	numb = 0;
	factor = 1;
	i = ft_strlen(in) - 1;
	while (in[i] != 'x' && i > 0)
	{
		numb = numb + (decodehex(in[i], "0123456789ABCDEF") * factor);
		factor = factor * 16;
		i--;
	}
	return (numb);
}


float	read_number(char *numb)
{
	float	out;
	// double	postcomma;
	char	**numbcompontens;

	if (numb == NULL)
		return (0);
	numbcompontens = ft_split(numb, ',');
	// out = atoi(numb);
	out = atoi(numbcompontens[0]);
	// postcomma = read_hexdec(numbcompontens[1]);
	// while (postcomma > 1)
	// 	postcomma = postcomma / 10;
	// out = out + postcomma;
	// if (postcomma != 0)
	// 	free_mem ((void **)numbcompontens, 2);
	// else
		free_mem((void **)numbcompontens, 1);
	return	(out);
}


// allocates memory for the topogrphical map.
float	**new_topmap(char **input, float **top_map, int lines)
{
	int	i;
	int	j;
	int	numb_of_digets;

	j = 0;
	top_map = malloc(lines * sizeof(float *));
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
		top_map[j] = ft_calloc(numb_of_digets + 1, sizeof(float));
		top_map[j][numb_of_digets] = 2147483647;
		j++;
	}
	return (top_map);
}

//###################################################
void	TOPMAPTESTER(int **top_map)
{
	int	i;
	int	j;

	j = 0;
	while (top_map[j] != NULL)
	{
		i = 0;
		while (top_map[j][i] != 2147483647)
		{
			printf("%d ", top_map[j][i]);
			i++;
		}
		printf("\n");
		j++;
	}
}
//####################################################

// Puts fills the chars from proc_input to the top_map + convertsthem them to int
int	load_topmap(float **top_map, char **proc_input, int lines)
{
	int		i;
	int		j;
	char	**temp;

	j = 0;
	// TOPMAPTESTER(top_map, lines);
	while (j < lines)
	{
		temp = ft_split(proc_input[j], ' ');
		i = 0;
		while(top_map[j][i] != 2147483647)
		{

			top_map[j][i] = read_number(temp[i]);
			i++;
		}
		free_mem((void **)temp, i);
		j++;
	}
	return (i);
}

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

int	**alloc_lines(int **topmap, char *in)
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
	topmap = (int **)malloc((lines + 1) * sizeof(int *));
	if (*topmap == NULL)
		return (NULL);
	topmap[lines] = NULL;
	return (topmap);
}

int	**alloc_dim(int **topmap, char *in, image *im)
{
	int	i;
	int *temp;

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
			temp = ft_calloc(im->column + 1, sizeof(int));
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

int	**fill_topmap(int **topmap, char *in, image *im)
{
	printf("presplit\n");
	int		i[4];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	printf("postsplit\n");
	while (in[i[0]] != '\0')
	{
		if (in[i[0]] == ' ' && ((in[i[0] + 1] > 47 && in[i[0] + 1] < 58) || in[i[0] + 1] == '-'))
		{
			topmap[i[2]][i[1]] = atoi(in + (i[0] + 1));
			if (i[1] > 0 && i[2] > 0 && i[1] < i[3])
				build_square(topmap, i[1], i[2], im);
				// printf("0");
			i[1]++;
		}
		if (in[i[0]] == '\n')
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
	int		**topmap;
	// char	**proc_input;

	input = NULL;
	topmap = NULL;

	input = read_lines(fd);
	// printf("input : %s\n", input);
	topmap = alloc_lines(topmap, input);
	printf("lines allocated\n");
	topmap = alloc_dim(topmap, input, im);
	printf("dimension allocated\n");
	topmap = fill_topmap(topmap, input, im);
	printf("lines %d columns %d :\n", im->lines, im->column);
	TOPMAPTESTER(topmap);


	// built_grid(topmap, im->lines, im->column, im);

	topmap = (int **)free_mem((void **)topmap, im->lines);
	free (input);
}

// 1. FILL-ALGORYTHMUS WEITER OPTIMIEREN
// 2. TRIGONS AUF INTEGER UMSTELLEN, KALKULATION AUS DEN INTGERN HERAUS
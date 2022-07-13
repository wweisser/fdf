/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 10:15:18 by wweisser          #+#    #+#             */
/*   Updated: 2022/07/13 11:38:00 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

// reads a text into input and returns the number of lines
int read_lines(char **input, int fd)
{
	int	i;
	char *line;

	i = 0;
	*input = get_next_line(fd);
	while (*input != NULL)
	{
		line = get_next_line(fd);
		// printf(" input:%s \n", *input);
		if (line == NULL)
			break ;
		*input = ft_strjoin(*input, line);
		free (line);
		i++;
	}
	return (i);
}

// allocates memory for the topogrphical map.
int **new_topmap(char **input, int **top_map, int lines)
{
	int	i;
	int	j;
	int	numb_of_digets;

	j = 0;
	top_map = malloc(lines * sizeof(int *));
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
		top_map[j] = ft_calloc(numb_of_digets + 1, sizeof(int));
		// INSERT PROTECTION
		top_map[j][numb_of_digets] = 2147483647;
		j++;
	}
	return (top_map);
}

void	free_mem(void **input, int size)
{
	while (size <= 0)
	{
		free (input[size]);
		size--;
	}
	free (input);
	input = NULL;
}

//###################################################
void	TOPMAPTESTER(int **top_map, int lines)
{
	int	i;
	int	j;

	j = 0;
	while (j < lines)
	{
		i = 0;
		while (top_map[j][i] != 2147483647)
		{
			printf("%d ", top_map[j][i]);
			i++;
		}
		j++;
		printf("\n");
	}
}
//####################################################

// Puts fills the chars from proc_input to the top_map + convertsthem them to int
int	load_topmap(int **top_map, char **proc_input, int lines)
{
	int		i;
	int		j;
	char	**temp;

	j = 0;
	TOPMAPTESTER(top_map, lines);
	while (j < lines)
	{
		temp = ft_split(proc_input[j], ' ');
		i = 0;
		while(top_map[j][i] != 2147483647)
		{
			top_map[j][i] = ft_atoi(temp[i]);
			i++;
		}
		free_mem((void **)temp, i);
		j++;
	}
	return (i);
}

void	new_grid(int fd, image *im)
{
	char	*input;
	int		**top_map;
	char	**proc_input;
	int		dim[2];

	dim[0] = 0;
	dim[1] = 0;
	input = NULL;
	top_map = NULL;
	proc_input = NULL;

	dim[0] = read_lines(&input, fd);
	proc_input = ft_split(input, '\n');
	top_map = new_topmap(proc_input, top_map, dim[0]);
	dim[1] = load_topmap(top_map, proc_input, dim[0]);
	TOPMAPTESTER(top_map, dim[0]);
	built_grid(top_map, im, dim[0], dim[1]);
	free_mem((void **)proc_input, dim[0]);
	free_mem((void **)top_map, dim[0]);
}
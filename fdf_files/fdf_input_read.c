/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_input_read.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 11:33:32 by wendelin          #+#    #+#             */
/*   Updated: 2022/08/08 19:16:29 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	double	numb;
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

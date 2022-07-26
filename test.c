/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:21:35 by wendelin          #+#    #+#             */
/*   Updated: 2022/07/26 22:34:48 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>



int	ft_strlen(const char *c)
{
	int	i;

	i = 0;
	while (c[i] != '\0')
		i++;
	return (i);
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

float	read_number(char *numb)
{
	double	postcomma;

	if (numb == NULL)
		return (0);
	postcomma = read_hexdec(numb);
	while (postcomma > 1)
		postcomma = postcomma / 10;
	return	(postcomma);
}


int main(void)
{
	double t = 3;
	int	j = 3;
	char test = 'C';
	printf("test %d \n", decodehex(test));
	// test = rnd(test, 0);
	t = read_number("20,0xFF0000 ");
	t = t - (int )t;
	printf(" %f ", t);
	return (0);
}

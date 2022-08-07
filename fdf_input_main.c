/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_input_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:17:03 by wendelin          #+#    #+#             */
/*   Updated: 2022/08/07 23:51:52 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

double	transfer_numb(const char *in , image *im)
{
	int		i;
	double	numb;

	i = 1;
	numb = 0;
	numb = atoi(in);
	if (numb > im->top_hight && numb < 2147483647)
		im->top_hight = numb;
	while (in[i] != ' ' && in[i] != '\0')
	{
		if (in[i] == ',')
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
	topmap[0][0] = transfer_numb(in, im);
	while (in[i[0]] != '\0')
	{
		if (in[i[0]] == ' ' && ((in[i[0] + 1] > 47 && in[i[0] + 1] < 58) || in[i[0] + 1] == '-'))
		{
			topmap[i[2]][i[1]] = transfer_numb(in + i[0], im);
			if (i[1] > 0 && i[2] > 0 && i[1] < i[3])
				build_square(topmap, i, im);
			i[1]++;
		}
		else if (in[i[0]] == '\n'  && ((in[i[0] + 1] > 47 && in[i[0] + 1] < 58) || in[i[0] + 1] == '-'))
		{
			i[3] = i[1];
			topmap[i[2]][0] = transfer_numb(in + i[0], im);
			i[1] = 0;
			i[2]++;
			printf("test %f\n", topmap[i[2]][0]);
		}
		i[0]++;
	}
	return (topmap);
}

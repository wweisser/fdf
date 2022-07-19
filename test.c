/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:21:35 by wendelin          #+#    #+#             */
/*   Updated: 2022/07/18 17:39:01 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}			point;

point	*new_point(double x, double y, double z)
{
	point	*p;

	p = NULL;
	p = (point *)malloc(sizeof(point));
	if (p == NULL)
		return (NULL);
	p->x = x;
	p->y = y;
	p->z = z;
	return (p);
}

// returns the sum of a vector
double	sum_vector(point p1)
{
	double  sum;
	sum = sqrt((p1.x * p1.x)+ (p1.y * p1.y) + (p1.z * p1.z));
	return (sum);
}

// multiplies p1 times f
void	fact_vector(point *p1, double f)
{
		p1->x = p1->x * f;
		p1->y = p1->y * f;
		p1->z = p1->z * f;
}

// normates a directionvector
void	norm_vector(point *p1)
{
	double	temp[3];
	double	fact;

	fact = 0.0;
	fact = 1 / sum_vector(*p1);
	printf("fact %f\n", fact);
	fact_vector(p1, fact);
}

// calculates p1xp2 an puts it to result
void	cross_product(point p1, point p2, point *result)
{
	result->x = round(p1.y * p2.z - p1.z * p2.y);
	result->y = round(p1.z * p2.x - p1.x * p2.z);
	result->z = round(p1.x * p2.y - p1.y * p2.x);
}

double	rnd(double in, int places)
{
	int		i;
	int		j;
	double	temp;

	i = 1;
	while (places > 0)
	{
		i = i * 10;
		places--;
	}
	temp = (in * i);
	j = temp;
	if (in > 0 && (temp - j) >= 0.5)
		temp++;
	if (in < 0 && (temp + j) <= -0.5)
		temp--;
	temp = (int )temp;
	in = temp / i;
	return (in);
}

int	ft_strlen(const char *c)
{
	int	i;

	i = 0;
	while (c[i] != '\0')
		i++;
	return (i);
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

// double	readnumber(char *numb)
// {
// 	double	out;
// 	double	postcomma;
// 	char	**numbcompontens;

// 	numbcompontens = ft_split(numb, ',');
// 	out = atoi(numbcompontens[0]);
// 	postcomma = read_hexdec(numbcompontens[0]);
// 	while (postcomma > 1)
// 		postcomma = postcomma / 10;
// 	out = out + postcomma;
// 	return	(out);
// }

int main(void)
{
	double test;
	test = read_hexdec("0xFF0000");
	// test = rnd(test, 0);
	printf(" %f ", test);
	return (0);
}

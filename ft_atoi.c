/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:11:36 by wweisser          #+#    #+#             */
/*   Updated: 2022/07/11 18:35:30 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	check_sign(const char *str, int state[2])
{
	int	i;

	i = 0;
	while (str[i] == '\t' || str[i] == ' ' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f' )
		i++;
	if ((str[i] == 45 || str[i] == 43) && (str[i + 1] == 45
			|| str[i + 1] == 43))
		return ;
	if (str[i] == 45)
	{
		state[1] = 1;
		i++;
	}
	if (str[i] == 43)
		i++;
	state[0] = i;
	return ;
}

	int	ft_atoi(const char *str)
{
	int			i;
	long long	numb;
	int			state[2];

	state[0] = -1;
	state[1] = -1;
	check_sign(str, state);
	i = state[0];
	numb = 0;
	if (state[0] == -1)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] < 48 || str[i] > 57
			|| numb < (-2147483648) || numb > 2147483647)
			break ;
		numb = ((numb * 10) - (str[i] - 48));
		i++;
	}
	numb = numb * state[1];
	if (numb < (-2147483648))
		return (0);
	if (numb > (2147483647))
		return (-1);
	return (numb);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:10:25 by wendelin          #+#    #+#             */
/*   Updated: 2022/08/08 14:06:17 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char *argv[])
{
	int	fd;

	if (argc == 1)
		return (0);
	else
	{
		fd = open(argv[1], O_RDONLY);
		fdf_bonus(fd);
	}
	system("leaks fdf");
	return (0);
}

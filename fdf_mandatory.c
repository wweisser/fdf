/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mandatory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:02:31 by wendelin          #+#    #+#             */
/*   Updated: 2022/08/06 15:19:27 by wendelin         ###   ########.fr       */
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
		fdf_mandatory(fd);
	}
	return (0);
}

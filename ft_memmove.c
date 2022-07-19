/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 21:23:45 by wweisser          #+#    #+#             */
/*   Updated: 2022/07/19 21:04:29 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// checks if &dest[0] is in &src, returns 1 else 0.
static int	dest_in_src(char *dest, const char *src, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (&src[i] == &dest[0])
			return (1);
		i++;
	}
	return (0);
}

void	*ft_memmove(void *dest, const void *src, unsigned int n)
{
	unsigned int	i;
	char			*pdest;
	const char		*psrc;

	i = 0;
	if (src == 0 && dest == 0 && n != 0)
		return (dest);
	pdest = (char *)dest;
	psrc = (const char *)src;
	if (dest_in_src((char *)dest, (const char *)src, n) == 1)
		while (n-- != 0)
			pdest[n] = psrc[n];
	else
	{
		while (i < n)
		{
			pdest[i] = psrc[i];
			i++;
		}
	}
	return (pdest);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// int	check;

// check = 0;
// char y[] = {65, 66, 67, 68, 69, 0, 45};
// char x[] = { 0,  0,  0,  0,  0,  0, 0};

// if (ft_memmove(y, x, 7) == y)
// 	check = 1;
// 	printf("%d \n", check);
// 	printf("memcmp %d \n", memcmp(x, y, 7));
// return (0);
// }

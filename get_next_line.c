/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:11:31 by wweisser          #+#    #+#             */
/*   Updated: 2022/07/11 15:39:50 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// #include <fcntl.h>

int	fill_lst(t_list **head, char *buf, int sw)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (i < sw)
	{
		ctol(buf[i], head);
		if (buf[i] == '\n')
			ret = 1;
		i++;
	}
	return (ret);
}

//Takes the head and the filedescriptor, mallocs memory in buffer size.
//Then read fills the buffer, and the buffer fills a list (fill_lst).
//If the buffer contains \n "ret" = 1 and the filling of the list stops.
int	gnl1(int fd, t_list **head)
{
	int		sw;
	char	*buf;
	int		ret;

	ret = -1;
	buf = NULL;
	buf = (char *) gnl_calloc(sizeof(char) * BUFFER_SIZE);
	if (buf == NULL)
		return (-1);
	sw = 1;
	while (1)
	{
		sw = read(fd, buf, BUFFER_SIZE);
		if (sw == (-1))
		{
			free (buf);
			return (-1);
		}
		ret = fill_lst(head, buf, sw);
		if (ret == 1 || sw < BUFFER_SIZE)
			break ;
	}
	free (buf);
	return (sw);
}

//Takes the input in form of the file descriptor.
//It creates a head node as the first list element and a pointer,
//that is returned containing the line.
char	*get_next_line(int fd)
{
	static t_list	*head;
	char			*pointer;
	int				sw;

	sw = 0;
	pointer = NULL;
	sw = gnl1(fd, &head);
	if (sw == -1 || head == NULL)
		return (NULL);
	pointer = ltos(&head);
	freelst(&head, '\n');
	return (pointer);
}

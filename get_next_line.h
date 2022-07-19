/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 09:50:31 by wweisser          #+#    #+#             */
/*   Updated: 2022/07/19 15:24:22 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifdef BUFFER_SIZE
# else
#  define BUFFER_SIZE 5100
# endif
# include <unistd.h>
# include <stdlib.h>

struct s_list
{
	char			content;
	struct s_list	*next;
};
typedef struct s_list	t_list;
int						gnl1(int fd, t_list **head);
int						iterlst(t_list **head, char del);
char					*gnl_calloc(size_t size);
char					*ltos(t_list **head);
char					*get_next_line(int fd);
void					ctol(char letter, t_list **head);
void					freelst(t_list **head, char del);
#endif

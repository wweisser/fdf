/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:12:44 by wweisser          #+#    #+#             */
/*   Updated: 2022/07/11 15:53:56 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// allocates memory and fills it with nullchars
char	*gnl_calloc(size_t size)
{
	char	*pointer;

	pointer = NULL;
	pointer = (char *)malloc(size * sizeof(char));
	if (pointer == NULL)
		return (NULL);
	while (size-- > 0)
		pointer[size] = 0;
	return (pointer);
}

// iterates to the char dst, returns the number of passed nodes.
int	iterlst(t_list **head, char del)
{
	int		i;
	t_list	**temp;

	i = 0;
	temp = head;
	if (head == NULL)
		return (-1);
	while (*temp)
	{
		i++;
		if ((*temp)->content == del || (*temp)->next == NULL)
			return (i);
		temp = &(*temp)->next;
	}
	return (-1);
}

// frees the list up unitl the char 'del'. Then also frees the del-node.
void	freelst(t_list **head, char del)
{
	t_list	*temp;

	temp = *head;
	while (*head)
	{
		temp = *head;
		if ((temp)->content == del)
		{
			*head = (*head)->next;
			free (temp);
			return ;
		}
		*head = (*head)->next;
		free(temp);
	}
}

// Puts a char to a node, then appends the node to the end of a list (head)
void	ctol(char letter, t_list **head)
{
	t_list	**temp;
	t_list	*new;

	new = NULL;
	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return ;
	new->content = letter;
	new->next = NULL;
	if (head == NULL)
		*head = new;
	else
	{
		temp = head;
		while (*temp)
			temp = &(*temp)->next;
		new->next = *temp;
		*temp = new;
	}
}

// Puts a list to a string, counts to \n by applying iterlst,
// then callocs memory and copys to the memory up until \n.
char	*ltos(t_list **head)
{
	int		i;
	char	*pointer;
	t_list	**temp;

	pointer = NULL;
	if (head != NULL || (*head)->content != 0)
	{
		i = iterlst(head, '\n');
		pointer = gnl_calloc(i + 1);
		if (pointer == NULL)
			return (NULL);
		i = 0;
		temp = head;
		while (*temp != NULL)
		{
			pointer[i] = (*temp)->content;
			i++;
			if ((*temp)->content == '\n')
				break ;
			temp = &(*temp)->next;
		}
		pointer[i] = '\0';
	}
	return (pointer);
}

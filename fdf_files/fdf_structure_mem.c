/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_structure_mem.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:27:13 by wendelin          #+#    #+#             */
/*   Updated: 2022/08/11 05:26:20 by wweisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// appends a node containing a trigon at the end of a list of trigons
// ADDTRIGON UND NEW TRIGON MÜSSEN GETRENNT WERDEN
void	addtrigon(t_trigon **head, t_trigon *new)
{
	if (new == NULL)
		return ;
	if (*head == NULL)
	{
		*head = new;
		new->next = NULL;
	}
	else
	{
		new->next = *head;
		*head = new;
	}
}

t_trigon	*free_lst(t_trigon **head)
{
	t_trigon	*temp;

	if (*head != NULL)
	{
		temp = *head;
		while (*head != NULL)
		{
			*head = (*head)->next;
			free ((void *)temp);
			temp = *head;
		}
	}
	return (*head);
}

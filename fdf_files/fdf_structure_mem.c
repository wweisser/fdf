/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_structure_mem.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweisser <wweisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:27:13 by wendelin          #+#    #+#             */
/*   Updated: 2022/08/08 20:30:36 by wweisser         ###   ########.fr       */
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
		new->next = NULL;
		*head = new;
	}
	else
	{
		new->next = *head;
		*head = new;
	}
}

void	free_lst(t_trigon **head)
{
	t_trigon	*temp;

	temp = *head;
	if (*head != NULL)
	{
		while (*head)
		{
			temp = *head;
			*head = (*head)->next;
			free(temp);
		}
		head = NULL;
	}
}

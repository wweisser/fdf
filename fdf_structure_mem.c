/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_structure_mem.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendelin <wendelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:27:13 by wendelin          #+#    #+#             */
/*   Updated: 2022/08/06 14:28:08 by wendelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// appends a node containing a trigon at the end of a list of trigons
// ADDTRIGON UND NEW TRIGON MÜSSEN GETRENNT WERDEN
void	addtrigon(trigon **head, trigon *new)
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

void	free_lst(trigon **head)
{
	trigon *temp;

	temp = *head;
	if (*head != NULL)
	{
		while(*head)
		{
			temp = *head;
			*head = (*head)->next;
			free(temp);
		}
		head = NULL;
	}
}

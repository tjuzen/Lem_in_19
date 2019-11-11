/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremoveif.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adefonta <adefonta@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 17:18:05 by adefonta          #+#    #+#             */
/*   Updated: 2019/11/11 16:22:02 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstremoveif(t_list **alst, void *data_ref, int (*cmp)())
{
	t_list *current;
	t_list *prev;

	if (alst == NULL)
		return ;
	current = *alst;
	while (current != NULL)
	{
		if (cmp(current->content, data_ref) == 0)
		{
			if (current == *alst)
			{
				*alst = current->next;
				free(current);
				current = *alst;
				continue ;
			}
			else
				prev->next = current->next;
			free(current);
			current = prev;
		}
		prev = current;
		current = current->next;
	}
}

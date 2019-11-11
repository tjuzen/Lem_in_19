/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adefonta <adefonta@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 17:18:28 by adefonta          #+#    #+#             */
/*   Updated: 2019/11/11 16:21:59 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstpushback(t_list **alst, const void *content, size_t content_size)
{
	t_list *last;

	last = *alst;
	if (last == NULL)
	{
		*alst = ft_lstnew(content, content_size);
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = ft_lstnew(content, content_size);
}

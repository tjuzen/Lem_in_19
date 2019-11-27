/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuarez- <bsuarez-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 11:07:02 by bsuarez-          #+#    #+#             */
/*   Updated: 2019/11/26 13:50:43 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int 	bellwhile_ford(t_linkstab *link, t_lemin *arg)
{
	int did_change;

	did_change = 0;
	while (link->next)
	{
		if (link->isactive == 1)
		{
			// printf("Je teste %s (%i) %s (%i)\n", link->rooma->room, link->rooma->weight, link->roomb->room, link->roomb->weight);
			if (link->rooma->weight != INFINITE
				&& link->rooma->weight + link->weight < link->roomb->weight
				&& link->roomb != arg->start && link->isactive == 1)
			{
				printf(" %s%c est le parent de %s%c\n", link->rooma->room, link->rooma->type, link->roomb->room, link->roomb->type);
				link->roomb->weight = link->weight + link->rooma->weight;
				link->roomb->parent = link->rooma;
				// link->rooma->child = link->roomb;
				did_change = 1;
				// printf("%s est le parent de %s\n", link->roomb->parent->room, link->roomb->room);
			}
		}
		link = link->next;
	}
	return (did_change == 0) ? 666 : 1;
}

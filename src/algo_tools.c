/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuarez- <bsuarez-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 11:07:02 by bsuarez-          #+#    #+#             */
/*   Updated: 2019/11/14 15:00:25 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void 	init_room_weight(t_data_map *map, t_lemin *arg, t_linkstab *links)
{
	t_node *a;
	t_node *b;


	while (links->next)
	{
		a = lookup(map, links->rooma->key, links->rooma->room);
		b = lookup(map, links->roomb->key, links->roomb->room);
		if (links->directed == 1)
		{
			if ((a != arg->start && a->weight != INFINITE)
				|| (b != arg->start && b->weight != INFINITE))
			{
				a->weight = INFINITE;
				b->weight = INFINITE;
			}
		}
		links = links->next;
	}
	arg->start->weight = 0;
}

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
				link->roomb->weight = link->weight + link->rooma->weight;
				link->roomb->parent = link->rooma;
				link->rooma->child = link->roomb;
				did_change = 1;
				// printf("%s est le parent de %s\n", link->roomb->parent->room, link->roomb->room);
			}
		}
		link = link->next;
	}
	if (did_change == 0)
		return (666);
	return (1);
}

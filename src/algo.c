/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:51:04 by tjuzen            #+#    #+#             */
/*   Updated: 2019/10/24 22:39:51 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void add_first_turn(t_data_map *map, t_lemin *arg)
{
	t_node *tmp;

	tmp = lookup(map, hashCode(arg->first), arg->first);
	while (tmp->link)
	{
		tmp->weight = 1;
		tmp->link = tmp->link->next;
	}
}

int bellman_peugeot(t_data_map *map, t_lemin *arg)
{
	t_linkstab *link;
	t_linkstab *linkorigine;

	link = map->links;
	linkorigine = map->links;
	while (link->next)
	{
		printf("Mon lien = %s %s\n", link->in->room, link->out->room);
		link = link->next;
	}
	printf("Mon totalinks = %lu\n\n", arg->totalinks);


	int count = arg->totalinks;
	int countrooms = arg->totalrooms;
	link = map->links;
	while (countrooms - 1 > 0)
	{
		count = arg->totalinks;
		while (link->next)
		{
			printf("in avant %d out avant %d link avant %d\n", link->in->weight, link->out->weight, link->weight);
			//
			if (link->in->weight + link->weight < link->out->weight)
				link->out->weight = link->weight;
			printf("in apres %d out apres %d link apres %d\n\n", link->in->weight, link->out->weight, link->weight);

			link = link->next;
		}
		countrooms--;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:51:04 by tjuzen            #+#    #+#             */
/*   Updated: 2019/10/25 16:41:56 by bsuarez-         ###   ########.fr       */
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
	int			one_room;
	int			two_room;

	link = map->links;
	printf("Mon totalinks = %lu\n\n", arg->totalinks);
	int countrooms = arg->totalrooms;
	while (countrooms - 1 > 0)
	{
		link = map->links;
		while (link->next)
		{
			one_room = map->list[hashCode(link->in->room) % map->size]->weight;
			two_room = map->list[hashCode(link->out->room) % map->size]->weight;
			// printf("________room nb: %s |%010d| room nb: %s |%010d|\n", link->in->room, one_room, link->out->room, two_room);
			// printf("________link_wei |%d|\n", link->weight);
			if (one_room != INT_MAX - 10 && one_room + link->weight < two_room)
				map->list[hashCode(link->out->room) % map->size]->weight = link->weight + one_room;
			printf("________room nb: %s |%010d| room nb: %s |%010d|\n", link->in->room, map->list[hashCode(link->in->room) % map->size]->weight, link->out->room, map->list[hashCode(link->out->room) % map->size]->weight);
			// printf("________link_wei |%d|\n", link->weight);


			link = link->next;
		}
		countrooms--;
	}
	return (1);
}

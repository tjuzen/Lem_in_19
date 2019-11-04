/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:51:04 by tjuzen            #+#    #+#             */
/*   Updated: 2019/11/04 13:17:59 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void 	print_path(t_data_map *map, t_lemin *arg, t_node *parent)
{
	if (parent->parent)
		print_path(map, arg, parent->parent);
	printf(" %s", parent->room);
}

// void add_first_turn(t_data_map *map, t_lemin *arg)
// {
// 	t_node *tmp;
//
// 	tmp = lookup(map, hashCode(arg->first), arg->first);
// 	while (tmp->link)
// 	{
// 		tmp->weight = 1;
// 		tmp->link = tmp->link->next;
// 	}
// }

int bellman_peugeot(t_data_map *map, t_lemin *arg)
{
	t_linkstab	*link;
	t_node		*room_a;
	t_node		*room_b;
	int			countrooms;

	printf("\n");

	countrooms = arg->totalrooms;
	while (--countrooms > 0)
	{
		link = map->links;
		while (link->next)
		{
			room_a = lookup(map, hashCode(link->in->room), link->in->room);
			room_b = lookup(map, hashCode(link->out->room), link->out->room);

			if (room_a->weight != INT_MAX - 10 && room_a->weight + link->weight < room_b->weight)
			{
				room_b->weight = link->weight + room_a->weight;
				room_b->parent = room_a;
			}
			link = link->next;
		}
	}

	printf("My path from src to dest is ");
	print_path(map, arg, arg->end);
	printf("\n");
	return (1);
}

int find_path(t_data_map *map, t_lemin *arg)
{
	bellman_peugeot(map, arg);
	return (1);
}

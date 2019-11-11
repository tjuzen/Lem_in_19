/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:51:04 by tjuzen            #+#    #+#             */
/*   Updated: 2019/11/08 21:13:23 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void modify_path(t_data_map *map, t_lemin *arg)
{
	t_node		*room = arg->end;
	t_linkstab	*link;
	t_linkstab	*findlink;

	link = map->links;
	while (room)
	{
		if (room->parent)
		{
			findlink = lookuplink(map, room, room->parent);
			findlink->weight = -1;
			findlink = lookuplink(map, room->parent, room);
			findlink->isactive = 0;
		}
		room = room->parent;
	}
}

void print_all_links(t_data_map *map, t_lemin *arg, t_linkstab *tmp)
{
	printf("\n");
	while (tmp->next)
	{
		printf("|%s-%s weight %3i|\n", tmp->rooma->room, tmp->roomb->room, tmp->weight);
		tmp = tmp->next;
	}
}

void 	print_path(t_data_map *map, t_lemin *arg, t_node *room)
{
	if (room->parent)
		print_path(map, arg, room->parent);
	if (room->status == 'I')
		printf("\n\nPATH IS OK\n");
	printf(" |%s| ", room->room);

}
//
// t_linkstab	*add_opti(t_node *room_a, t_node *room_b, t_linkstab *tab)
// {
// 	t_linkstab *test = room_b->from;
// 	if (!(test))
// 		return (NULL);
// 	if (tab == NULL)
// 		tab = test;
// 	else
// 	{
// 		test->nextfrom = tab;
// 		tab = test;
// 	}
// 	return (test);
// }

int bellman_peugeot(t_data_map *map, t_lemin *arg)
{
	t_linkstab	*link;
	int			countrooms;

	countrooms = arg->totalrooms;
	while (--countrooms > 0)
	{
		link = map->links;
		while (link->next)
		{
			if (link->rooma->weight != INT_MAX - 10 && link->rooma->weight + link->weight < link->roomb->weight)
			{
				link->roomb->weight = link->weight + link->rooma->weight;
				link->roomb->parent = link->rooma;
				// link->in->child = link->out;
				// if (link->out->from->out != link->in)
				// 	opti = add_opti(link->in, link->out, opti);
			}
			link = link->next;
		}
	}
	return (1);
}

int find_path(t_data_map *map, t_lemin *arg)
{
	bellman_peugeot(map, arg);
	print_path(map, arg, arg->end);
	printf("\n");
	modify_path(map, arg);

	// print_all_links(map, arg, map->links);
	return (1);
}

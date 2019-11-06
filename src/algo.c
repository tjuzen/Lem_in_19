/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:51:04 by tjuzen            #+#    #+#             */
/*   Updated: 2019/11/06 14:55:55 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void modify_path(t_data_map *map, t_lemin *arg)
{
	t_node *room = arg->end;
	t_linkstab *link;

	link = room->to;
	while (link)
	{
		if (link->out->parent == link->in)
		{
			link->weight = -1;
			link = link->in->to;
		}
		else
			link = link->nexto;
	}
}

void print_all_links(t_data_map *map, t_lemin *arg, t_linkstab *tmp)
{
	printf("\n");
	while (tmp->next)
	{
		printf("|%s-%s weight %3i|\n", tmp->in->room, tmp->out->room, tmp->weight);
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

t_linkstab	*add_opti(t_node *room_a, t_node *room_b, t_linkstab *tab)
{
	t_linkstab *test = room_b->from;
	if (!(test))
		return (NULL);
	if (tab == NULL)
		tab = test;
	else
	{
		test->nextfrom = tab;
		tab = test;
	}
	return (test);
}

int bellman_peugeot(t_data_map *map, t_lemin *arg)
{
	t_linkstab	*link;
	int			countrooms;
	t_linkstab *opti;
	t_linkstab *tmp;

	printf("\n");
	countrooms = arg->totalrooms;
	opti = arg->start->from;
	link = opti;
	while (--countrooms > 0)
	{
		// printf("---\n");
		while (link->next)
		{
			if (link->in->weight != INT_MAX - 10 && link->in->weight + link->weight < link->out->weight)
			{
				link->out->weight = link->weight + link->in->weight;
				link->out->parent = link->in;
				link->in->child = link->out;
				// if (link->out->from->out != link->in)
				// 	opti = add_opti(link->in, link->out, opti);
			}
			link = link->next;
		}
		link = map->links;
		// link = opti;
		// opti = NULL;
	}

	return (1);
}

int find_path(t_data_map *map, t_lemin *arg)
{
	t_linkstab *prout = map->links;
	print_all_links(map, arg, prout);
	prout = map->links;
	bellman_peugeot(map, arg);

	print_path(map, arg, arg->end);
	printf("\n");
	modify_path(map, arg);
	print_all_links(map, arg, map->links);
	return (1);
}

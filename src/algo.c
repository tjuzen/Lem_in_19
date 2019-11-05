/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:51:04 by tjuzen            #+#    #+#             */
/*   Updated: 2019/11/05 18:48:39 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

// void modify_path(t_data_map *map, t_lemin *arg)
// {
// 	t_node *room = arg->start;
// 	t_linkstab *link;
//
// 	link = room->from;
// 	while (link)
// 	{
// 		// printf("Coucou theo %i\n", link->weight);
// 		if (link->out->parent == link->in)
// 		{
// 			link->weight = -1;
// 		}
// 		link = link->nextfrom;
// 	}
// }

void modify_path(t_data_map *map, t_lemin *arg)
{
	t_node *room = arg->end;
	t_linkstab *link;

	link = room->to;
	while (link)
	{
		// printf("Coucou theo %i\n", link->weight);
		if (link->out->parent == link->in)
		{
			link->weight = -1;
			link = link->in->to;
		}
		else
			link = link->nexto;
	}
}

void print_all_links(t_data_map *map, t_lemin *arg)
{
	t_linkstab *tmp;
	//
	// tmp = map->links;
	// while (tmp->next)
	// {
	// 	if (tmp->in->child && tmp->in->child == tmp->out)
	// 	{
	// 		printf("[%s] {%s}\n", tmp->in->child->room, tmp->out->parent->room);
	// 		tmp->weight = -1;
	// 	}
	// 	tmp = tmp->next;
	// }
	tmp = map->links;
	while (tmp->next)
	{
		printf(" %s %s  %i\n", tmp->in->room, tmp->out->room, tmp->weight);

		tmp = tmp->next;
	}
}




void 	print_path(t_data_map *map, t_lemin *arg, t_node *room)
{
	if (room->parent)
		print_path(map, arg, room->parent);
	if (room->status == 'I')
		printf("\nPATH IS OK\n");
	printf(" |%s| ", room->room);
	// room-> = -1;
	// printf(" |%i| ", room->in->from->weight);

}

t_linkstab	*add_opti(t_node *room_a, t_node *room_b, t_linkstab *tab)
{
	t_linkstab	*newtab;

	if (!(newtab = ft_memalloc(sizeof(t_linkstab))))
	{
		// ft_freetab_str(splitted);
		return (NULL);
	}

	newtab->weight = 1;
	newtab->in = room_a;
	newtab->out = room_b;

	if (tab == NULL)
		tab = newtab;
	else
	{
		newtab->next = tab;
		tab = newtab;
	}
	return (tab);
}

int bellman_peugeot(t_data_map *map, t_lemin *arg)
{
	t_linkstab	*link;
	int			countrooms;

	printf("\n");
	countrooms = arg->totalrooms;
	while (--countrooms > 0)
	{
		// boucler avec les links room_a_modif->room_b_original
		link = map->links;
		while (link->next)
		{
			if (link->in->weight != INT_MAX - 10 && link->in->weight + link->weight < link->out->weight)
			{
				link->out->weight = link->weight + link->in->weight;
				// link->out->isactive
				link->out->parent = link->in;
				link->in->child = link->out;
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
	// print_all_links(map, arg);
	return (1);
}

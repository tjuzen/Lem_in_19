/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:51:04 by tjuzen            #+#    #+#             */
/*   Updated: 2019/11/04 20:07:15 by tjuzen           ###   ########.fr       */
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

// int bellman_peugeot(t_data_map *map, t_lemin *arg)
// {
// 	t_linkstab	*link;
// 	t_node		*room_a;
// 	t_node		*room_b;
// 	int			countrooms;
// 	int 		previous_weight;
//
// 	printf("\n");
//
// 	countrooms = arg->totalrooms;
// 	while (--countrooms > 0)
// 	{
// 		link = map->links;
// 		// boucler avec les links room_a_modif->room_b_original
// 		while (link->next)
// 		{
// 			room_a = lookup(map, hashCode(link->in->room), link->in->room);
// 			// printf("A : %s && %i\n", room_a->room, room_a->isactive);
// 			// if (room_a->isactive > -1)
// 			// {
// 				// printf("je rentre\n");
// 				room_a->isactive -= 1;
// 				room_b = lookup(map, hashCode(link->out->room), link->out->room);
// 				if (room_a->weight != INT_MAX - 10 && room_a->weight + link->weight < room_b->weight)
// 				{
// 					room_b->weight = link->weight + room_a->weight;
// 					room_b->isactive += 1;
// 					room_b->parent = room_a;
// 					// printf("B : %s && %i\n", room_b->room, room_b->isactive);
// 				}
// 			// }
// 			link = link->next;
// 		}
// 	}
//
// 	printf("My path from src to dest is ");
// 	print_path(map, arg, arg->end);
// 	printf("\n");
//
// 	return (1);
// }

// Qyy5 Kc_6 Zna3 Dcc7 Pz_4 Igl7 Nyy3 Tiq8 M_c6 Gzh2 K_m8 Guc4 Aj_9 Jug4 Wuw6 Ft_7 Xij8


int bellman_peugeot(t_data_map *map, t_lemin *arg)
{
	t_linkstab	*link;
	t_linkstab	*newlink = NULL;

	t_node		*room_a;
	t_node		*room_b;
	int			countrooms;
	int 		previous_weight;

	printf("\n");

	countrooms = arg->totalrooms;
	link = map->links;

	while (--countrooms > 0)
	{
		// boucler avec les links room_a_modif->room_b_original
		link = map->links;

		while (link->next)
		{
			room_a = lookup(map, hashCode(link->in->room), link->in->room);
			// if (room_a->isactive > -1)
			// {
				// printf("je rentre\n");
				// room_a->isactive -= 1;
				room_b = lookup(map, hashCode(link->out->room), link->out->room);
				printf("%s & %s\n", room_a->room, room_b->room);

				if (room_a->weight != INT_MAX - 10 && room_a->weight + link->weight < room_b->weight)
				{
					room_b->weight = link->weight + room_a->weight;
					// room_b->isactive += 1;
					room_b->parent = room_a;
					newlink = add_opti(room_b, room_a, newlink);

				}
			// }
			link = link->next;
		}
		printf("________________________\n\n");
		link = newlink;
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

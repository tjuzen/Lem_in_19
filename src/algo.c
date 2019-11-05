/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:51:04 by tjuzen            #+#    #+#             */
/*   Updated: 2019/11/05 13:06:38 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void 	print_path(t_data_map *map, t_lemin *arg, t_node *parent)
{
	if (parent->parent)
		print_path(map, arg, parent->parent);
	printf(" |%s| ", parent->room);
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
			}
			link = link->next;
		}
	}

	return (1);
}

int find_path(t_data_map *map, t_lemin *arg)
{
	bellman_peugeot(map, arg);
	// printf("My path from src to dest is ");
	print_path(map, arg, arg->end);
	// printf("\n");
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuarez- <bsuarez-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 11:30:57 by bsuarez-          #+#    #+#             */
/*   Updated: 2019/12/17 17:29:41 by bsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_node	*lookup(t_data_map *map, unsigned long key, char *room)
{
	t_node *tmp;

	tmp = map->list[key % map->size];
	while (tmp)
	{
		// printf("Mon node %s\n", tmp->room);

		if (tmp->key == key && ft_strcmp(room, tmp->room) == 0)
				return (tmp);
		tmp = tmp->hash_next;
	}
	return (NULL);
}

// t_linkstab *lookuplinknode(t_node *a, t_node *b)
// {
// 	t_linkstab *find;
//
// 	find = a->to;
// 	while (find->nexto)
// 	{
// 		if (find->rooma == a && find->roomb == b)
// 			return (find);
// 		find = find->nexto;
// 	}
// 	return (NULL);
// }

t_linkstab *lookuplink(t_data_map *map, t_node *a, t_node *b)
{
	t_linkstab *find;

	find = map->links;
	if (!a || !b)
		return (NULL);
	while (find->next)
	{
		// printf("[%s]-[%s]\n", find->rooma->room, find->roomb->room);
		// print_colors(find);
		// printf("		[%s]-[%s]\n", a->room, b->room);
		if (find->rooma && find->roomb && a && b)
			if (find->rooma->key == a->key && find->roomb->key == b->key)
				return (find);
		find = find->next;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:51:04 by tjuzen            #+#    #+#             */
/*   Updated: 2019/12/19 15:55:22 by bsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

// Augmente de 1 la valeur de selected pour A-B (== tmp) et B-A (== reversed)

int 	add_found_path(t_data_map *map, t_lemin *arg, t_node *room)
{
	t_linkstab *tmp;

	while (room)
	{
		tmp = lookuplink(map, room->parent, room);
		if (tmp)
		{
			tmp->selected++;
			if (tmp->reversed)
				tmp->reversed->selected++;
		}
		room = room->parent;
	}
	return (1);
}


int bellman_peugeot(t_data_map **map, t_lemin *arg)
{
	t_linkstab	*link;
	int			countrooms;

	countrooms = arg->totalrooms;
	link = (*map)->links;
	while (--countrooms > 0 && link)
	{
		link = (*map)->links;
		if (bellwhile_ford(link, arg) == 666)
			break;
	}
	return (1);
}

void out_infos(t_data_map *map, t_lemin *arg, t_linkstab *link, t_node *out)
{
	link->roomb->duplicated = 1;
	out->duplicated = 1;
	out->key = hashCode(out->room);
	out->paths = NULL;
	out->status = 'X';
	out->type = 'O';
	out->in = link->roomb;
	link->roomb->out = out;
	if (map->list[out->key % map->size] == NULL)
		map->list[out->key % map->size] = out;
	else
	{
		out->hash_next = map->list[out->key % map->size];
		map->list[out->key % map->size] = out;
	}
}

int intern_infos(t_data_map *map, t_lemin *arg, t_linkstab *link, t_node *out)
{
	t_linkstab *intern;

	if (!(intern = ft_memalloc(sizeof(t_linkstab))))
	{
		arg->malloc_error = 1;
		ft_strdel(&out->room);
		free(out);
		return (-1);
	}
	intern->rooma = link->roomb;
	intern->roomb = out;
	intern->isactive = 1;
	intern->selected = 1;
	intern->rooma->in = intern->roomb;
	intern->roomb->out = intern->rooma;
	intern->rooma->type = 'I';
	intern->roomb->parent = intern->rooma;
	add_it(arg, &map, intern);
	return (1);
}

int new_duplicate(t_data_map *map, t_lemin *arg, t_linkstab *link)
{
	t_node *out;

	if (!(out = ft_memalloc(sizeof(t_node))))
	{
		arg->malloc_error = 1;
		return (-1);
	}
	if (!(out->room = ft_strdup(link->roomb->room)))
	{
		arg->malloc_error = 1;
		free(out);
		return (-1);
	}
	out_infos(map, arg, link, out);
	if (intern_infos(map, arg, link, out) == -1)
		return (-1);
	link->rooma->parent = out;
	return (1);
}

void        update_links(t_data_map *map, t_lemin *arg, t_linkstab *tmp)
{
	t_linkstab *link;

	link = tmp;
	while (link->next)
	{
        if (link->rooma->type == 'I' && link->rooma->out != link->roomb)
				link->rooma = link->rooma->out;
		link = link->next;
	}
}

int duplicate_nodes(t_data_map *map, t_lemin *arg, t_node *room)
{
	t_linkstab *tmp;

	while (room)
	{
		tmp = lookuplink(map, room, room->parent);
		if (tmp)
		{
			if (tmp->roomb->status == 'X' && tmp->roomb->duplicated != 1)
				if (new_duplicate(map, arg, tmp) == -1)
					return (-1);
		}
		room = room->parent;
	}
	update_links(map, arg, map->links);
	return (1);
}

void inverse_links(t_data_map *map, t_lemin *arg, t_node *room)
{
	t_linkstab	*tmp;
	t_node		*tmproom;

	while (room)
	{
		tmp = lookuplink(map, room->parent, room);
		if (tmp)
		{
			tmproom = tmp->rooma;
			tmp->rooma = tmp->roomb;
			tmp->roomb = tmproom;
			tmp->weight = -1;
			tmp->inversed = 1;
		}
		room = room->parent;
	}
}

void check_inversed(t_data_map *map, t_lemin *arg, t_linkstab *tmp)
{
	while (tmp->next)
	{
		if (tmp->selected > 1)
			tmp->selected = 0;
		if (tmp->reversed && tmp->reversed->selected > 1)
			tmp->reversed->selected = 0;
		tmp = tmp->next;
	}
}

/*

1: Find the shortest path P1 from node s to node t
2: for i = 2,..., k
3: For node-disjoint paths, split the intermediate nodes of all Px where x < i (refer to Figure 3)
4: Replace each link of all Px where x < i with a reverse link of inverted link weight in the original graph
5: Find the shortest path Pi from node s to node t
6: Remove all overlapping links to get i disjoint paths Px where x ≤ i.

*/

int find_path(t_data_map **map, t_lemin *arg)
{
	t_node *tmp;
	int nombredepaths = 1;
	int nbr = 0;

	bellman_peugeot(map, arg);
	if (add_found_path((*map), arg, arg->end) == -1)
		return (-1);
	max_path(arg, map);
	print_all_links((*map), arg, (*map)->links);

	while (nombredepaths--)
	{
		printf("\n\n\n                                   CA TOURNE \n\n\n");
		printf("je dup \n");
		if (duplicate_nodes((*map), arg, arg->end) == -1)
			return (-1);
			print_all_links((*map), arg, (*map)->links);

		printf("j'inverse \n");
		inverse_links((*map), arg, arg->end);
		print_all_links((*map), arg, (*map)->links);

		printf("je  reset\n");
		reset(map, arg, (*map)->links);
		print_all_links((*map), arg, (*map)->links);

		printf("je bellman \n");
		bellman_peugeot(map, arg);
		if (add_found_path((*map), arg, arg->end) == -1)
			return (-1);
			print_all_links((*map), arg, (*map)->links);

		printf("je check inversed\n");
	 	check_inversed((*map), arg, (*map)->links);
		print_all_links((*map), arg, (*map)->links);

	}
	if ((nbr = find_nbr_way(map, arg, (*map)->links)) == -1)
		return (-1);
	print_way(map, arg, nbr);
	return (1);
}

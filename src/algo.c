/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:51:04 by tjuzen            #+#    #+#             */
/*   Updated: 2019/11/11 21:59:48 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
  B --- C
 /       \
A -- E -- D -- H
      \      /
	  F --- G
*/

/*

     i o    i o
A -- E-E -- D-D -- H
  -1  0  -1  0  -1

*/
//
// void modify_room(t_node *room, t_data_map *map, t_lemin *arg)
// {
//
// }
//
t_data_map *duplicate(t_node *in, t_data_map *map, t_lemin *arg)
{
	t_node			*out;
	t_linkstab		*newlink;

	if (!(out = ft_memalloc(sizeof(t_node))))
	{
		arg->malloc_error = 1;
		return (NULL);
	}
	if (!(out->room = ft_strdup(in->room)))
	{
		arg->malloc_error = 1;
		free(out);
		return (NULL);
	}
	if (!(newlink = ft_memalloc(sizeof(t_linkstab))))
	{
		arg->malloc_error = 1;
		return (map);
	}
	out->key = hashCode(out->room);
	out->status = 'X';
	out->isactive = 0;  // ?
	out->parent = NULL;
	out->child = NULL;
	out->to = in->to; // ajouter tous les to sauf parent
	out->type = 'O';
	if (map->list[out->key % map->size] == NULL)
		map->list[out->key % map->size] = out;
	else
	{
		out->hash_next = map->list[out->key % map->size];
		map->list[out->key % map->size] = out;
	}
	arg->totalrooms++;

	in->to = NULL;
	// in->to = in->parent;
	in->to = lookuplink(map, in, in->parent);
	newlink->rooma = out;
	newlink->roomb = in;
	newlink->weight = 0;
	newlink->directed = 2;
	newlink->isactive = 1;
	map->links = add_it(map, newlink);
	printf("%s ", in->room);
printf("in  :");
	while (in->to)
	{
		if (in->to->isactive)
		printf("  %s  ", in->to->roomb->room);
		in->to = in->to->nexto;
	}
printf("\n");
printf("%s ", in->room);
printf("out :");
	while (out->to)
	{
		if (out->to->isactive)
		printf("  %s  ", out->to->roomb->room);
		out->to = out->to->nexto;
	}
printf("\n");
	return (map);
}

// void modify_path(t_data_map *map, t_lemin *arg)
// {
// 	t_node		*room = arg->end;
// 	t_linkstab	*link;
// 	t_linkstab	*findlink;
//
// 	link = map->links;
// 	while (room)
// 	{
// 		if (room->parent)
// 		{
// 			findlink = lookuplink(map, room, room->parent);
// 			findlink->weight = -1;
// 			if (room != arg->start && room != arg->end)
// 				map = duplicate(room, map, arg);
// 			findlink = lookuplink(map, room->parent, room);
// 			findlink->isactive = 0;
// 		}
// 		room = room->parent;
// 	}
// }

void modify_path(t_data_map *map, t_lemin *arg)
{
	t_node		*room = arg->start;
	t_linkstab	*link;
	t_linkstab	*findlink;

	link = map->links;
	while (room)
	{
		if (room->path)
		{
			findlink = lookuplink(map, room->path, room);
			findlink->weight = -1;
			if (room != arg->start && room != arg->end)
				map = duplicate(room, map, arg);
			findlink = lookuplink(map, room, room->path);
			findlink->isactive = 0;
		}
		room = room->path;
	}
}

void print_all_links(t_data_map *map, t_lemin *arg, t_linkstab *tmp)
{
	printf("\n");
	while (tmp->next)
	{
		printf("|%s-%s weight %3i active %3i|\n", tmp->rooma->room, tmp->roomb->room, tmp->weight, tmp->isactive);
		tmp = tmp->next;
	}
}

void 	print_path(t_data_map *map, t_lemin *arg, t_node *room)
{
	if (room->parent)
	{
		room->parent->path = room;
		print_path(map, arg, room->parent);
	}
	if (room->status == 'I')
		printf("\n\nPATH IS OK\n");
	printf(" |%s| ", room->room);
}

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
				link->rooma->child = link->roomb;
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

	print_all_links(map, arg, map->links);
	return (1);
}

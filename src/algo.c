/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:51:04 by tjuzen            #+#    #+#             */
/*   Updated: 2019/11/13 11:09:26 by bsuarez-         ###   ########.fr       */
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
int		switch_links(t_data_map *map, t_lemin *arg, t_linkstab *tmp, char *io)
{
	t_linkstab 	*link;
	char *start;

	link = map->links;
	if (!(start = ft_strjoin(io, "-")))
		return (-1);
	while (link->next)
	{
		if (link->rooma->room == tmp->rooma->room)
		{
			if (!(io = ft_strdup(start)))
				return (-1);
			if (!(io = ft_strjoin(io, link->roomb->room)))
				return (-1);
			// printf ("|%s| - room - |%s|\n", link->rooma->room, link->roomb->room);
			// if (check_in_out(map, arg, ))
			map = add_link(map, io, arg, 0);
		}
		link = link->next;
	}
	return (1);
}

int 		multiply_room(t_data_map *map, t_lemin *arg, t_node *room)
{
	char	*in;
	char	*out;
	char	*newroom;

	if (!(in = ft_strdup("#i_")) || !(out = ft_strdup("#o_")))
		return (-1);
	if (!(newroom = ft_strjoin(in, room->room)))
		return (-1);
	map = add_room(map, newroom, 'X', arg);
	if (!(switch_links(map, arg, room->to, newroom)))
		return (-1);
	free (newroom);
	if (!(newroom = ft_strjoin(out, room->room)))
		return (-1);
	map = add_room(map, newroom, 'X', arg);
	switch_links(map, arg, room->to, newroom);
	free (newroom);
	free (in);
	free (out);
	return (1);
}

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
	out->type = 'I';
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
		// if (in->to->isactive)
		printf("  %s  ", in->to->roomb->room);
		in->to = in->to->nexto;
	}
printf("\n");
printf("%s ", in->room);
printf("out :");
	while (out->to)
	{
		// if (out->to->isactive)
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

int modify_path(t_data_map *map, t_lemin *arg)
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
			if (room->path->status == 'X')
			{
				if (multiply_room(map, arg, room->path) == -1)
					return (-1);
				// switch_links(map, arg, room->path->to);
			}
			findlink = lookuplink(map, room, room->path);
			findlink->isactive = 0;
		}
		room = room->path;
	}
	return (1);
}

void print_all_links(t_data_map *map, t_lemin *arg, t_linkstab *tmp)
{
	printf("\n");
	while (tmp->next)
	{
		printf("|%s-%s weight %3i active %3i| |type %c - %c|\n", tmp->rooma->room, tmp->roomb->room, tmp->weight, tmp->isactive, tmp->rooma->type, tmp->roomb->type);
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
	if (modify_path(map, arg) == -1)
		return (-1);
	// switch_link(map, arg, map->links);

	// print_all_links(map, arg, map->links);
	return (1);
}

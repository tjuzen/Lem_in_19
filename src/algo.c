/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:51:04 by tjuzen            #+#    #+#             */
/*   Updated: 2019/11/14 15:34:10 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void print_theo(t_data_map *map)
{
	t_node *a = lookup(map, hashCode("a"), "a");


	while (a->to)
	{
		// if (a->to->isactive)
		printf("$$$ %c-%s $$$\n", a->to->roomb->type, a->to->roomb->room);
		a->to = a->to->nexto;
	}
}

void print_all_links(t_data_map *map, t_lemin *arg, t_linkstab *tmp)
{
	printf("\n");
	while (tmp->next)
	{
		printf("%c%2s    ---    %c%2s%5i", tmp->rooma->type, tmp->rooma->room, tmp->roomb->type, tmp->roomb->room, tmp->weight);
		if (tmp->isactive == 1)
			printf(" XXXX");
		printf("\n");
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
	printf("|%s| ", room->room);
}

t_data_map *duplicate(t_node *in, t_node *tmp, t_data_map *map, t_lemin *arg)
{
	t_node			*out;
	t_linkstab		*newlink;

	if (!(out = ft_memalloc(sizeof(t_node))))
	{
		arg->malloc_error = 1;
		return (NULL);
	}
	if (!(out->room = ft_strjoin("#", in->room)))
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
	out->isactive = 1;  // ?
	out->parent = in->parent;
	out->path = in->path;
	out->type = 'O';
	in->type = 'I';
	out->weight = 1;
	in->weight = 1;
t_linkstab *try;

	while (in->to)
	{
		if (in->to->isactive)
		{
			try = lookuplink(map, in, in->to->roomb);
			// printf("Mon link %c%s %c%s\n", try->rooma->type, try->rooma->room, try->roomb->type, try->roomb->room);
			if (try->roomb->path == try->rooma)
			{
				// printf("Je passe \n");
				// printf("Je remplace %s par %s\n", try->rooma->room, try->roomb->room);
				// try->rooma = out;
			}
			else
			{
				try->rooma = out;
			}
			in->to = in->to->nexto;
		}
		else
			in->to = in->to->nexto;

	}
	if (map->list[out->key % map->size] == NULL)
		map->list[out->key % map->size] = out;
	else
	{
		out->hash_next = map->list[out->key % map->size];
		map->list[out->key % map->size] = out;
	}
	arg->totalrooms++;

	newlink->rooma = out;
	newlink->roomb = in;
	// newlink->weight = 0;
	newlink->isactive = 1;
	map->links = add_it(map, newlink);
	try = lookuplink(map, in->path, in);
	try->roomb = out;
	return (map);
}


void duppp(t_data_map *map, t_lemin *arg)
{
	t_node		*room = arg->start;
	t_linkstab	*findlink;

	while (room->path)
	{
		if (room->path->status == 'X')
			duplicate(room->path, room, map, arg);
		room = room->path;
	}
}

int modify_path(t_data_map *map, t_lemin *arg)
{
	t_node		*room = arg->start;
	t_linkstab	*findlink;

	if (!(room->path))
		return (-1);
	while (room->path)
	{
		findlink = lookuplink(map, room->path, room);
		findlink->weight = -1;
		findlink = lookuplink(map, room, room->path);
		findlink->isactive = -1;
		room = room->path;
	}
	return (1);
}



int bellman_peugeot(t_data_map *map, t_lemin *arg)
{
	t_linkstab	*link;
	int			countrooms;

	countrooms = arg->totalrooms;
	while (--countrooms > 0)
	{
		link = map->links;
		// printf("-----------\n");
		if (bellwhile_ford(link, arg) == 666)
			break;
	}
	// link = map->links;
	// while (link->next)
	// {
	// 	if (link->rooma->weight != INFINITE
	// 		&& link->rooma->weight + link->weight < link->roomb->weight)
	// 		printf("negcycle\n");
	// 	link = link->next;
	// }
	return (1);
}


int find_path(t_data_map *map, t_lemin *arg)
{
	int i;

	i = -1;
	bellman_peugeot(map, arg);
	print_path(map, arg, arg->end);

	if (modify_path(map, arg) == -1)
		return (-1);
	duppp(map, arg);
	init_room_weight(map, arg, map->links);
	// print_all_links(map, arg, map->links);
	// print_theo(map);
	bellman_peugeot(map, arg);
	print_path(map, arg, arg->end);

	return (1);
}

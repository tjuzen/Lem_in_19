/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuarez- <bsuarez-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 11:07:02 by bsuarez-          #+#    #+#             */
/*   Updated: 2019/11/15 17:38:45 by bsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_node		*give_name(t_data_map *map, int i, t_lemin *arg)
{
	t_node *tmp;
	char *str;
	char *nbr;

	if (!(nbr = ft_itoa(i)))
		return (NULL);
	if (!(str = ft_strjoin("L-", nbr)))
	{
		free(nbr);
		return (NULL);
	}
	free(nbr);
	map = add_room(map, str, 'P', arg);
	tmp = lookup(map, hashCode(str), str);
	free(str);
	return (tmp);
}

void 	init_room_weight(t_data_map *map, t_lemin *arg, t_linkstab *links)
{
	t_node *a;
	t_node *b;

	while (links->next)
	{
		a = lookup(map, links->rooma->key, links->rooma->room);
		b = lookup(map, links->roomb->key, links->roomb->room);
		if (links->directed == 1)
		{
			if ((a != arg->start && a->weight != INFINITE)
				|| (b != arg->start && b->weight != INFINITE))
			{
				a->weight = INFINITE;
				b->weight = INFINITE;
				a->path = NULL;
				b->path = NULL;
			}
		}
		links = links->next;
	}
	arg->start->weight = 0;
}

int 	bellwhile_ford(t_linkstab *link, t_lemin *arg)
{
	int did_change;

	did_change = 0;
	while (link->next)
	{
		if (link->isactive == 1)
		{
			// printf("Je teste %s (%i) %s (%i)\n", link->rooma->room, link->rooma->weight, link->roomb->room, link->roomb->weight);
			if (link->rooma->weight != INFINITE
				&& link->rooma->weight + link->weight < link->roomb->weight
				&& link->roomb != arg->start && link->isactive == 1)
			{
				link->roomb->weight = link->weight + link->rooma->weight;
				link->roomb->parent = link->rooma;
				link->rooma->child = link->roomb;
				did_change = 1;
				// printf("%s est le parent de %s\n", link->roomb->parent->room, link->roomb->room);
			}
		}
		link = link->next;
	}
	return (did_change == 0) ? 666 : 1;
}

int duplicate(t_node *in, t_node *tmp, t_data_map *map, t_lemin *arg)
{
	t_node			*out;
	t_linkstab		*newlink;
	t_linkstab *try;

	if (!(out = ft_memalloc(sizeof(t_node))))
	{
		arg->malloc_error = 1;
		return (-1);
	}
	if (!(out->room = ft_strjoin("#", in->room)))
	{
		arg->malloc_error = 1;
		free(out);
		return (-1);
	}
	if (!(newlink = ft_memalloc(sizeof(t_linkstab))))
	{
		arg->malloc_error = 1;
		ft_strdel(&out->room);
		free(out);
		return (-1);
	}
	out->key = hashCode(out->room);
	out->status = 'X';
	out->isactive = 1;
	out->parent = in->parent;
	out->path = in->path;
	out->type = 'O';
	out->weight = 1;
	in->type = 'I';
	in->weight = 1;
	while (in->to)
	{
		if (in->to->isactive)
		{
			if (!(try = lookuplink(map, in, in->to->roomb)))
				break ;
			if (try->roomb->path != try->rooma)
				try->rooma = out;
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
	newlink->isactive = 1;
	map->links = add_it(map, newlink);
	if (!(try = lookuplink(map, in->path, in)))
		return (-1);
	try->roomb = out;
	return (1);
}


int duppp(t_data_map *map, t_lemin *arg)
{
	t_node		*room;
	t_linkstab	*findlink;

	room = arg->start;
	while (room->path)
	{
		if (room->path->status == 'X')
			if (duplicate(room->path, room, map, arg) == -1)
				return (-1);
		room = room->path;
	}
	return (1);
}

int modify_path(t_data_map *map, t_lemin *arg)
{
	t_node		*room;
	t_linkstab	*findlink;

	room = arg->start;
	if (!(room->path))
		return (-1);
	while (room->path)
	{
		if (!(findlink = lookuplink(map, room->path, room)))
			return (-1);
		findlink->weight = -1;
		if (!(findlink = lookuplink(map, room, room->path)))
			return (-1);
		findlink->isactive = -1;
		room = room->path;
	}
	return (1);
}

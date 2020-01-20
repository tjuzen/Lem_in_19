/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:08:58 by tjuzen            #+#    #+#             */
/*   Updated: 2020/01/20 16:10:46 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		out_infos(t_data_map *map, t_node *room, t_node *out)
{
	out->duplicated = 1;
	room->duplicated = 1;
	out->key = hashCode(out->room);
	out->paths = NULL;
	out->status = 'X';
	out->type = 'O';
	out->in = room;
	room->out = out;
	room->type = 'I';
	if (map->list[out->key % map->size] == NULL)
		map->list[out->key % map->size] = out;
	else
	{
		out->hash_next = map->list[out->key % map->size];
		map->list[out->key % map->size] = out;
	}
	change_type(room);
}

int		intern_infos(t_data_map *map, t_lemin *arg, t_node *room, t_node *out)
{
	t_linkstab *intern;

	if (!(intern = ft_memalloc(sizeof(t_linkstab))))
	{
		arg->malloc_error = 1;
		ft_strdel(&out->room);
		free(out);
		return (-1);
	}
	intern->rooma = room;
	intern->roomb = out;
	intern->isactive = 1;
	intern->imintern = 1;
	intern->selected = 1;
	intern->roomb->parent = intern->rooma;
	add_it(arg, &map, intern);
	return (1);
}

t_node		*new_duplicate(t_data_map *map, t_lemin *arg, t_node *room)
{
	t_node *out;

	if (!(out = ft_memalloc(sizeof(t_node))))
	{
		arg->malloc_error = 1;
		return (NULL);
	}
	if (!(out->room = ft_strdup(room->room)))
	{
		arg->malloc_error = 1;
		free(out);
		return (NULL);
	}
	room->just_dup = 1;
	out_infos(map, room, out);
	if (intern_infos(map, arg, room, out) == -1)
		return (NULL);
	return (out);
}

void	update_links(t_linkstab *tmp)
{
	t_linkstab *link;

	link = tmp;
	while (link->next)
	{
		if (link->rooma->type == 'I' && link->rooma->out != link->roomb
			&& link->rooma->just_dup == 1 && link->weight != 0)
		{
			link->rooma = link->rooma->out;
			link->rooma->just_dup = 0;
		}
		link = link->next;
	}
}

int		duplicate_nodes(t_data_map *map, t_lemin *arg, t_node *room)
{
	while (room && room != arg->start)
	{
		if (room->parent->duplicated != 1 && room->parent &&
			room->parent != arg->start)
		{
			new_duplicate(map, arg, room->parent);
			room->parent = room->parent->out;
		}
		room = room->parent;
	}
	return (1);
}

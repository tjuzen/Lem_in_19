/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:28:27 by tjuzen            #+#    #+#             */
/*   Updated: 2019/11/14 18:12:21 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
t_linkstab	*add_it(t_data_map *map, t_linkstab *newlink)
{
	if (map->links == NULL)
		map->links = newlink;
	else
	{
		newlink->next = map->links;
		map->links = newlink;
	}
	return (map->links);
}
t_data_map	*add_link(t_data_map *map, char *line, t_lemin *arg, int directed)
{
	char			**splitted;
	t_linkstab		*newlink;
	t_linkstab		*otherlink;
	t_node			*rooma;
	t_node			*roomb;

	if (!(splitted = ft_strsplit(line, '-')))
	{
		arg->malloc_error = 1;
		return (map);
	}
	rooma = lookup(map, hashCode(splitted[0]), splitted[0]);
	if (!(rooma))
	{
		arg->malloc_error = 1;
		ft_freetab_str(splitted);
		return (map);
	}
	roomb = lookup(map, hashCode(splitted[1]), splitted[1]);
	if (!(roomb))
	{
		arg->malloc_error = 1;
		ft_freetab_str(splitted);
		return (map);
	}
	if (!(newlink = ft_memalloc(sizeof(t_linkstab))))
	{
		arg->malloc_error = 1;
		ft_freetab_str(splitted);
		return (map);
	}
	if (directed == 1) // si a<->b
	{
		if (!(otherlink = ft_memalloc(sizeof(t_linkstab))))
		{
			arg->malloc_error = 1;
			ft_freetab_str(splitted);
			return (map);
		}
		newlink->rooma = rooma;
		newlink->roomb = roomb;
		newlink->weight = 1;
		newlink->directed = 2;
		newlink->isactive = 1;
		map->links = add_it(map, newlink);
		if (!(rooma->to))
			rooma->to = newlink;
		else
		{
			newlink->nexto = rooma->to;
			rooma->to = newlink;
		}
		otherlink->rooma = roomb;
		otherlink->roomb = rooma;
		otherlink->weight = 1;
		otherlink->directed = 1;
		otherlink->isactive = 1;
		map->links = add_it(map, otherlink);
		if (!(roomb->to))
			roomb->to = otherlink;
		else
		{
			otherlink->nexto = roomb->to;
			roomb->to = otherlink;
		}
		if (rooma->status == 'I' && roomb->status == 'O')
		{
			arg->foundpath = 1;
			roomb->parent = rooma;
		}
		if (roomb->status == 'I' && rooma->status == 'O')
		{
			arg->foundpath = 1;
			rooma->parent = roomb;
		}
	}
	arg->totalinks++;
	ft_freetab_str(splitted);
	return (map);
}

t_data_map *add_room_info(t_data_map *map, char stat, t_lemin *arg, t_node *new)
{
	new->key = hashCode(new->room);
	new->status = stat;
	new->isactive = 0; // ?
	new->parent = NULL;
	new->child = NULL;
	new->path = NULL;
	new->type = '/';
	if (stat == 'I')
	{
		new->weight= 0;
		arg->start = new;
	}
	else
	{
		if (stat == 'O')
			arg->end = new;
		new->weight = INFINITE;
	}

	if (map->list[new->key % map->size] == NULL)
		map->list[new->key % map->size] = new;
	else
	{
		new->hash_next = map->list[new->key % map->size];
		map->list[new->key % map->size] = new;
	}
	return (map);
}

t_data_map	*add_room(t_data_map *map, char *str, char status, t_lemin *arg)
{
	t_node			*new;
	char			**splitted;

	if (!(splitted = ft_strsplit(str, ' ')))
	{
		arg->malloc_error = 1;
		return (NULL);
	}
	if (!(new = ft_memalloc(sizeof(t_node))))
	{
		arg->malloc_error = 1;
		ft_freetab_str(splitted);
		return (NULL);
	}
	if (!(new->room = ft_strdup(splitted[0])))
	{
		arg->malloc_error = 1;
		ft_freetab_str(splitted);
		free(new);
		return (NULL);
	}
	arg->totalrooms++;
	ft_freetab_str(splitted);
	return (add_room_info(map, status, arg, new));
}

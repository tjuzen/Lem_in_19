/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:28:27 by tjuzen            #+#    #+#             */
/*   Updated: 2019/11/07 13:48:26 by bsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_data_map	*add_link(t_data_map *map, char *line, t_lemin *arg)
{
	char			**splitted;
	t_linkstab		*newlink;

	if (!(splitted = ft_strsplit(line, '-')))
	{
		arg->malloc_error = 1;
		return (map);
	}
	if (!(newlink = ft_memalloc(sizeof(t_linkstab))))
	{
		arg->malloc_error = 1;
		ft_freetab_str(splitted);
		return (map);
	}
	newlink->weight = 1;
	newlink->directed = 1;
	newlink->in = lookup(map, hashCode(splitted[0]), splitted[0]);
	newlink->out = lookup(map, hashCode(splitted[1]), splitted[1]);
	// printf("#$^$#  %s %s\n", newlink->in->room, newlink->out->room);

	if (!(newlink->in || (!(newlink->out))))
		return (map);
	if (!(newlink->in->from))
		newlink->in->from = newlink;
	else
	{
		newlink->nextfrom = newlink->in->from;
		newlink->in->from = newlink;
	}
	if (!(newlink->out->to))
		newlink->out->to = newlink;
	else
	{
		newlink->nexto = newlink->out->to;
		newlink->out->to = newlink;
	}
	if (map->links == NULL)
		map->links = newlink;
	else
	{
		newlink->next = map->links;
		map->links = newlink;
	}
	arg->totalinks++;
	ft_freetab_str(splitted);
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
	new->key = hashCode(new->room);
	new->status = status;
	new->isactive = 0;
	if (status == 'I')
	{
		new->weight= 0;
		arg->start = new;
	}
	else
	{
		if (status == 'O')
			arg->end = new;
		new->weight = INT_MAX - 10;
	}

	if (map->list[new->key % map->size] == NULL)
		map->list[new->key % map->size] = new;
	else
	{
		new->hash_next = map->list[new->key % map->size];
		map->list[new->key % map->size] = new;
	}
	arg->totalrooms++;
	ft_putendl(new->room);
	ft_freetab_str(splitted);
	return (map);
}

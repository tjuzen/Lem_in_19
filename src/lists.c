/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:28:27 by tjuzen            #+#    #+#             */
/*   Updated: 2019/11/05 12:50:25 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_data_map	*add_link(t_data_map *map, char *line, t_lemin *arg)
{
	char			**splitted;
	unsigned long	keya;
	unsigned long	keyb;
	t_linkstab		*newtab;

	if (!(splitted = ft_strsplit(line, '-')))
	{
		arg->malloc_error = 1;
		return (map);
	}
	if (!(newtab = ft_memalloc(sizeof(t_linkstab))))
	{
		arg->malloc_error = 1;
		ft_freetab_str(splitted);
		return (map);
	}
	newtab->weight = 1;
	newtab->directed = 1;
	newtab->in = lookup(map, hashCode(splitted[0]), splitted[0]);
	newtab->out = lookup(map, hashCode(splitted[1]), splitted[1]);
	if (!(newtab->in || (!(newtab->out))))
		return (map);
	if (map->links == NULL)
		map->links = newtab;
	else
	{
		newtab->next = map->links;
		map->links = newtab;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:28:27 by tjuzen            #+#    #+#             */
/*   Updated: 2019/11/04 19:25:32 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_data_map	*add(t_data_map *map, char *splitted1, char *splitted0, t_lemin *arg)
{
	t_linkstab	*newtab;

	if (!(newtab = ft_memalloc(sizeof(t_linkstab))))
	{
		// ft_freetab_str(splitted);
		return (NULL);
	}

	newtab->weight = 1;
	newtab->in = lookup(map, hashCode(splitted1), splitted1);
	newtab->out = lookup(map, hashCode(splitted0), splitted0);

	if (map->links == NULL)
		map->links = newtab;
	else
	{
		newtab->next = map->links;
		map->links = newtab;
	}
	return (map);
}

t_data_map	*add_link(t_data_map *map, char *line, t_lemin *arg)
{
	char		**splitted;
	unsigned long keya;
	unsigned long keyb;

	if (!(splitted = ft_strsplit(line, '-')))
		return (NULL);
	map = add(map, splitted[0], splitted[1], arg);
	arg->totalinks++;
	ft_freetab_str(splitted);
	return (map);
}

t_data_map	*add_collision(t_data_map *map, t_node *new, unsigned long key)
{
	new->hash_next = map->list[key % map->size];
	map->list[key % map->size] = new;
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
		// new->isactive = 1;
	}
	else
	{
		if (status == 'O')
			arg->end = new;
		// new->isactive = 0;
		new->weight = INT_MAX - 10;
	}

	if (map->list[new->key % map->size] == NULL)
		map->list[new->key % map->size] = new;
	else
		map = add_collision(map, new, new->key);

	// if (map->easyList == NULL)
	// 	map->easyList = new;
	// else
	// {
	// 	new->hash_next = map->easyList;
	// 	map->easyList = new;
	// }

	arg->totalrooms++;
	ft_putendl(new->room);
	ft_freetab_str(splitted);
	return (map);
}

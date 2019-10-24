/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:28:27 by tjuzen            #+#    #+#             */
/*   Updated: 2019/10/24 14:08:01 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_data_map	*add_collision(t_data_map *map, t_node *new, unsigned long key)
{
	new->hash_next = map->list[key % map->size];
	map->list[key % map->size] = new;
	return (map);
}

t_data_map	*add_connection(t_data_map *map, t_connect *new, unsigned long key)
{
	new->next = map->list[key % map->size]->link;
	map->list[key % map->size]->link = new;
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
	if (map->list[new->key % map->size] == NULL)
		map->list[new->key % map->size] = new;
	else
		map = add_collision(map, new, new->key);
	// printf("Room %s Key %6lu Size %3lu Pos %3lu\n",new->room,  new->key, map->size, new->key % map->size);

	ft_freetab_str(splitted);
	return (map);
}

t_data_map	*add_link(t_data_map *map, char *line)
{
	t_connect	*new;
	char		**splitted;
	unsigned long key;
	unsigned long key1;

	if (!(splitted = ft_strsplit(line, '-')))
		return (NULL);
	key = hashCode(splitted[0]);
	key1 = hashCode(splitted[1]);
	if (!(new = ft_memalloc(sizeof(t_connect))))
	{
		ft_freetab_str(splitted);
		return (NULL);
	}
	new->weight = 1;
	new->in = lookup(map, key, splitted[0]);
	new->out = lookup(map, key1, splitted[1]);
	if (map->list[key % map->size]->link == NULL)
		map->list[key % map->size]->link = new;
	else
		map = add_connection(map, new, key);
	ft_freetab_str(splitted);
	return (map);
}

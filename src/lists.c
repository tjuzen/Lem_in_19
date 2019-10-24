/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:28:27 by tjuzen            #+#    #+#             */
/*   Updated: 2019/10/24 16:29:43 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_data_map	*add_connection(t_data_map *map, t_connect *new, unsigned long key)
{
	new->next = map->list[key % map->size]->link;
	map->list[key % map->size]->link = new;
	return (map);
}

t_data_map	*add_in(t_data_map *map, char *splitted0, char *splitted1)
{
	t_connect	*new;

	if (!(new = ft_memalloc(sizeof(t_connect))))
	{
		// ft_freetab_str(splitted);
		return (NULL);
	}
	new->weight = 1;
	new->in = lookup(map, hashCode(splitted0), splitted0);
	new->out = lookup(map, hashCode(splitted1), splitted1);
	if (map->list[hashCode(splitted0) % map->size]->link == NULL)
		map->list[hashCode(splitted0) % map->size]->link = new;
	else
		map = add_connection(map, new, hashCode(splitted0));
	return (map);
}

t_data_map	*add_out(t_data_map *map, char *splitted1, char *splitted0)
{
	t_connect	*new;

	if (!(new = ft_memalloc(sizeof(t_connect))))
	{
		// ft_freetab_str(splitted);
		return (NULL);
	}
	new->weight = 1;
	new->in = lookup(map, hashCode(splitted1), splitted1);
	new->out = lookup(map, hashCode(splitted0), splitted0);
	printf("add out ajoute %s %s\n", splitted0, splitted1);
	if (map->list[hashCode(splitted1) % map->size]->link == NULL)
		map->list[hashCode(splitted1) % map->size]->link = new;
	else
		map = add_connection(map, new, hashCode(splitted1));
	return (map);
}

t_data_map	*add_link(t_data_map *map, char *line)
{
	char		**splitted;
	unsigned long keya;
	unsigned long keyb;

	if (!(splitted = ft_strsplit(line, '-')))
		return (NULL);
	keya = hashCode(splitted[0]);
	keyb = hashCode(splitted[1]);
	// printf("J'add in : ")
	map = add_in(map, splitted[0], splitted[1]);
	map = add_out(map, splitted[1], splitted[0]);
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
	if (map->list[new->key % map->size] == NULL)
		map->list[new->key % map->size] = new;
	else
		map = add_collision(map, new, new->key);
	// printf("%lu\n", new->key);
	// printf("Room %s Key %6lu Size %3lu Pos %3lu\n",new->room,  new->key, map->size, new->key % map->size);
	ft_putendl(new->room);
	ft_freetab_str(splitted);
	return (map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:28:27 by tjuzen            #+#    #+#             */
/*   Updated: 2019/10/21 14:46:39 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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
	{
		map->list[new->key % map->size]->hash_next = new;
		map->list[new->key % map->size]->count_hash++;
		arg->count_hash++;
	}
	printf("count_hash->%s: %d\n", new->room, map->list[new->key % map->size]->count_hash);
	ft_freetab_str(splitted);
	return (map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:28:27 by tjuzen            #+#    #+#             */
/*   Updated: 2019/10/23 20:38:28 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

unsigned long hashCode(char *room)
{
    unsigned long  hash = 0;
    while (*room)
        hash = (hash * 10) + *room++ - '0';
    return (200);
}

t_node	*lookup(t_data_map *map, unsigned long key, char *value)
{
	t_node *tmp;
	tmp = map->list[key % map->size];
	while(tmp)
	{
		if (tmp->key == key) // strequ
			return (tmp);
		tmp = tmp->hash_next;
	}
	return (NULL);
}

t_data_map *createMap(unsigned long size)
{
   t_data_map	*map;
   t_data_map	*tmp;
   int			i;
   unsigned long onessaieuntruc = 0;

   i = 0;
   if (!(map = (t_data_map*)ft_memalloc(sizeof(t_data_map))))
   	return (NULL);
   map->size = size;
   if (!(map->list = (t_node**)ft_memalloc(sizeof(t_node*)*size)))
   {
       free(map);
	   return (NULL);
   }
   return (map);
}

int				main(void)
{
	t_lemin			arg;
	t_data_map		*map;

	init_arg(&arg);
	if (!(map = createMap(100)))
		return (exit_free(&arg, map));
	map = read_file(&arg, map);
	if (arg.malloc_error != 0)
		return (exit_free(&arg, map));
	// free_map(map);
	printf("%s\n", map->list[200 % map->size]->room);
	printf("%s\n", map->list[200 % map->size]->hash_next->room);
	printf("%s\n", map->list[200 % map->size]->hash_next->hash_next->room);
	printf("%s\n", map->list[200 % map->size]->hash_next->hash_next->hash_next->room);
	printf("%s\n", map->list[200 % map->size]->hash_next->hash_next->hash_next->hash_next->room);
	printf("%s\n", map->list[200 % map->size]->hash_next->hash_next->hash_next->hash_next->hash_next->room);
	return (0);
}

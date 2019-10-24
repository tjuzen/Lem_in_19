/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:28:27 by tjuzen            #+#    #+#             */
/*   Updated: 2019/10/24 12:13:33 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

unsigned long hashCode(char *room)
{
    unsigned long  hash = 0;
    while (*room)
        hash = (hash * 6 * 10) + *room++ - '0' + 't' + 'j' + 'u' + 'z' + 'e' + 'n';
	// hash = (hash * 10) + *room++ - '0'; // donne bcp de fois la same key
	return (hash);
}

t_node	*lookup(t_data_map *map, unsigned long key, char *room)
{
	t_node *tmp;

	tmp = map->list[key % map->size];
	while (tmp)
	{
		if (tmp->key == key)
		{
			if (ft_strcmp(room, tmp->room) != 0)
			{
				printf("!String is not equal but same key! : %s %s\n", room, tmp->room);
				return (NULL);
			}
			return (tmp);
		}
		tmp = tmp->hash_next;
	}
	return (NULL);
}

t_data_map *createMap(unsigned long size)
{
   t_data_map	*map;
   t_data_map	*tmp;
   int			i;

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
	if (!(map = createMap(50000)))
		return (exit_free(&arg, map));
	map = read_file(&arg, map);
	if (arg.malloc_error != 0)
		return (exit_free(&arg, map));
	printf("is ok\n");
	free_map(map);
	return (0);
}

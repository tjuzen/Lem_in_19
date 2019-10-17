/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:28:27 by tjuzen            #+#    #+#             */
/*   Updated: 2019/10/17 18:08:06 by bsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

unsigned long hashCode(char *room)
{
    unsigned long  hash = 0;
    while (*room)
        hash = (hash * 10) + *room++ - '0';
    return hash;
}

t_node	*lookup(t_data_map *map, unsigned long key, char *value)
{
	t_node *tmp;

	tmp = map->list[key % map->size];
	while(tmp)
	{
		if (tmp->key == key)
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
	if (!(map = createMap(10000000)))
		return (exit_free(&arg, map));
	map = read_file(&arg, map);
	if (arg.malloc_error != 0)
		return (exit_free(&arg, map));
	// mylist = reverse_list(mylist);
	// print_delete(mylist, &arg);
	// insert(map,hashCode("A"),"A");
    printf("count_hash->ARG: %d\n", arg.count_hash);
	// printf("%c\n",lookup(map, hashCode("5"), "5"));
	return (0);
}

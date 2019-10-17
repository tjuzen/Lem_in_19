/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:28:27 by tjuzen            #+#    #+#             */
/*   Updated: 2019/10/17 15:15:46 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

unsigned long hashCode(t_data_map *map, char *room)
{
    unsigned long  hash = 0;
    while (*room)
        hash = (hash * 10) + *room++ - '0';
    return hash;
}

char lookup(t_data_map *map, unsigned long pos, char *value)
{
	t_node *list = map->list[pos];
	t_node *temp = list;
	while(temp)
	{
		if (temp->key == pos)
			return temp->status;
		temp = temp->next;
	}
	return 0;
}


t_data_map *createMap(unsigned long long size)
{
   t_data_map *map;
   int i;

   i = 0;
   map = (t_data_map*)ft_memalloc(sizeof(t_data_map));
   map->size = size;
   map->list = (t_node**)ft_memalloc(sizeof(t_node*)*size);
   return (map);
}

int				main(void)
{
	t_lemin			arg;
	t_data_map		*map;

	map = createMap(10000000);
	init_arg(&arg);
	map = read_file(&arg, map);
	// if (arg.malloc_error != 0)
	// 	return (exit_free(&arg, mylist));
	// mylist = reverse_list(mylist);
	// print_delete(mylist, &arg);
	// insert(map,hashCode("A"),"A");
	printf("%c\n",lookup(map, hashCode(map, "5"), "5"));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:28:27 by tjuzen            #+#    #+#             */
/*   Updated: 2019/10/17 13:35:01 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

unsigned long hashCode(t_data_map *map, char *cp)
{
    unsigned long  hash = 0;
    while (*cp)
        hash = (hash * 10) + *cp++ - '0';
    return hash;
}

char *lookup(t_data_map *map, char *key)
{
	unsigned long pos;
	pos = hashCode(map, key);
	t_node *list = map->list[pos];
	t_node *temp = list;
	while(temp)
	{
		if (temp->room==key)
			return temp->link;
		temp = temp->next;
	}
	return NULL;
}


t_data_map *createMap(int size)
{
   t_data_map *map;
   int i;

   i = 0;
   map = (t_data_map*)ft_memalloc(sizeof(t_data_map));
   map->size = size;
   map->list = (t_node**)ft_memalloc(sizeof(t_node*)*size);
   return (map);
}

void insert(t_data_map *map ,unsigned long pos, char *val)
{
	t_node *list = map->list[pos];
	t_node *newNode = (t_node*)ft_memalloc(sizeof(t_node));
	t_node *temp = list;
	while (temp)
	{
		if (temp->room==key)
		{
			temp->link = val;
			return ;
		}
		temp = temp->next;
	}
	newNode->room = key;
	newNode->link = val;
	newNode->next = list;
	map->list[pos] = newNode;
}

int				main(void)
{
	t_list_lemin	*mylist;


	t_lemin			arg;
	t_data_map		*map;
	t_node			*node;

	node = NULL;
	map = createMap(10000000);
	init_arg(&arg);
	mylist = read_file(&arg, map);
	if (arg.malloc_error != 0)
		return (exit_free(&arg, mylist));
	mylist = reverse_list(mylist);
	print_delete(mylist, &arg);
	insert(map,hashCode("A"),"A");
	printf("%s\n",lookup(map,"A"));
	return (0);
}

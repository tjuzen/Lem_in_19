/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:28:27 by tjuzen            #+#    #+#             */
/*   Updated: 2019/10/17 16:08:37 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_data_map	*add_room(t_data_map *map, char *str, char status, t_lemin *arg)
{
	t_node			*new;
	t_node			*tmp;
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
		return (NULL);
	}
	new->key = hashCode(new->room);
	new->status = status;
	if (map->list[new->key % map->size] == NULL)
		map->list[new->key % map->size] = new;
	else
	{
		tmp = map->list[tmp->key % map->size]->hash_next;
		map->list[tmp->key % map->size]->hash_next = new;
		new->hash_next = tmp;
	}
	ft_freetab_str(splitted);
	return (map);
}

// void			delete(t_data_map *map, t_lemin *arg)
// {
// 	t_data_map	*tmp;
//
// 	tmp = map;
// 	while (tmp != NULL)
// 		tmp = tmp->hash_next;
// 	while (mylist)
// 	{
// 		tmp = map->hash_next;
// 		ft_strdel(&map->room);
// 		free(map);
// 		map = tmp;
// 	}
// }
//
// void			print_delete(t_list_lemin *mylist, t_lemin *arg)
// {
// 	t_list_lemin	*tmp;
//
// 	tmp = mylist;
// 	ft_printf("Nubers of ants = %i\n\n", arg->ants);
// 	while (tmp != NULL)
// 	{
// 		ft_printf("Room     :   %s\nStatus   :   %c\n\n",
// 		tmp->room, tmp->status);
// 		tmp = tmp->hash_next;
// 	}
// 	while (mylist)
// 	{
// 		tmp = mylist->hash_next;
// 		ft_strdel(&mylist->room);
// 		free(mylist);
// 		mylist = tmp;
// 	}
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:28:27 by tjuzen            #+#    #+#             */
/*   Updated: 2019/10/17 14:30:19 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void insert(t_data_map *map ,unsigned long pos, char *value, t_node	*tmp)
{
	t_node *list = map->list[pos];
	map->list[pos] = tmp;
}

t_data_map	*add_room(t_data_map *map, char *str, char status, t_lemin *arg)
{
	t_node			*tmp;
	char			**splitted;

	if (!(splitted = ft_strsplit(str, ' ')))
	{
		arg->malloc_error = 1;
		return (NULL);
	}
	if (!(tmp = ft_memalloc(sizeof(t_node))))
	{
		arg->malloc_error = 1;
		ft_freetab_str(splitted);
		return (NULL);
	}
	if (!(tmp->room = ft_strdup(splitted[0])))
	{
		arg->malloc_error = 1;
		ft_freetab_str(splitted);
		// print_delete(tmp, arg);
		return (NULL);
	}
	tmp->key = hashCode(map, tmp->room);
	tmp->status = status;
	insert(map, hashCode(map, tmp->room), tmp->room, tmp);
	ft_freetab_str(splitted);
	return (map);
}

// void			delete(t_list_lemin *mylist, t_lemin *arg)
// {
// 	t_list_lemin	*tmp;
//
// 	tmp = mylist;
// 	while (tmp != NULL)
// 		tmp = tmp->next;
// 	while (mylist)
// 	{
// 		tmp = mylist->next;
// 		ft_strdel(&mylist->room);
// 		free(mylist);
// 		mylist = tmp;
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
// 		tmp = tmp->next;
// 	}
// 	while (mylist)
// 	{
// 		tmp = mylist->next;
// 		ft_strdel(&mylist->room);
// 		free(mylist);
// 		mylist = tmp;
// 	}
// }

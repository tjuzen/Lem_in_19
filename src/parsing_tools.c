/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:47:12 by tjuzen            #+#    #+#             */
/*   Updated: 2019/10/17 15:42:20 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int get_number_of_ants(t_lemin *arg)
{
	char	*line;

	get_next_line(0, &line);
	if (!(line))
		return (intreturn_mallocerr(1, arg));
	if (arg->ants == -1)
		arg->ants = ft_atoi(line);
	ft_strdel(&line);
	return (arg->ants == 0 ? -1 : 1);
}

t_data_map	*start(t_data_map *map, char *str, char status, t_lemin *arg)
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
	tmp->key = hashCode(tmp->room);
	tmp->status = status;
	t_node *list = map->list[hashCode(tmp->room)];
	map->list[hashCode(tmp->room)] = tmp;	ft_freetab_str(splitted);
	return (map);
}
//
// t_data_map *end(t_lemin *arg, t_data_map *map)
// {
// 	char	*line;
//
// 	get_next_line(0, &line);
// 	if (!(line))
// 		return (lstreturn_mallocerr(1, arg));
// 	if (is_room(line, arg) == 1)
// 	{
// 		if (arg->end != 0)
// 		{
// 			arg->wrong_line = 1;
// 			ft_strdel(&line);
// 			return (mylist);
// 		}
// 		mylist = add_room(mylist, line, 'O', arg);
// 		arg->end++;
// 	}
// 	else
// 		arg->malloc_error = 2;
// 	return (return_delete(mylist, line));
// }

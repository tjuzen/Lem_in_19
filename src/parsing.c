/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 20:26:27 by tjuzen            #+#    #+#             */
/*   Updated: 2019/10/14 16:54:16 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_list_lemin *get_infos(char *line, t_list_lemin *mylist, t_lemin *arg)
{
	if (ft_strcmp(line, "##start") == 0)
		return (start(arg, mylist));
	if (ft_strcmp(line, "##end") == 0)
		return (end(arg, mylist));
	if (is_room(line, arg) == 1)
	{
		mylist = add_room(mylist, line, 'X', arg);
		return (mylist);
	}
	if (is_comment(line, arg) == 1)
		return (mylist);
	arg->wrong_line = 1;
	return (mylist);
}

t_list_lemin *read_file(t_lemin *arg)
{
	char			*line;
	t_list_lemin	*mylist;

	mylist = NULL;
	if (get_number_of_ants(arg) == -1)
		return (lstreturn_mallocerr(1, arg));
	while (get_next_line(0, &line) > 0)
	{
		if (!(line))
			return (lstreturn_mallocerr(1, arg));
		mylist = get_infos(line, mylist, arg);
		if (arg->malloc_error != 0 || arg->wrong_line == 1)
			return (return_delete(mylist, line));
		ft_strdel(&line);
	}
	return (return_delete(mylist, line));
}

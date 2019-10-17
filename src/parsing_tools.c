/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:47:12 by tjuzen            #+#    #+#             */
/*   Updated: 2019/10/16 14:53:02 by tjuzen           ###   ########.fr       */
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

t_list_lemin *start(t_lemin *arg, t_list_lemin *mylist)
{
	char	*line;

	get_next_line(0, &line);
	if (!(line))
		return (lstreturn_mallocerr(1, arg));
	if (is_room(line, arg) == 1)
	{
		if (arg->start != 0)
		{
			arg->wrong_line = 1;
			ft_strdel(&line);
			return (mylist);
		}
		mylist = add_room(mylist, line, 'I', arg);
		arg->start++;
	}
	else
		arg->malloc_error = 2;
	return (return_delete(mylist, line));
}

t_list_lemin *end(t_lemin *arg, t_list_lemin *mylist)
{
	char	*line;

	get_next_line(0, &line);
	if (!(line))
		return (lstreturn_mallocerr(1, arg));
	if (is_room(line, arg) == 1)
	{
		if (arg->end != 0)
		{
			arg->wrong_line = 1;
			ft_strdel(&line);
			return (mylist);
		}
		mylist = add_room(mylist, line, 'O', arg);
		arg->end++;
	}
	else
		arg->malloc_error = 2;
	return (return_delete(mylist, line));
}

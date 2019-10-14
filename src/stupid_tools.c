/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stupid_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:24:31 by tjuzen            #+#    #+#             */
/*   Updated: 2019/10/14 16:37:12 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_list_lemin	*lstreturn_mallocerr(int value, t_lemin *arg)
{
	arg->malloc_error = value;
	return (NULL);
}

int				intreturn_mallocerr(int value, t_lemin *arg)
{
	arg->malloc_error = value;
	return (-1);
}

void			init_arg(t_lemin *arg)
{
	arg->ants = -1;
	arg->wrong_line = 0;
	arg->malloc_error = 0;
	arg->start = 0;
	arg->end = 0;
}

t_list_lemin	*return_delete(t_list_lemin *mylist, char *line)
{
	ft_strdel(&line);
	return (mylist);
}

int				exit_free(t_lemin *arg, t_list_lemin *mylist)
{
	if (arg->malloc_error == 2)
	{
		ft_putendl("Wrong start or end!");
		delete(mylist, arg);
	}
	if (arg->malloc_error == 3)
	{
		ft_putendl("invalid file!");
		delete(mylist, arg);
	}
	return (-1);
}

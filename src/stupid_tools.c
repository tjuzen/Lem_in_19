/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stupid_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:24:31 by tjuzen            #+#    #+#             */
/*   Updated: 2019/10/17 14:31:57 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_data_map	*lstreturn_mallocerr(int value, t_lemin *arg)
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

t_data_map	*return_delete(t_data_map	*map, char *line)
{
	ft_strdel(&line);
	return (map);
}

int				exit_free(t_lemin *arg, t_data_map	*map)
{
	if (arg->malloc_error == 2)
	{
		ft_putendl("Wrong start or end!");
		// delete(map, arg);
	}
	if (arg->malloc_error == 3)
	{
		ft_putendl("invalid file!");
		// delete(map, arg);
	}
	return (-1);
}

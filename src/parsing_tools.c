/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:47:12 by tjuzen            #+#    #+#             */
/*   Updated: 2019/11/14 18:10:33 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int get_number_of_ants(t_lemin *arg)
{
	char	*line;

	get_next_line(0, &line , 1);
	if (!(line))
		return (intreturn_mallocerr(1, arg));
	if (arg->ants == -1)
		arg->ants = ft_atoi(line);
	ft_strdel(&line);
	return (arg->ants == 0 ? -1 : 1);
}

t_data_map *add_in_out(char *line, t_data_map *map, t_lemin *arg, char s)
{
	get_next_line(0, &line, 1);
	if (!line)
	{
		arg->malloc_error = -1;
		return (map);
	}
	if (is_room(line, arg) != 1)
	{
		printf("End is not a valid room\n");
		arg->malloc_error = -1;
		ft_strdel(&line);
		return (map);
	}
	map = add_room(map, line, s, arg);
	ft_strdel(&line);
	return (map);
}

int		check_links(t_data_map *map, t_node *a, t_node *b)
{

	t_linkstab *find;

	find = a->to;
	if (a->to != NULL)
	{
		while (find->nexto)
		{
			if (find->rooma->room == a->room && find->roomb->room == b->room)
				return (0);
			if (find->rooma->room == b->room && find->roomb->room == a->room)
				return (0);
			find = find->nexto;
		}
	}
	return (1);
}

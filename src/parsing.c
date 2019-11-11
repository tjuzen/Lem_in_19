/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 20:26:27 by tjuzen            #+#    #+#             */
/*   Updated: 2019/11/11 18:16:30 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_data_map *get_infos(char *line, t_data_map *map, t_lemin *arg)
{

	if (ft_strcmp(line, "##start") == 0)
	{
		get_next_line(0, &line, 0);
		if (!line)
		{
			arg->malloc_error = -1;
			return (map);
		}
		if (is_room(line, arg) != 1)
		{
			printf("Start is not a valid room\n");
			arg->malloc_error = -1;
			ft_strdel(&line);
			return (map);
		}
		map = add_room(map, line, 'I', arg);
		ft_strdel(&line);
		return (map);
	}
	if (ft_strcmp(line, "##end") == 0)
	{
		get_next_line(0, &line, 0);
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
		map = add_room(map, line, 'O', arg);
		ft_strdel(&line);
		return (map);
	}
	if (is_comment(line, arg) == 1)
		return (map);

	if (is_room(line, arg) == 1)
	{
		// ft_putendl(line);
		map = add_room(map, line, 'X', arg);
		return (map);
	}
	if (is_link(line, map, arg) != -1)
	{
		// ft_putendl(line);
		map = add_link(map, line, arg, 1);
		return (map);
	}

	printf("\nWrong line\n");
	arg->wrong_line = 1;
	return (map);
}

t_data_map *read_file(t_lemin *arg, t_data_map *map)
{
	char	*line;

	if (get_number_of_ants(arg) == -1)
		return (lstreturn_mallocerr(1, arg, map));
	while (get_next_line(0, &line, 0) > 0)
	{
		if (!(line))
			return (lstreturn_mallocerr(1, arg, map));
		map = get_infos(line, map, arg);
		if (arg->malloc_error != 0 || arg->wrong_line == 1)
			return (return_delete(map, line));
		ft_strdel(&line);
	}
	return (return_delete(map, line));
}

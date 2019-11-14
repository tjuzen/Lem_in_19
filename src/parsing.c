/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 20:26:27 by tjuzen            #+#    #+#             */
/*   Updated: 2019/11/14 15:23:49 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_data_map *get_infos(char *line, t_data_map *map, t_lemin *arg)
{
	if (ft_strcmp(line, "##start") == 0)
		return (add_in_out(line, map, arg, 'I'));
	if (ft_strcmp(line, "##end") == 0)
		return (add_in_out(line, map, arg, 'O'));
	if (is_comment(line, arg) == 1)
		return (map);
	if (is_room(line, arg) == 1)
	{
		map = add_room(map, line, 'X', arg);
		return (map);
	}
	int ret = is_link(line, map, arg);
	if (ret == 0)
		return (map);
	else if (ret == 1)
	{
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
	while (get_next_line(0, &line, 1) > 0)
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

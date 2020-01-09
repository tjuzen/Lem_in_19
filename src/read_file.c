/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuarez- <bsuarez-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 11:18:56 by bsuarez-          #+#    #+#             */
/*   Updated: 2020/01/09 17:51:56 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int 	get_infos(char *line, t_data_map **map, t_lemin *arg)
{
	char	s;
	int		ret;

	s = 'X';
	if (is_ant(line, arg) == 1)
		return (get_number_of_ants(line, arg));
	if ((s = is_command(line)) == 73 && arg->in == 0)
		return (add_end_start(line, map, arg, s));
	if ((s = is_command(line)) == 79 && arg->out == 0)
		return (add_end_start(line, map, arg, s));
	if (is_room(line, arg) == 1)
		return (add_room(map, line, 'X', arg));
	if ((ret = is_link(line, map, arg)) == 1)
		return (add_link(map, line, arg, 1));
	if (is_comment(line, arg) == 1 || is_command(line) == 1 || ret == 0)
		return (0);
	return (-1);
}

int 	read_file(t_lemin *arg, t_data_map **map)
{
	char 	*line;
	int		ret;

	line = NULL;
	while ((ret = get_next_line(0, &line, 1)) > 0)
	{
		if (!(line) || (get_infos(line, map, arg) == -1) || ret == 0)
		{
			ft_strdel(&line);
			return (-1);
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (0);
}

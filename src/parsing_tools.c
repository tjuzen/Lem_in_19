/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:47:12 by tjuzen            #+#    #+#             */
/*   Updated: 2020/01/08 13:29:02 by bsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int 	get_number_of_ants(char *line, t_lemin *arg)
{
	if (arg->ants == -1)
		arg->ants = ft_atoi(line);
	if (arg->ants <= 0)
		return (-1);
	return (0);
}

int		valid_end_start(int i, t_lemin *arg, char s)
{
	if (s == 'I')
	{
		i = arg->in;
		arg->in = 1;
	}
	if (s == 'O')
	{
		i = arg->out;
		arg->out = 1;
	}
	return (i);
}

int 	add_end_start(char *line, t_data_map **map, t_lemin *arg, char s)
{
	int i;

	i = valid_end_start(0, arg, s);
	while (i == 0)
	{
		get_next_line(0, &line, 1);
		if (!line)
			return (-1);
		if (is_room(line, arg) == 1)
		{
			i++;
			add_room(map, line, s, arg);
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (0);
}

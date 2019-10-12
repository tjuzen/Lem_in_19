/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 20:26:27 by tjuzen            #+#    #+#             */
/*   Updated: 2019/10/12 20:32:33 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"


int get_number_of_ants(t_lemin *arg)
{
	char	*line;

	get_next_line(0, &line);
	if (!(line))
		exit(EXIT_FAILURE);
	if (arg->ants == -1)
		arg->ants = ft_atoi(line);
	if (arg->ants == 0)
	{
		ft_printf("NO ANTS!\n");
		ft_strdel(&line);
		return (-1);
	}
	ft_strdel(&line);
	return (1);
}

int is_room(char *line, t_lemin *arg)
{
	char **splitted;
	int i;

	i = -1;
	if (line[0] == '#' || line[0] == 'L')
		return (-1);
	if (!(splitted = ft_strsplit(line, ' ')))
		exit(EXIT_FAILURE);
	if (!(splitted[0]) || !(splitted[1]) || !(splitted[2]) || splitted[3])
	{
		ft_freetab_str(splitted);
		return (-1);
	}
	while (splitted[1][++i])
		if (ft_isdigit(splitted[1][i]) != 1)
		{
			ft_freetab_str(splitted);
			return (-1);
		}
	i = -1;
	while (splitted[2][++i])
		if (ft_isdigit(splitted[2][i]) != 1)
		{
			ft_freetab_str(splitted);
			return (-1);
		}
	ft_freetab_str(splitted);
	return (1);
}

t_list_lemin *get_infos(char *line, t_list_lemin *mylist, t_lemin *arg)
{
	if (ft_strcmp(line, "##start") == 0)
	{
		get_next_line(0, &line);
		if (!(line))
			exit(EXIT_FAILURE);
		if (is_room(line, arg) == 1)
			mylist = add_room(mylist, line, 0, arg);
		ft_strdel(&line);
		return (mylist);
	}
	if (ft_strcmp(line, "##end") == 0)
	{
		get_next_line(0, &line);
		if (!(line))
			exit(EXIT_FAILURE);
		if (is_room(line, arg) == 1)
			mylist = add_room(mylist, line, 2, arg);
		ft_strdel(&line);
		return (mylist);
	}
	if (is_room(line, arg) == 1)
	{
		mylist = add_room(mylist, line, 1, arg);
		return (mylist);
	}
	arg->wrong_line = 1;
	ft_strdel(&line);
	return (mylist);
}

t_list_lemin *read_file(t_lemin *arg)
{
	char	*line;
	t_list_lemin *mylist;

	mylist = NULL;
	if (get_number_of_ants(arg) == -1)
		return (NULL);
	while (get_next_line(0, &line) > 0)
	{
		if (!line)
			exit(EXIT_FAILURE);
		mylist = get_infos(line, mylist, arg);
		if (arg->wrong_line == 1)
			return (mylist);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (mylist);
}

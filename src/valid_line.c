/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:27:56 by tjuzen            #+#    #+#             */
/*   Updated: 2019/11/22 13:59:09 by bsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		is_ant(char *line, t_lemin *arg)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]) == 0)
			return (-1);
		i++;
	}
	if ((ft_atoi(line) && arg->ants == -1))
		return (1);
	return (-1);
}

int		is_comment(char *line, t_lemin *arg)
{
	if (ft_strlen(line) < 2)
		return (-1);
	if (line[0] == '#' && line[1] != '#')
		return (1);
	return (-1);
}

int		is_command(char *line)
{
	if (ft_strcmp(line, "##start") == 0)
		return (73);
	if (ft_strcmp(line, "##end") == 0)
		return (79);
	if (line [0] == '#' && line[1] =='#')
		return (1);
	return (-1);
}

int		is_room(char *line, t_lemin *arg)
{
	char	**splitted;
	int		i;

	i = -1;
	if (line[0] == '#' || line[0] == 'L')
		return (-1);
	if (ft_strchr(line, '-') != NULL)
		return (-1);
	if (!(splitted = ft_strsplit(line, ' ')))
		return (-1);
	if (!(splitted[0]) || !(splitted[1]) || !(splitted[2]) || splitted[3])
	{
		return (retfreetab_str(splitted, -1));
	}
	if (ft_strlen(splitted[1]) > 9 || ft_strlen(splitted[2]) > 9)
	{
		printf("PUTE\n\n\n\n");
		return (-1);
	}
	while (splitted[1][++i])
		if (ft_isdigit(splitted[1][i]) != 1)
			return (retfreetab_str(splitted, -1));
	i = -1;
	while (splitted[2][++i])
		if (ft_isdigit(splitted[2][i]) != 1)
			return (retfreetab_str(splitted, -1));
	return (retfreetab_str(splitted, 1));
}

int		is_link(char *line, t_data_map **map, t_lemin *arg)
{
	char	**splitted;
	int		i;
	t_node	*room_a;
	t_node	*room_b;

	i = -1;
	splitted = NULL;
	if (!(splitted = ft_strsplit(line, '-')))
		return (-1);
	if (!(splitted[0] || (!(splitted[1]))))
	{
		ft_freetab_str(splitted);
		return (-1);
	}
	room_a = lookup((*map), hashCode(splitted[0]), splitted[0]);
	if (!(room_a))
		return (-1);
	room_b = lookup((*map), hashCode(splitted[1]), splitted[1]);
	if (!(room_b))
		return (-1);
	ft_freetab_str(splitted);
	return (1);
}

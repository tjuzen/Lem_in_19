/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:27:56 by tjuzen            #+#    #+#             */
/*   Updated: 2019/10/21 14:32:58 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		is_comment(char *line, t_lemin *arg)
{
	if (ft_strlen(line) < 2)
		return (-1);
	if (line[0] == '#' && line[1] != '#')
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
	if (!(splitted = ft_strsplit(line, ' ')))
		return (intreturn_mallocerr(1, arg));
	if (!(splitted[0]) || !(splitted[1]) || !(splitted[2]) || splitted[3])
		return (retfreetab_str(splitted, -1));
	while (splitted[1][++i])
		if (ft_isdigit(splitted[1][i]) != 1)
			return (retfreetab_str(splitted, -1));
	i = -1;
	while (splitted[2][++i])
		if (ft_isdigit(splitted[2][i]) != 1)
			return (retfreetab_str(splitted, -1));
	return (retfreetab_str(splitted, 1));
}

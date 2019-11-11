/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:47:12 by tjuzen            #+#    #+#             */
/*   Updated: 2019/11/04 14:29:45 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int get_number_of_ants(t_lemin *arg)
{
	char	*line;

	get_next_line(0, &line);
	if (!(line))
		return (intreturn_mallocerr(1, arg));
	if (arg->ants == -1)
		arg->ants = ft_atoi(line);
	// if (arg->ants != 0)
	// 	ft_putendl(line);
	ft_strdel(&line);
	return (arg->ants == 0 ? -1 : 1);
}

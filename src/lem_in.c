/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:28:27 by tjuzen            #+#    #+#             */
/*   Updated: 2019/10/07 16:58:59 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

// int get_ants(char *line)
// {
// 	int	i;
//
// 	i = -1;
// 	while (line[++i] < )
// }

int main()
{
	char	*line;
	int		ants;

	ants = -1;
	while (get_next_line(0, &line) > 0)
	{
		if (ants == -1)
			ants = ft_atoi(line);
		ft_printf("%s\nants : %i\n", line, ants);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (0);
}

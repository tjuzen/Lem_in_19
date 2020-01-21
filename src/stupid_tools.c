/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stupid_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:24:31 by tjuzen            #+#    #+#             */
/*   Updated: 2020/01/21 14:46:31 by bsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_data_map		*init_arg(t_lemin *arg)
{
	t_data_map *map;

	map = NULL;
	if (!(map = createmap(500000, map)))
		return (NULL);
	arg->ants = -1;
	arg->wrong_line = 0;
	arg->malloc_error = 0;
	arg->totalrooms = 0;
	arg->totalinks = 0;
	arg->total_weight = 0;
	arg->nbr_round = INFINITE;
	arg->in = 0;
	arg->out = 0;
	arg->sum_path = 0;
	arg->one = 0;
	arg->found = 0;
	arg->display_links = 0;
	arg->display_score = 0;
	return (map);
}

int				exit_free(t_lemin *arg, t_data_map *map)
{
	arg->one = 1;
	ft_printf("ERROR\n");
	free_map(map);
	return (-1);
}

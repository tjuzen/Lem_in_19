/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_ants.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuarez- <bsuarez-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 14:36:58 by bsuarez-          #+#    #+#             */
/*   Updated: 2020/01/21 14:41:26 by bsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	check_best_path(t_lemin *arg, t_path **way, int path)
{
	int i;
	int weight;
	int res;

	i = 0;
	res = 0;
	weight = INFINITE;
	while (i < path)
	{
		if (way[i]->weight < weight)
		{
			weight = way[i]->weight;
			res = way[i]->path;
		}
		i++;
	}
	arg->best = res;
}

int		last_ants(t_lemin *arg, int i, t_path **way, int j)
{
	arg->modif++;
	if ((i >= (arg->ants / 10) * 6)
		&& ((arg->nbr_round) / 10 * 4 >= way[j]->weight)
		&& ((arg->ants - i) >= way[j]->weight))
	{
		if ((assign_ants(arg, i++, way[j], arg->turn + 1)) == -1)
			return (-1);
		arg->check++;
	}
	if ((i >= (arg->ants / 100) * 99)
		&& (arg->modif == arg->max_path && arg->check == 0))
	{
		if ((assign_ants(arg, i++, way[arg->best], arg->turn + 1)) == -1)
			return (-1);
	}
	return (i);
}

int		prepare_ants(t_lemin *arg, int i, t_path **way, int path)
{
	int j;

	check_best_path(arg, way, path);
	while (i < arg->ants)
	{
		j = 0;
		arg->modif = 0;
		arg->check = 0;
		while (j < path && i <= arg->ants)
		{
			if (arg->turn + way[j]->weight <= (int)arg->nbr_round + 1)
			{
				if ((assign_ants(arg, i++, way[j], arg->turn + 1)) == -1)
					return (-1);
			}
			else
			{
				if ((i = last_ants(arg, i, way, j)) == -1)
					return (-1);
			}
			j++;
		}
		arg->turn++;
	}
	return (0);
}

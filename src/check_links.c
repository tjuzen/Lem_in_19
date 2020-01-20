/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:10:12 by tjuzen            #+#    #+#             */
/*   Updated: 2020/01/20 16:10:43 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		count_select(t_data_map *map, t_lemin *arg, int ok)
{
	t_node		*tmproom;
	t_linkstab	*tmp;

	tmproom = arg->end;
	while (tmproom)
	{
		tmp = lookuplink(map, tmproom->parent, tmproom);
		if (tmp)
		{
			if (tmp->imintern != 1)
			{
				arg->total_weight -= -1;
				tmp->fakeselected++;
			}
			if (tmp->reversed)
				tmp->reversed->fakeselected++;
		}
		if (tmproom->parent == arg->start)
		{
			ok = 1;
			break ;
		}
		tmproom = tmproom->parent;
	}
	return (ok);
}

int		checkeverything(t_data_map *map, t_lemin *arg, t_linkstab *tmp)
{
	int tmpweight;

	tmpweight = arg->total_weight;
	if (count_select(map, arg, 0) == 1)
	{
		tmp = (*map).links;
		while (tmp)
		{
			if (tmp->fakeselected > 1)
			{
				if (tmp->imintern != 1)
					arg->total_weight--;
				tmp->fakeselected = 0;
			}
			tmp = tmp->next;
		}
	}
	else
	{
		arg->total_weight = tmpweight;
		return (-1);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_moretools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:15:07 by tjuzen            #+#    #+#             */
/*   Updated: 2020/01/22 13:44:00 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int			add_found_path(t_data_map *map, t_lemin *arg, t_node *room)
{
	int			weight;
	t_linkstab	*tmp;

	weight = 0;
	while (room)
	{
		tmp = lookuplink(map, room->parent, room);
		if (tmp)
		{
			if (tmp->imintern != 1)
			{
				tmp->selected++;
				weight++;
			}
			if (tmp->reversed)
				tmp->reversed->selected++;
		}
		if (room == arg->start)
			return (0);
		room = room->parent;
	}
	return (-1);
}

t_linkstab	*change_type(t_node *a)
{
	t_linkstab *find;

	find = a->to;
	while (find)
	{
		find->rooma = find->rooma->out;
		find = find->nexto;
	}
	return (NULL);
}

void		inverse_links(t_data_map *map, t_node *room)
{
	t_linkstab	*tmp;
	t_node		*tmproom;

	while (room)
	{
		tmp = lookuplink(map, room->parent, room);
		if (tmp)
		{
			tmproom = tmp->rooma;
			tmp->rooma = tmp->roomb;
			tmp->roomb = tmproom;
			tmp->weight *= -1;
			tmp->inversed = 1;
		}
		room = room->parent;
	}
}

void		check_inversed(t_linkstab *tmp)
{
	t_node		*tmproom;

	while (tmp->next)
	{
		if (tmp->selected > 1)
		{
			tmproom = tmp->rooma;
			tmp->rooma = tmp->roomb;
			tmp->roomb = tmproom;
			tmp->inversed = 0;
			if (tmp->imintern == 1)
				tmp->weight = 0;
			else
				tmp->weight = 1;
			tmp->selected = 0;
		}
		tmp = tmp->next;
	}
}

int			split(t_data_map **map, t_lemin *arg)
{
	if (duplicate_nodes((*map), arg, arg->end) == -1)
		return (-1);
	inverse_links((*map), arg->end);
	reset(arg, (*map)->links);
	bellman_peugeot(map, arg);
	return (1);
}

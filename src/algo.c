/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:51:04 by tjuzen            #+#    #+#             */
/*   Updated: 2020/01/20 18:37:36 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		bellman_peugeot(t_data_map **map, t_lemin *arg)
{
	t_linkstab	*link;
	int			countrooms;

	countrooms = arg->totalrooms;
	link = (*map)->links;
	while (--countrooms > 0 && link)
	{
		link = (*map)->links;
		if (bellwhile_ford(link, arg) == 666)
			break ;
	}
	return (1);
}

/*
** 1: Find the shortest path P1 from node s to node t
** 2: for i = 2,..., k
** 3: For node-disjoint paths, split the intermediate nodes
** 4: Replace each link of all Px where x < i with a reverse link
** 5: Find the shortest path Pi from node s to node t
** 6: Remove all overlapping links to get i disjoint paths Px where x ≤ i.
*/

int		negative_cycle(t_data_map **map, t_lemin *arg)
{
	t_linkstab	*link;

	link = (*map)->links;
	if (arg->display_links == 1)
		print_all_links(arg, link);
	while (link->next)
	{
		if (link->isactive == 1)
		{
			if (link->rooma->weight != INFINITE
				&& link->rooma->weight + link->weight < link->roomb->weight
				&& link->roomb != arg->start && link->isactive == 1
				&& link->rooma != arg->end)
			{
				arg->found--;
				return (1);
			}
		}
		link = link->next;
	}
	return (-1);
}

int		find_first(t_data_map **map, t_lemin *arg)
{
	bellman_peugeot(map, arg);
	if (add_found_path((*map), arg, arg->end) == -1)
		return (-1);
	checkeverything((*map), arg, (*map)->links);
	return (1);
}

int		find_more(double new, double old, t_data_map **map, t_lemin *arg)
{
	if (new < old)
	{
		if (add_found_path((*map), arg, arg->end) == -1)
		{
			arg->found--;
			return (-1);
		}
		check_inversed((*map)->links);
	}
	else
		arg->found--;
	return (1);
}

int		find_path(t_data_map **map, t_lemin *arg)
{
	double	new;
	double	old;

	find_first(map, arg);
	old = INFINITE;
	new = cost_path(arg, 1);
	while ((int)new < (int)old && arg->one == 0)
	{
		if (split(map, arg) == -1)
			return (-1);
		if (negative_cycle(map, arg) == 1)
			break ;
		if (checkeverything((*map), arg, (*map)->links) == -1)
			break ;
		old = new;
		new = cost_path(arg, arg->found + 1);
		if (find_more(new, old, map, arg) == -1)
			break ;
	}
	if (resolve_map(arg, map, arg->found) == -1)
		return (-1);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuarez- <bsuarez-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:29:06 by bsuarez-          #+#    #+#             */
/*   Updated: 2020/01/20 18:42:13 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_node	*follow_path(t_path *new, t_lemin *arg, t_data_map **map, t_node *tmp)
{
	t_linkstab *links;

	links = (*map)->links;
	if (new->path_list[0] == NULL)
		return (tmp);
	while (links)
	{
		if (links->selected == 1)
		{
			if ((ft_strcmp(links->rooma->room, tmp->room) == 0)
				&& check_follow(new, arg, links->roomb) == 0)
				return (tmp = links->roomb);
			if ((ft_strcmp(links->roomb->room, tmp->room) == 0)
				&& (check_follow(new, arg, links->rooma) == 0))
				return (tmp = links->rooma);
		}
		links = links->next;
	}
	return (NULL);
}

int		stock_path(t_data_map **map, t_lemin *arg, t_linkstab *links, int way)
{
	t_path	*new;
	t_node	*tmp;
	int		i;

	i = 0;
	tmp = switch_room(links, arg);
	if (!tmp)
		return (-1);
	if (!(new = ft_memalloc(sizeof(t_path))))
		return (-1);
	if (!(new->path_list = ft_memalloc(sizeof(char**) * 500)))
		return (-1);
	while ((tmp = follow_path(new, arg, map, tmp)) != arg->end && tmp)
		new->path_list[i++] = tmp->room;
	new->weight = i + 1;
	arg->sum_path += i;
	new->path = way;
	new->path_list[i] = arg->end->room;
	(*map)->way[way] = new;
	return (0);
}

int		find_nbr_way(t_data_map **map, t_lemin *arg, t_linkstab *links, int f)
{
	int path;

	path = 0;
	while (links)
	{
		if (links->selected == 1)
		{
			if (arg->start->room == links->rooma->room
				|| arg->start->room == links->roomb->room)
			{
				if (check_way(arg, map, links, path) == 0)
				{
					if (stock_path(map, arg, links, path) == -1)
						return (-1);
					path++;
				}
				if (path == f)
					return (path);
			}
		}
		links = links->next;
	}
	return (path);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuarez- <bsuarez-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:50:10 by bsuarez-          #+#    #+#             */
/*   Updated: 2020/01/20 12:33:36 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_node	*switch_room(t_linkstab *links, t_lemin *arg)
{
	t_node *room;

	if (links->rooma->room == arg->start->room)
		room = links->roomb;
	else
		room = links->rooma;
	return (room);
}

int		check_way(t_lemin *arg, t_data_map **map, t_linkstab *links, int way)
{
	t_node	*tmp;
	int		i;

	i = 0;
	tmp = switch_room(links, arg);
	while (i < way && (*map)->way[i]->path_list[0] != NULL)
	{
		if (ft_strcmp((*map)->way[i]->path_list[0], tmp->room) == 0)
			return (1);
		i++;
	}
	return (0);
}

int		check_follow(t_path *new, t_lemin *arg, t_node *links)
{
	int i;

	i = 0;
	if (ft_strcmp(links->room, arg->start->room) == 0)
		return (1);
	while (new->path_list[i] != NULL)
	{
		if (ft_strcmp(new->path_list[i], links->room) == 0)
			return (1);
		i++;
	}
	return (0);
}

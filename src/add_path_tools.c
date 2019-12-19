/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuarez- <bsuarez-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:50:10 by bsuarez-          #+#    #+#             */
/*   Updated: 2019/12/18 15:59:02 by bsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_node		*switch_room(t_linkstab *links, t_lemin *arg)
{
	t_node *room;

	if (links->rooma->room == arg->start->room)
		room = links->roomb;
	else
		room = links->rooma;
	return (room);
}

int			check_way(t_lemin *arg, t_data_map **map, t_linkstab *links, int way)
{
	t_node	*tmp;
	int i;
	int j;

	i = 0;
	tmp = switch_room(links, arg);
	while (i < way && (*map)->way[i]->path_list[0] != NULL)
	{
		j = 0;
		while ((*map)->way[i]->path_list[j] != NULL)
		{
			if (ft_strcmp((*map)->way[i]->path_list[j], tmp->room) == 0)
			{
				// printf("____[CHECK_WAY]-[%s]-[%s]\n", tmp->room, (*map)->way[i]->path_list[0]);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int 		check_follow(t_path *new, t_lemin *arg, t_node *links)
{
	int i;

	i = 0;
	if (ft_strcmp(links->room, arg->start->room) == 0)
		return (1);
	while (new->path_list[i] != NULL)
	{
		// printf ("*******{%s}\n", new->path_list[i]);
		// printf ("X*******{%s}\n", links->room);
		if (ft_strcmp(new->path_list[i], links->room) == 0)
			return (1);
		i++;
	}
	return (0);
}

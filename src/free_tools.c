/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuarez- <bsuarez-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 14:46:07 by bsuarez-          #+#    #+#             */
/*   Updated: 2020/01/21 14:51:35 by bsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_data_map		*return_delete(t_data_map *map, char *line)
{
	ft_strdel(&line);
	return (map);
}

void			free_node(t_node *node)
{
	t_node	*tmp;

	tmp = node;
	while (tmp != NULL)
		tmp = tmp->hash_next;
	while (node)
	{
		tmp = node->hash_next;
		ft_strdel(&node->room);
		free(node);
		node = tmp;
	}
}

void			free_map_next(t_data_map *map)
{
	int				j;
	t_linkstab		*tmp;

	j = 0;
	tmp = map->links;
	while (tmp != NULL)
		tmp = tmp->next;
	while (map->links)
	{
		tmp = map->links->next;
		free(map->links);
		map->links = tmp;
	}
	while (map->way[j])
	{
		free(map->way[j]->path_list);
		free(map->way[j]);
		j++;
	}
}

void			free_map(t_data_map *map)
{
	unsigned long	i;
	t_node			*tmp;

	i = 0;
	while (i < map->size)
	{
		tmp = map->list[i];
		if (tmp != NULL)
			free_node(tmp);
		i++;
	}
	free_map_next(map);
	free(map->list);
	free(map->way);
	free(map->links);
	free(map);
}

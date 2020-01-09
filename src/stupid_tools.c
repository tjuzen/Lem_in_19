/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stupid_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:24:31 by tjuzen            #+#    #+#             */
/*   Updated: 2020/01/09 18:13:46 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_data_map			*init_arg(t_lemin *arg)
{
	t_data_map *map;

	if (!(map = createMap(500000, map)))
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
	return (map);
}

t_data_map	*return_delete(t_data_map	*map, char *line)
{
	ft_strdel(&line);
	return (map);
}

void free_node(t_node* node)
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

void free_map(t_data_map* map)
{
	unsigned long	i;
	int prout;
	t_node			*tmp;
	t_linkstab		*tmp2;

	prout = 0;
	i = 0;
	while (i < map->size)
	{
		tmp = map->list[i];
		if (tmp != NULL)
			free_node(tmp);
		i++;
	}
	tmp2 = map->links;
	while (tmp2 != NULL)
		tmp2 = tmp2->next;
	while (map->links)
	{
		tmp2 = map->links->next;
		free(map->links);
		map->links = tmp2;
	}
	while (map->way[prout])
	{
		free(map->way[prout]->path_list);
		free(map->way[prout]);
		prout++;
	}
    free(map->list);
	free(map->way);
	free(map->links);
    free(map);
}

int				exit_free(t_lemin *arg, t_data_map	*map)
{
	printf("ERROR\n");
	free_map(map);
	return (-1);
}

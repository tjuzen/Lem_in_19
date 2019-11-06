/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stupid_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:24:31 by tjuzen            #+#    #+#             */
/*   Updated: 2019/11/06 11:28:26 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_linkstab *lookuplink(t_data_map *map, t_node *a, t_node *b)
{
	t_linkstab *find;

	find = map->links;
	while (find->next)
	{
		if (find->in == a && find->out == b)
			return (find);
		find = find->next;
	}
	// find = map->links;
	// while (find->nexto)
	// {
	// 	if (find->out == a && find->in == b)
	// 		return (find);
	// 	find = find->nexto;
	// }
	// find = map->links;
	// while (find->nextfrom)
	// {
	// 	if (find->in == a && find->out == b)
	// 		return (find);
	// 	find = find->nextfrom;
	// }
	return (NULL);
}

t_data_map	*lstreturn_mallocerr(int value, t_lemin *arg, t_data_map *map)
{
	arg->malloc_error = value;
	return (map);
}

int				intreturn_mallocerr(int value, t_lemin *arg)
{
	arg->malloc_error = value;
	return (-1);
}

void			init_arg(t_lemin *arg)
{
	arg->ants = -1;
	arg->wrong_line = 0;
	arg->malloc_error = 0;
	arg->count_hash = 0;
	arg->totalrooms = 0;
	arg->totalinks = 0;
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
	unsigned long i;
	t_node *tmp;
	t_linkstab	*tmp2;

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
    free(map->list);
    free(map);
}

int				exit_free(t_lemin *arg, t_data_map	*map)
{
	if (arg->malloc_error == -1)
	{
		ft_putendl("error get_next_line!");
		free_map(map);
	}
	if (arg->malloc_error == 1)
	{
		ft_putendl("error malloc room! hihi");
		free(map->list);
		free(map->links);
		free(map);
	}
	if (arg->malloc_error == 2)
		ft_putendl("Wrong start or end!");
	if (arg->malloc_error == 3)
		ft_putendl("invalid file!");
	return (-1);
}

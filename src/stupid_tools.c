/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stupid_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:24:31 by tjuzen            #+#    #+#             */
/*   Updated: 2019/10/24 22:07:01 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_data_map	*lstreturn_mallocerr(int value, t_lemin *arg)
{
	arg->malloc_error = value;
	return (NULL);
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

void free_link(t_connect *link)
{
	t_connect	*tmp;

	tmp = link;
	while (tmp != NULL)
		tmp = tmp->next;
	while (link)
	{
		tmp = link->next;
		free(link);
		link = tmp;
	}
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
		free_link(node->link);
		ft_strdel(&node->room);
		free(node);
		node = tmp;
	}
}

void free_map(t_data_map* map)
{
	unsigned long i;
	t_node *tmp;

	i = 0;
	while (i < map->size)
	{
		tmp = map->list[i];
		if (tmp != NULL)
			free_node(tmp);
		i++;
	}
    free(map->list);
    free(map);
}

int				exit_free(t_lemin *arg, t_data_map	*map)
{
	printf("J'exit free\n");
	if (arg->malloc_error == -1)
	{
		ft_putendl("error get_next_line!");
		free_map(map);
	}
	if (arg->malloc_error == 1)
		ft_putendl("error malloc room!");
	if (arg->malloc_error == 2)
		ft_putendl("Wrong start or end!");
	if (arg->malloc_error == 3)
		ft_putendl("invalid file!");
	return (-1);
}

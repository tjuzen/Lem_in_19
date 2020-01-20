/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stupid_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:24:31 by tjuzen            #+#    #+#             */
/*   Updated: 2020/01/20 19:05:56 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_data_map		*init_arg(t_lemin *arg)
{
	t_data_map *map;

	map = NULL;
	if (!(map = createmap(500000, map)))
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
	arg->one = 0;
	arg->found = 0;
	arg->display_links = 0;
	arg->display_score = 0;
	return (map);
}

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

void			free_map(t_data_map *map)
{
	unsigned long	i;
	int				j;
	t_node			*tmp;
	t_linkstab		*tmp2;

	j = 0;
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
	while (map->way[j])
	{
		free(map->way[j]->path_list);
		free(map->way[j]);
		j++;
	}
	free(map->list);
	free(map->way);
	free(map->links);
	free(map);
}

int				exit_free(t_lemin *arg, t_data_map *map)
{
	arg->one = 1;
	ft_printf("ERROR\n");
	free_map(map);
	return (-1);
}

void			print_all_links(t_lemin *arg, t_linkstab *tmp)
{
	ft_printf("\n\n");
	ft_printf(BLUE "OUT "DEFAULT_COLOR);
	ft_printf(RED " IN "DEFAULT_COLOR);
	ft_printf(GREY " START ET END \n\n"DEFAULT_COLOR);
	while (tmp->next)
	{
		if (tmp->rooma == arg->end || tmp->rooma == arg->start)
		{
			ft_printf(GREY" %-5s "DEFAULT_COLOR, tmp->rooma->room );
		}
		else
		{
			if (tmp->rooma->type == 0)
				ft_printf(DEFAULT_COLOR" %-5s " DEFAULT_COLOR, tmp->rooma->room);
			else if (tmp->rooma->type == 'I')
				ft_printf(RED " %-5s "DEFAULT_COLOR, tmp->rooma->room);
			else if (tmp->rooma->type == 'O')
				ft_printf(BLUE " %-5s " DEFAULT_COLOR, tmp->rooma->room);
		}
		ft_printf(" ----   ");
		if (tmp->roomb == arg->end || tmp->roomb == arg->start)
		{
			ft_printf(GREY"  %-5s "DEFAULT_COLOR, tmp->roomb->room );
		}
		else
		{
			if (tmp->roomb->type == 0)
				ft_printf(DEFAULT_COLOR"  %-5s " DEFAULT_COLOR, tmp->roomb->room);
			else if (tmp->roomb->type == 'I')
				ft_printf(RED "  %-5s " DEFAULT_COLOR, tmp->roomb->room);
			else if (tmp->roomb->type == 'O')
				ft_printf(BLUE "  %-5s " DEFAULT_COLOR, tmp->roomb->room);
		}

		if (tmp->selected == 1)
		ft_printf(RED" %3i "DEFAULT_COLOR, tmp->weight);
		else
		ft_printf(BLUE" %3i "DEFAULT_COLOR, tmp->weight);
		if (tmp->inversed == 1)
		ft_printf(RED" inversed "DEFAULT_COLOR);
		else
		ft_printf(BLUE" inversed "DEFAULT_COLOR);
		if (tmp->isactive == 1)
			ft_printf(DEFAULT_COLOR" XXXX\n"DEFAULT_COLOR);
		else
			ft_printf("\n");
		tmp = tmp->next;
	}
	ft_printf("\n_______________________________________________\n\n");
}

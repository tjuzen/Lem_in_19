/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stupid_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:24:31 by tjuzen            #+#    #+#             */
/*   Updated: 2020/01/20 17:57:23 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_data_map			*init_arg(t_lemin *arg)
{
	t_data_map *map;

	map = NULL;
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
	arg->one = 0;
	arg->found = 0;
	arg->display_links = 0;
	arg->display_score = 0;
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
	arg->one = 1;
	printf("ERROR\n");
	free_map(map);
	return (-1);
}

void print_all_links(t_lemin *arg, t_linkstab *tmp)
{
	printf("\n\n");
	printf(BLUE "OUT "DEFAULT_COLOR);
	printf(RED " IN "DEFAULT_COLOR);
	printf(GREY " START ET END \n\n"DEFAULT_COLOR);
	while (tmp->next)
	{
		if (tmp->rooma == arg->end || tmp->rooma == arg->start)
		{
			printf(GREY" %-5s "DEFAULT_COLOR, tmp->rooma->room );
		}
		else
		{
			if (tmp->rooma->type == 0)
				printf(DEFAULT_COLOR" %-5s " DEFAULT_COLOR, tmp->rooma->room);
			else if (tmp->rooma->type == 'I')
				printf(RED " %-5s "DEFAULT_COLOR, tmp->rooma->room);
			else if (tmp->rooma->type == 'O')
				printf(BLUE " %-5s " DEFAULT_COLOR, tmp->rooma->room);
		}
		printf(" ----   ");
		if (tmp->roomb == arg->end || tmp->roomb == arg->start)
		{
			printf(GREY"  %-5s "DEFAULT_COLOR, tmp->roomb->room );
		}
		else
		{
			if (tmp->roomb->type == 0)
				printf(DEFAULT_COLOR"  %-5s " DEFAULT_COLOR, tmp->roomb->room);
			else if (tmp->roomb->type == 'I')
				printf(RED "  %-5s " DEFAULT_COLOR, tmp->roomb->room);
			else if (tmp->roomb->type == 'O')
				printf(BLUE "  %-5s " DEFAULT_COLOR, tmp->roomb->room);
		}

		if (tmp->selected == 1)
		printf(RED" %3i "DEFAULT_COLOR, tmp->weight);
		else
		printf(BLUE" %3i "DEFAULT_COLOR, tmp->weight);
		if (tmp->inversed == 1)
		printf(RED" inversed "DEFAULT_COLOR);
		else
		printf(BLUE" inversed "DEFAULT_COLOR);
		if (tmp->isactive == 1)
			printf(DEFAULT_COLOR" XXXX\n"DEFAULT_COLOR);
		else
			printf("\n");
		tmp = tmp->next;
	}
	printf("\n_______________________________________________\n\n");
}

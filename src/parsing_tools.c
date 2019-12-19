/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:47:12 by tjuzen            #+#    #+#             */
/*   Updated: 2019/12/19 15:55:53 by bsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int 	get_number_of_ants(char *line, t_lemin *arg)
{
	if (arg->ants == -1)
		arg->ants = ft_atoi(line);
	if (arg->ants <= 0)
		return (-1);
	return (0);
}

int		valid_end_start(int i, t_lemin *arg, char s)
{
	if (s == 'I')
	{
		i = arg->in;
		arg->in = 1;
	}
	if (s == 'O')
	{
		i = arg->out;
		arg->out = 1;
	}
	return (i);
}

int 	add_end_start(char *line, t_data_map **map, t_lemin *arg, char s)
{
	int i;

	i = valid_end_start(0, arg, s);
	while (i == 0)
	{
		get_next_line(0, &line, 1);
		if (!line)
			return (-1);
		if (is_room(line, arg) == 1)
		{
			i++;
			add_room(map, line, s, arg);
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (0);
}

int		max_path(t_lemin *arg, t_data_map **map)
{
	t_linkstab *links;
	int			end;
	int			tmp;
	double		turns;

	links = (*map)->links;
	tmp = 0;
	end = 0;
	while (links->next)
	{
		if (arg->start->room == links->rooma->room)
			tmp++;
		if (arg->end->room == links->rooma->room)
			end++;
		links = links->next;
	}
	printf ("START %i, END %i\n", tmp ,end);
	arg->max_path = ((tmp > end) ? end : tmp);
	tmp = arg->ants + arg->total_weight;
	printf ("TURNS %f, TMP %i\n", turns, tmp);
	turns = ((double)tmp / (double)arg->max_path) - (double)1;
	arg->nbr_round = turns;
	printf("total_weight: %d\nmax_path: %i\nants :%i\nNBR_ROUND %f\n", arg->total_weight, arg->max_path, arg->ants, arg->nbr_round);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:47:12 by tjuzen            #+#    #+#             */
/*   Updated: 2019/12/20 02:47:09 by bsuarez-         ###   ########.fr       */
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

int 	assign_ants(t_lemin *arg, int i, t_path *way)
{
	t_ants *walker;

	printf("ants: %i weight: %i\n", i, way->weight);
	if (!(walker = ft_memalloc(sizeof(t_ants))))
		return (-1);
	walker->nbr = i;
	walker->nrj = way->weight;
	walker->path = way->path;
	walker->room = 0;
	if (arg->army == NULL)
		arg->army = walker;
	else
	{
		walker->next = arg->army;
		arg->army = walker;
	}
	return (0);
}

int 	is_army_empty(t_lemin *arg)
{
	t_ants *list;

	list = arg->army;
	while (list)
	{
		if (list->nrj > 0)
			return (0);
		list = list->next;
	}
	return (1);
}

int 	find_short(t_path **way, t_lemin *arg, int path, int i)
{
	int j;
	int l;
	int k;
	t_ants *list;

	list = arg->army;
	j = 0;
	l = INFINITE;
	while (way[j])
	{
		if (way[j]->weight < l)
		{
			printf("_________________%i____________%i\n", way[j]->weight, l);
			l = way[j]->weight;
			k = j;
		}
		// if (arg->ants - i + way[j]->weight < way[j + 1]->weight)
		// 	return (0);
		j++;
	}
	printf("_________________  ____________%i\n", k);
	return (k);
}

int		gives_order(t_lemin *arg, t_path **way, int path)
{
	int i;
	int j;
	int l;
	int round;
	t_ants *list;

	i = arg->ants;
	j = 0;
	l = 0;
	round = 0;
	while (i > 0)
	{
		if ((i / path) + way[j % path]->weight < (int)arg->nbr_round + 1)
		{
			if ((assign_ants(arg, i--, way[j % path])) == -1)
				return (-1);
		}
		j++;
	}
	j = 0;
	i = 0;
	while (is_army_empty(arg) == 0)
	{
		list = arg->army;
		if (l > 0)
			printf ("[LINE]: %i ", l);
		 l++;
		while (j < path * round)
		{
			// printf("koukou: j: %i    path: %i     round : %i\n", j, path, round);
			if (list->nrj > 0/* && list->nbr / path*/)
			{
				list->nrj--;
				printf ("L%i-%s ", list->nbr, way[list->path]->path_list[list->room++]);
			}
			if (list->nbr == arg->ants)
			{
				// printf("koukou: derniere fourmis\n");
				break ;
			}
			j++;
			list = list->next;
		}
		// if (is_army_empty(arg) == 1)
		// 	break;
		printf ("\n");
		j = 0;
		round -= -1;
		// if (list->nbr == arg->ants && list->nrj == 0)
		// 	return (l);
	}
	return (0);
}

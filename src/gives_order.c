/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gives_order.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuarez- <bsuarez-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 13:28:30 by bsuarez-          #+#    #+#             */
/*   Updated: 2020/01/21 15:03:52 by bsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		assign_ants(t_lemin *arg, int i, t_path *way, int turn)
{
	t_ants *walker;

	if (!(walker = ft_memalloc(sizeof(t_ants))))
		return (-1);
	walker->nbr = i;
	walker->nrj = way->weight;
	walker->path = way->path;
	walker->room = 0;
	walker->turn = turn;
	if (arg->army == NULL)
		arg->army = walker;
	else
	{
		walker->next = arg->army;
		arg->army = walker;
	}
	return (0);
}

int		send_ants(t_path **way, t_ants *list, int l, t_lemin *arg)
{
	int modif;
	int check;

	modif = 0;
	check = 0;
	while (list)
	{
		if (list->nrj > 0 && list->turn <= l)
		{
			if (check == 0)
			{
				if (arg->display_score == 1)
					ft_printf("[LINE]: %02i ", l);
				check = 1;
			}
			list->nrj--;
			ft_printf("L%i-%s ", list->nbr,
			way[list->path]->path_list[list->room++]);
			modif = 1;
		}
		list = list->next;
	}
	if (check == 1)
		ft_printf("\n");
	return (modif);
}

int		gives_order(t_lemin *arg, t_path **way, int path)
{
	int		l;
	int		modif;
	t_ants	*list;
	t_ants	*tmp;

	l = 1;
	modif = 1;
	if (prepare_ants(arg, 1, way, path) == -1)
		return (-1);
	while (modif == 1)
	{
		list = arg->army;
		modif = 0;
		modif = send_ants(way, list, l++, arg);
	}
	tmp = arg->army;
	while (tmp != NULL)
		tmp = tmp->next;
	while (arg->army)
	{
		tmp = arg->army->next;
		free(arg->army);
		arg->army = tmp;
	}
	return (0);
}

int		resolve_map(t_lemin *arg, t_data_map **map, int path)
{
	int	i;

	i = 1;
	if (arg->one == 1)
	{
		ft_printf("[LINE]01: ");
		while (i++ <= arg->ants)
			ft_printf("L%i-%s ", i, arg->end->room);
		ft_printf("\n");
	}
	else
	{
		arg->max_path = path;
		if (find_nbr_way(map, arg, (*map)->links, path) == -1)
			return (-1);
		if (gives_order(arg, (*map)->way, path) == -1)
			return (-1);
	}
	return (0);
}

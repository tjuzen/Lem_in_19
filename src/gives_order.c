/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gives_order.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuarez- <bsuarez-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 13:28:30 by bsuarez-          #+#    #+#             */
/*   Updated: 2020/01/09 17:21:16 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int 	assign_ants(t_lemin *arg, int i, t_path *way, int turn)
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

int 	prepare_ants(t_lemin *arg, int i, t_path **way, int path)
{
	int j;
	int turn;
	int ind = 0;
	int modif = 0;

	turn = 0;
	while (i <= arg->ants)
	{
		j = 0;
		modif = 0;
		while (j < path && i <= arg->ants)
		{
			if (turn + way[j]->weight <= (int)arg->nbr_round + 1)
			{
				if ((assign_ants(arg, i++, way[j], turn + 1)) == -1)
					return (-1);
				ind = j;
				printf ("  antscount %i turn %i path[%i] %i  NBR_ROUND: %i\n", i, turn, way[j]->path, way[j]->weight, (int)arg->nbr_round + 1);
			}
			else
			{
				modif++;
				if (modif == path)
				{
					if ((assign_ants(arg, i++, way[ind], turn + 1)) == -1)
						return (-1);
					printf ("_antscount %i turn %i path[%i] %i  NBR_ROUND: %i |  path: %i ind :%i\n", i, turn, way[ind]->path, way[ind]->weight, (int)arg->nbr_round + 1, path, ind);
				}
			}
			j++;
		}
		turn++;
	}
	return (0);
}

int		send_ants(t_lemin *arg, t_path **way, t_ants *list, int l)
{
	int modif;
	t_ants tmp;

	modif = 0;
	while (list)
	{
		if (list->nrj > 0 && list->turn <= l)
		{
			list->nrj--;
			printf ("L%i-%s ", list->nbr, way[list->path]->path_list[list->room++]);
			modif = 1;
		}
		// if (list->nrj == 0)
		// {
		// 	list->next = arg->army;
		// 	free(list);
		// }
		list = list->next;
	}
	return (modif);
}

int		gives_order(t_lemin *arg, t_path **way, int path)
{
	int l;
	int modif;
	t_ants *list;
	t_ants *tmp;

	l = 1;
	modif = 1;
	if (prepare_ants(arg, 1, way, path) == -1)
		return (-1);
	while (modif == 1)
	{
		list = arg->army;
		modif = 0;
		// if (l < arg->nbr_round + 1)
			printf ("[LINE]: %02i ", l);
		modif = send_ants(arg, way, list, l);
		// if (l < arg->nbr_round + 1)
			printf ("\n");
			// printf ("\n");
		l++;
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
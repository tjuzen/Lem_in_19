/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuarez- <bsuarez-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 11:07:02 by bsuarez-          #+#    #+#             */
/*   Updated: 2020/01/06 18:34:59 by bsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int 	bellwhile_ford(t_linkstab *link, t_lemin *arg)
{
	int did_change;
	int finished = 0;

	did_change = 0;
	while (link->next)
	{
		if (link->isactive == 1)
		{
			if (link->rooma->weight != INFINITE
				&& link->rooma->weight + link->weight < link->roomb->weight
				&& link->roomb != arg->start && link->isactive == 1
				&& link->rooma != arg->end)
			{
				link->roomb->weight = link->weight + link->rooma->weight;
				link->roomb->parent = link->rooma;
				// printf("%s%c a comme parent  %s%c\n", link->roomb->room, link->roomb->type, link->roomb->parent->room, link->roomb->parent->type);
				did_change = 1;
			}
		}
		link = link->next;
	}
	return (did_change == 0) ? 666 : 1;
}

double 		cost_path(t_lemin *arg, int nbr)
{
	int 	tmp;
	double 	turns;

	tmp = arg->ants + arg->total_weight;
	// printf(" suce %i\n", tmp);
	printf("hahahaha %i\n", nbr);
	// printf ("TURNS %f, TMP %i\n", turns, tmp);
	turns = ((double)tmp / (double)nbr) - 1.0;
	arg->nbr_round = turns;
	printf("total_weight: %d\nmax_path: %i\nants :%i\n", arg->total_weight, arg->max_path, arg->ants);
	// printf(" ici ici %f\n", turns);
	return (turns);
}


int reset(t_data_map **map, t_lemin *arg, t_linkstab *links)
{
	t_node *a;
	t_node *b;

	while (links->next)
	{
		a = lookup((*map), links->rooma->key, links->rooma->room);
		b = lookup((*map), links->roomb->key, links->roomb->room);
		if (a)
		{
			a->weight = INFINITE;
			a->parent = NULL;
			if (a->in)
			{
				a->in->weight = INFINITE;
				a->in->parent = NULL;
			}
			if (a->out)
			{
				a->out->weight = INFINITE;
				a->out->parent = NULL;
			}
		}
		if (b)
		{
			b->weight = INFINITE;
			b->parent = NULL;
			if (b->in)
			{
				b->in->weight = INFINITE;
				b->in->parent = NULL;
			}
			if (b->out)
			{
				b->out->weight = INFINITE;
				b->out->parent = NULL;
			}
		}
		links = links->next;
	}
	arg->start->weight = 0;
	return (1);
}

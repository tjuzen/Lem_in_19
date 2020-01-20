/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuarez- <bsuarez-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 11:07:02 by bsuarez-          #+#    #+#             */
/*   Updated: 2020/01/20 18:47:41 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		bellwhile_ford(t_linkstab *link, t_lemin *arg)
{
	int did_change;

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
				did_change = 1;
			}
		}
		link = link->next;
	}
	return (did_change == 0) ? 666 : 1;
}

double	cost_path(t_lemin *arg, int nbr)
{
	int		tmp;
	double	turns;

	arg->found++;
	tmp = arg->ants + arg->total_weight;
	turns = ((double)tmp / (double)nbr) - 1.0;
	if (turns < arg->nbr_round)
		arg->nbr_round = turns;
	return (turns);
}

void	reset_a(t_node *a)
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

void	reset_b(t_node *b)
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

int		reset(t_lemin *arg, t_linkstab *links)
{
	while (links->next)
	{
		reset_a(links->rooma);
		reset_b(links->roomb);
		links = links->next;
	}
	arg->start->weight = 0;
	return (1);
}

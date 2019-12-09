/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:51:04 by tjuzen            #+#    #+#             */
/*   Updated: 2019/12/09 13:45:16 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void print_all_links(t_data_map *map, t_lemin *arg, t_linkstab *tmp)
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
}

void print_colors(t_data_map *map, t_lemin *arg, t_linkstab *tmp)
{
	if (tmp->rooma == arg->end || tmp->rooma == arg->start)
	{
		printf(GREY" %s "DEFAULT_COLOR, tmp->rooma->room );
	}
	else
	{
		if (tmp->rooma->type == 0)
			printf(DEFAULT_COLOR" %s " DEFAULT_COLOR, tmp->rooma->room);
		else if (tmp->rooma->type == 'I')
			printf(RED " %s "DEFAULT_COLOR, tmp->rooma->room);
		else if (tmp->rooma->type == 'O')
			printf(BLUE " %s " DEFAULT_COLOR, tmp->rooma->in->room);
	}
	printf(" ----");
	if (tmp->roomb == arg->end || tmp->roomb == arg->start)
	{
		printf(GREY"  %s "DEFAULT_COLOR, tmp->roomb->room );
	}
	else
	{
		if (tmp->roomb->type == 0)
			printf(DEFAULT_COLOR"  %s " DEFAULT_COLOR, tmp->roomb->room);
		else if (tmp->roomb->type == 'I')
			printf(RED "  %s " DEFAULT_COLOR, tmp->roomb->room);
		else if (tmp->roomb->type == 'O')
			printf(BLUE "  %s " DEFAULT_COLOR, tmp->roomb->in->room);
	}
	printf("\n");
}

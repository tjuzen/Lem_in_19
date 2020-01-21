/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all_links.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuarez- <bsuarez-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 14:43:43 by bsuarez-          #+#    #+#             */
/*   Updated: 2020/01/21 14:44:03 by bsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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

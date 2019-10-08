/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:28:27 by tjuzen            #+#    #+#             */
/*   Updated: 2019/10/08 14:41:52 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void get_number_of_ants(t_lemin *arg)
{
	char	*line;

	get_next_line(0, &line);
	if (arg->ants == -1)
		arg->ants = ft_atoi(line);
	ft_strdel(&line);
}

void init_arg(t_lemin *arg)
{
	arg->ants = -1;
}

t_list_lemin	*add_link_front(t_list_lemin *mylist, char *str, int state)
{
	t_list_lemin		*tmp;
	char				**split;

	split = ft_strsplit(str, ' ');
	tmp = ft_memalloc(sizeof(t_list_lemin));
	if (tmp)
	{
		ft_printf("0 %s\n1 %s\n2 %s\n\n", split[0], split[1], split[2]);
		tmp->state = state;
		tmp->room = ft_atoi(split[0]);
		tmp->x = ft_atoi(split[1]);
		tmp->y = ft_atoi(split[2]);
		tmp->next = mylist;
	}
	else
		return (NULL);
	return (tmp);
}

t_list_lemin *get_infos(char *line, t_list_lemin *mylist)
{
	if (ft_strstr(line, "start"))
	{
		get_next_line(0, &line);
		mylist = add_link_front(mylist, line, 0);
		return (mylist);
	}
	if (ft_strstr(line, "end"))
	{
		get_next_line(0, &line);
		mylist = add_link_front(mylist, line, 1);
		return (mylist);
	}
	mylist = add_link_front(mylist, line, 2);
	return (mylist);
}

void		print_delete(t_list_lemin *mylist, t_lemin *arg)
{
	t_list_lemin	*tmp;

	tmp = mylist;
	ft_printf("\n\nNubers of ants = %i\n", arg->ants);
	while (tmp != NULL)
	{
		ft_printf("State:%i\nRoom:%i\nX:%i\nY:%i\n\n", tmp->state, tmp->room, tmp->x, tmp->y);
		tmp = tmp->next;
	}
	while (mylist)
	{
		tmp = mylist->next;
		free(mylist);
		mylist = tmp;
	}
}

int main()
{
	char			*line;
	t_lemin			arg;
	t_list_lemin	*mylist;

	mylist = NULL;
	init_arg(&arg);
	get_number_of_ants(&arg);
	while (get_next_line(0, &line) > 0)
	{
		if (!(ft_strstr(line, "-")))
			if (!(mylist = get_infos(line, mylist)))
				return (-1);
		ft_strdel(&line);

	}
	print_delete(mylist, &arg);
	ft_strdel(&line);
	return (0);
}

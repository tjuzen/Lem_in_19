/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:28:27 by tjuzen            #+#    #+#             */
/*   Updated: 2019/10/12 20:33:33 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_list_lemin	*add_room(t_list_lemin *mylist, char *str, char state, t_lemin *arg)
{
	t_list_lemin		*tmp;
	char **splitted;

	if (!(splitted = ft_strsplit(str, ' ')))
		exit(EXIT_FAILURE);
	if (!(tmp = ft_memalloc(sizeof(t_list_lemin))))
		exit(EXIT_FAILURE);
	tmp->state = state;
	if (!(tmp->room = ft_strdup(splitted[0])))
			exit(EXIT_FAILURE);
	tmp->next = mylist;
	ft_freetab_str(splitted);
	return (tmp);
}

t_list_lemin	*reverse_list(t_list_lemin *mylist)
{
	t_list_lemin *prev;
	t_list_lemin *current;
	t_list_lemin *next;

	prev = NULL;
	next = NULL;
	current = mylist;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	mylist = prev;
	return (mylist);
}

void		print_delete(t_list_lemin *mylist, t_lemin *arg)
{
	t_list_lemin	*tmp;

	mylist = reverse_list(mylist);
	tmp = mylist;
	ft_printf("\nNubers of ants = %i\n\n", arg->ants);
	while (tmp != NULL)
	{
		ft_printf("Room : %s\nState : %i\n\n", tmp->room, tmp->state);
		tmp = tmp->next;
	}
	while (mylist)
	{
		tmp = mylist->next;
		ft_strdel(&mylist->room);
		free(mylist);
		mylist = tmp;
	}
}

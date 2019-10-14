/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:28:27 by tjuzen            #+#    #+#             */
/*   Updated: 2019/10/14 16:55:14 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_list_lemin	*add_room(t_list_lemin *mylist, char *str,
	char status, t_lemin *arg)
{
	t_list_lemin	*tmp;
	char			**splitted;

	if (!(splitted = ft_strsplit(str, ' ')))
	{
		arg->malloc_error = 1;
		return (NULL);
	}
	if (!(tmp = ft_memalloc(sizeof(t_list_lemin))))
	{
		arg->malloc_error = 1;
		ft_freetab_str(splitted);
		return (NULL);
	}
	tmp->status = status;
	if (!(tmp->room = ft_strdup(splitted[0])))
	{
		arg->malloc_error = 1;
		ft_freetab_str(splitted);
		print_delete(tmp, arg);
		return (NULL);
	}
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

void			delete(t_list_lemin *mylist, t_lemin *arg)
{
	t_list_lemin	*tmp;

	tmp = mylist;
	while (tmp != NULL)
		tmp = tmp->next;
	while (mylist)
	{
		tmp = mylist->next;
		ft_strdel(&mylist->room);
		free(mylist);
		mylist = tmp;
	}
}

void			print_delete(t_list_lemin *mylist, t_lemin *arg)
{
	t_list_lemin	*tmp;

	tmp = mylist;
	ft_printf("Nubers of ants = %i\n\n", arg->ants);
	while (tmp != NULL)
	{
		ft_printf("Room     :   %s\nStatus   :   %c\n\n",
		tmp->room, tmp->status);
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

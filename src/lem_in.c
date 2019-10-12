/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:28:27 by tjuzen            #+#    #+#             */
/*   Updated: 2019/10/12 21:41:57 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void			init_arg(t_lemin *arg)
{
	arg->ants = -1;
	arg->wrong_line = 0;
	arg->malloc_error = 0;
}

int exit_free(t_lemin *arg, t_list_lemin *mylist)
{
	if (arg->malloc_error == 2)
	{
		ft_printf("je suis ici");
		print_delete(mylist, arg);
	}
	return (-1);
}

int				main()
{
	t_lemin			arg;
	t_list_lemin	*mylist;

	init_arg(&arg);
	mylist = read_file(&arg);
	if (arg.malloc_error != 0)
		return (exit_free(&arg, mylist));
	mylist = reverse_list(mylist);
	print_delete(mylist, &arg);
	return (0);
}

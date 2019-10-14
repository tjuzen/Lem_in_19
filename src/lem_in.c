/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:28:27 by tjuzen            #+#    #+#             */
/*   Updated: 2019/10/14 16:37:35 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int				main(void)
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

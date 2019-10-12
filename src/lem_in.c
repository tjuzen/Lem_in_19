/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:28:27 by tjuzen            #+#    #+#             */
/*   Updated: 2019/10/12 20:30:07 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void init_arg(t_lemin *arg)
{
	arg->ants = -1;
	arg->wrong_line = 0;
}

int main()
{
	t_lemin			arg;
	t_list_lemin	*mylist;

	init_arg(&arg);
	mylist = read_file(&arg);
	print_delete(mylist, &arg);
	return (0);
}

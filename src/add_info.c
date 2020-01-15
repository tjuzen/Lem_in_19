/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuarez- <bsuarez-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 11:41:54 by bsuarez-          #+#    #+#             */
/*   Updated: 2020/01/15 15:58:23 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	add_it(t_lemin *arg, t_data_map **map, t_linkstab *newlink)
{
	if (newlink->rooma->status == 'I' && newlink->roomb->status == 'O')
	{
		arg->one = 1;
		newlink->roomb->parent = newlink->rooma;
	}
	if (newlink->roomb->status == 'I' && newlink->rooma->status == 'O')
	{
		arg->one = 1;
		newlink->rooma->parent = newlink->roomb;
	}
	if ((*map)->links == NULL)
		(*map)->links = newlink;
	else
	{
		newlink->next = (*map)->links;
		(*map)->links = newlink;
	}
}

t_linkstab 	*add_link_info(t_linkstab *link, t_node *a, t_node *b, int directed)
{
	link->rooma = a;
	link->roomb = b;
	link->weight = 1;
	link->isactive = 1;
	link->inversed = -1;
	link->selected = 0;
	link->fakeselected = 0;
	link->imintern = 0;
	if (!(a->to))
		a->to = link;
	else
	{
		link->nexto = a->to;
		a->to = link;
	}
	return (link);
}


int		add_link(t_data_map **map, char *line, t_lemin *arg, int directed)
{
	char			**splitted;
	t_linkstab		*newlink;
	t_linkstab		*otherlink;
	t_node			*rooma;
	t_node			*roomb;

	if (!(splitted = ft_strsplit(line, '-')))
		return (-1);
	rooma = lookup(*map, hashCode(splitted[0]), splitted[0]);
	roomb = lookup(*map, hashCode(splitted[1]), splitted[1]);
	if (!(rooma) || !(roomb) || !(newlink = ft_memalloc(sizeof(t_linkstab)))
		|| !(otherlink = ft_memalloc(sizeof(t_linkstab))))
	{
		ft_freetab_str(splitted);
		return (-1);
	}
	if (directed == 1) // si a<->b
	{
		add_it(arg, map, add_link_info(newlink, rooma, roomb, 1));
		add_it(arg, map, add_link_info(otherlink, roomb, rooma, 2));
		newlink->reversed = otherlink;
		otherlink->reversed = newlink;
	}
	arg->totalinks++;
	ft_freetab_str(splitted);
	return (0);
}

int 	add_room_info(t_data_map **map, char stat, t_lemin *arg, t_node *new)
{
	new->in = NULL;
	new->out = NULL;
	new->parent = NULL;
	new->paths = NULL;
	new->just_dup = 0;
	if (stat == 'I')
	{
		new->weight= 0;
		arg->start = new;
	}
	else
	{
		if (stat == 'O')
			arg->end = new;
		new->weight = INFINITE;
	}

	if ((*map)->list[new->key % (*map)->size] == NULL)
		(*map)->list[new->key % (*map)->size] = new;
	else
	{
		new->hash_next = (*map)->list[new->key % (*map)->size];
		(*map)->list[new->key % (*map)->size] = new;
	}
	return (0);
}

int		add_room(t_data_map **map, char *str, char stat, t_lemin *arg)
{
	t_node			*new;
	char			**splitted;

	if (!(splitted = ft_strsplit(str, ' ')))
		return (-1);
	if (!(new = ft_memalloc(sizeof(t_node))))
	{
		ft_freetab_str(splitted);
		return (-1);
	}
	if (!(new->room = ft_strdup(splitted[0])))
	{
		ft_freetab_str(splitted);
		free(new);
		return (-1);
	}
	arg->totalrooms++;
	ft_freetab_str(splitted);
	new->key = hashCode(new->room);
	new->duplicated = 0;
	new->status = stat;
	new->type = 0;
	return (add_room_info(map, stat, arg, new));
}

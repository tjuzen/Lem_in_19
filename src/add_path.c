/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuarez- <bsuarez-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:29:06 by bsuarez-          #+#    #+#             */
/*   Updated: 2019/12/20 06:11:02 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_node		*follow_path(t_path *new, t_lemin *arg, t_data_map **map, t_node *tmp)
{
	t_linkstab *links;

	links = (*map)->links;
	if (new->path_list[0] == NULL)
		return (tmp);
	while (links->next)
	{
		if (links->selected == 1)
		{
			if ((ft_strcmp(links->rooma->room, tmp->room) == 0)
				&& check_follow(new, arg, links->roomb) == 0)
			{
					return (tmp = links->roomb);
					// printf ("1111111______[%s]-[%s]________\n", links->rooma->room, links->roomb->room);
			}
			if ((ft_strcmp(links->roomb->room, tmp->room) == 0)
				&& (check_follow(new, arg, links->rooma) == 0))
			{
					return (tmp = links->rooma);
					// printf ("22222________[%s]-[%s]________\n", links->rooma->room, links->roomb->room);
			}
		}
		links = links->next;
	}
	return (tmp);
}

int 		stock_path(t_data_map **map, t_lemin *arg, t_linkstab *links, int way)
{
	t_path	*new;
	t_node	*tmp;
	int i;

	i = 0;
	tmp = switch_room(links, arg);
	if (!(new = ft_memalloc(sizeof(t_path))))
		return (-1);
	if (!(new->path_list = ft_memalloc(sizeof(char**) * 5000)))
		return (-1);
	while ((tmp = follow_path(new, arg, map, tmp)) != arg->end)
	{
		if (!(new->path_list[i++] = ft_strdup(tmp->room)))
		{
			free(new);
			return (-1);
		}
		ft_printf(" [%s]", new->path_list[i-1]);
	}
	printf("_____weight: %i\n", i);
	// printf("_____new: %s\n", new->path_list[i]);
	new->weight = i + 1;
	arg->sum_path += i;
	new->path = way;
	new->path_list[i] = arg->end->room;
	ft_printf(" [%s]", new->path_list[i]);
	// printf("_____new: %s\n", new->path_list[i]);
	(*map)->way[way] = new;
	return (0);
}

int			find_nbr_way(t_data_map **map, t_lemin *arg, t_linkstab *links)
{
	int path;

	path = 0;
	while (links->next)
	{
		if (links->selected == 1)
		{
			if (arg->start->room == links->rooma->room
				|| arg->start->room == links->roomb->room)
			{
				// printf("[CHECK1]-");
				// printf ("[%s]-[%s]\n", links->rooma->room, links->roomb->room);
				if (check_way(arg, map, links, path) == 0)
					if (stock_path(map, arg, links, path++) == -1)
						return (-1);
					printf(":i %i\n", path - 1);
			}
		}
		links = links->next;
	}
	// printf ("YOOOOOOOOOWWWWWWWWW\nYOOOOOOOOOOOOOOOWWWWOWOWOWOWWWWWWW");
	printf ("OOOOOwwww: %i\n", path);
	return (path);
}

void		print_way(t_data_map **map, t_lemin *arg, int nbr, int ant)
{
	int i;
	int j;

	i = 0;
	while (i < nbr)
	{
		printf("WAY:--");
		j = 0;
		while (j <= (*map)->way[i]->weight)
			printf("[%s]", (*map)->way[i]->path_list[j++]);
		i++;
		printf("\n");
	}
}

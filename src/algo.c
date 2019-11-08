/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:51:04 by tjuzen            #+#    #+#             */
/*   Updated: 2019/11/08 19:30:56 by bsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		update_links(t_data_map *map, t_lemin *arg)
{
	t_linkstab *link;

	link = map->links;

}

void 		multiply_room(t_data_map *map, t_lemin *arg, int y)
{
	t_path	*path;
	char	*in;
	char	*out;
	char	*newroom;

	in = ft_strdup("#i-");
	out = ft_strdup("#o-");
	path = map->wayList[y];
	while (path->x_next)
	{
		if (path->room->status == 'X')
		{
			newroom = ft_strjoin(in, path->room->room);
			map = add_room(map, newroom, 'X', arg);
			newroom = ft_strjoin(out, path->room->room);
			map = add_room(map, newroom, 'X', arg);
		}
		path = path->x_next;
	}
}

t_data_map	*add_path(t_data_map *map, t_node *tmp, t_lemin *arg, int y)
{
	t_path 	*newpath;

	if (!(newpath = ft_memalloc(sizeof(t_path))))
	{
		arg->malloc_error = 1;
		return (map);
	}
	newpath->room = tmp;
	if (map->wayList[y] == NULL)
		map->wayList[y] = newpath;
	else
	{
		newpath->x_next = map->wayList[y];
		map->wayList[y] = newpath;
	}
	return (map);
}

void  modify_path(t_data_map *map, t_lemin *arg)
{
	t_node *room = arg->end;
	t_linkstab *link;

	link = room->to;
	while (link)
	{
		if (link->out->parent == link->in)
		{
			link->weight = -1;
			link = link->in->to;
		}
		else
			link = link->nexto;
	}
}

void print_all_links(t_data_map *map, t_path *path, t_linkstab *tmp, int i)
{
	printf("\n");
	if (i == 2)
	{
		while (path->x_next)
		{
			printf("|%s|\n", path->room->room);
			path = path->x_next;
		}
	}
	if (i == 1)
	{
		while (tmp->next)
		{
			printf("|%s-%s weight %5i|\n", tmp->in->room, tmp->out->room, tmp->weight);
			tmp = tmp->next;
		}
	}
	if (i == 0)
	{
		while (tmp->next)
		{
			printf("|%s w:%5i|\n", tmp->in->room, tmp->in->weight);
			tmp = tmp->next;
		}
	}
}

void 	print_path(t_data_map *map, t_lemin *arg, t_node *room)
{
	if (room->parent)
		print_path(map, arg, room->parent);
	if (room->status == 'I')
		printf("\n\nPATH IS OK\n");
	// map = add_path(map, room, arg);
	printf(" |%s|:%i\n", room->room, room->weight);
}

void	follow(t_data_map *map, t_lemin *arg, t_node *room, int y)
{
	// map = add_path(map, room, arg, y);
	if (room->parent)
		follow(map, arg, room->parent, y);
	map = add_path(map, room, arg, y);
}

t_linkstab	*add_opti(t_node *room_a, t_node *room_b, t_linkstab *tab)
{
	t_linkstab *test = room_b->from;
	if (!(test))
		return (NULL);
	if (tab == NULL)
		tab = test;
	else
	{
		test->nextfrom = tab;
		tab = test;
	}
	return (test);
}

int bellman_peugeot(t_data_map *map, t_lemin *arg)
{
	t_linkstab	*link;
	int			countrooms;
	t_linkstab *opti;
	t_linkstab *tmp;

	printf("\n");
	countrooms = arg->totalrooms;
	opti = arg->start->from;
	link = opti;
	while (--countrooms > 0)
	{
		// printf("---\n");
		while (link->next)
		{
			// if (link->weight == -1 && ((link->in->status == 'I' || link->in->status == 'O') || (link->out->status == 'O')))
			// 	link = link->next;
			if (link->in->weight != INT_MAX - 10 && link->in->weight + link->weight < link->out->weight)
			{
				printf("|######%s-%s weight %5i|\n", link->in->room, link->out->room, link->weight);
				link->out->weight = link->weight + link->in->weight;
				link->out->parent = link->in;
				link->in->child = link->out;
				// if (link->out->from->out != link->in)
				// 	opti = add_opti(link->in, link->out, opti);
			}
			link = link->next;
		}
		link = map->links;
		// link = opti;
		// opti = NULL;
	}

	return (1);
}

int find_path(t_data_map *map, t_lemin *arg)
{
	t_linkstab *prout = map->links;
	// print_all_links(map, arg, prout);
	prout = map->links;
	bellman_peugeot(map, arg);

	// print_path(map, arg, arg->end);
	printf("\n");
	modify_path(map, arg);
	add_path(map, arg->start, arg, 0);
	follow(map, arg, arg->end, 0);
	multiply_room(map, arg, 0);
	print_path(map, arg, arg->end);
	print_all_links(map, *map->wayList, map->links, 1);
	print_all_links(map, *map->wayList, map->links, 0);
	print_all_links(map, *map->wayList, map->links, 2);


	// print_way(map, arg, map->walker);
	// bellman_peugeot(map, arg);
	// follow(map, arg, arg->end, 1);
	// print_path(map, arg, arg->end);
	// print_all_links(map, *map->wayList, map->links, 1);
	// print_all_links(map, *map->wayList, map->links, 0);
	// print_all_links(map, map->wayList[0], map->links, 2);
	// print_all_links(map, map->wayList[1], map->links, 2);


	return (1);
}

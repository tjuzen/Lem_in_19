/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:51:04 by tjuzen            #+#    #+#             */
/*   Updated: 2019/11/15 17:32:01 by bsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void print_theo(t_data_map *map)
{
	t_node *a = lookup(map, hashCode("a"), "a");


	while (a->to)
	{
		// if (a->to->isactive)
		printf("$$$ %c-%s $$$\n", a->to->roomb->type, a->to->roomb->room);
		a->to = a->to->nexto;
	}
}

void print_all_links(t_data_map *map, t_lemin *arg, t_linkstab *tmp)
{
	printf("\n");
	while (tmp->next)
	{
		printf("%c%2s    ---    %c%2s%5i", tmp->rooma->type, tmp->rooma->room, tmp->roomb->type, tmp->roomb->room, tmp->weight);
		if (tmp->isactive == 1)
			printf(" XXXX");
		printf("\n");
		tmp = tmp->next;
	}
}

void 	print_path(t_data_map *map, t_lemin *arg, t_node *room, t_node *path)
{
	if (room->parent)
	{
		room->parent->path = room;
		print_path(map, arg, room->parent, path);
	}
	if (room->status == 'I')
		printf("\n\nPATH IS OK\n");
	if (room)
	{
		path->path = room;
		printf("|%s|", path->path->room);
		path = path->path;
		printf("|%s| ", room->room);
	}
}




int bellman_peugeot(t_data_map *map, t_lemin *arg)
{
	t_linkstab	*link;
	int			countrooms;

	countrooms = arg->totalrooms;
	link = map->links;

	while (--countrooms > 0 && link)
	{
		link = map->links;
		// printf("-----------\n");
		if (bellwhile_ford(link, arg) == 666)
			break;
	}
	// link = map->links;
	// while (link->next)
	// {
	// 	if (link->rooma->weight != INFINITE
	// 		&& link->rooma->weight + link->weight < link->roomb->weight)
	// 		printf("negcycle\n");
	// 	link = link->next;
	// }
	return (1);
}


int find_path(t_data_map *map, t_lemin *arg)
{
	int i;
	int p;
	t_node *way;

	p = 50;
	i = -1;
	while (--p)
	{
		bellman_peugeot(map, arg);
		way = give_name(map, ++i, arg);
		print_path(map, arg, arg->end, way);
		if (modify_path(map, arg) == -1)
			return (-1);
		duppp(map, arg);
		init_room_weight(map, arg, map->links);
	}

	// duppp(map, arg);
	// bellman_peugeot(map, arg);
	// print_path(map, arg, arg->end);
	// print_all_links(map, arg, map->links);
	// print_theo(map);
	return (1);
}

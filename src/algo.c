/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:51:04 by tjuzen            #+#    #+#             */
/*   Updated: 2019/12/20 06:41:55 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

// Augmente de 1 la valeur de selected pour A-B (== tmp) et B-A (== reversed)

int 	add_found_path(t_data_map *map, t_lemin *arg, t_node *room)
{
	t_linkstab *tmp;

	while (room)
	{
		tmp = lookuplink(map, room->parent, room);
		if (tmp)
		{
			// print_colors(tmp);
			arg->total_weight -= -1;
			tmp->selected++;
			if (tmp->reversed)
				tmp->reversed->selected++;
		}
		room = room->parent;
	}
	return (1);
}


int bellman_peugeot(t_data_map **map, t_lemin *arg)
{
	t_linkstab	*link;
	int			countrooms;

	countrooms = arg->totalrooms;
	link = (*map)->links;
	while (--countrooms > 0 && link)
	{
		link = (*map)->links;
		if (bellwhile_ford(link, arg) == 666)
			break;
	}
	// print_all_links(*map, arg, link);
	return (1);
}

t_linkstab *change_type(t_node *a)
{
	t_linkstab *find;

	find = a->to;
	while (find)
	{
		find->rooma = find->rooma->out;
		// printf("je change le lien %s%c - %s%c\n", find->rooma->room, find->rooma->type, find->roomb->room, find->roomb->type);
		find = find->nexto;
	}
	return (NULL);
}

void out_infos(t_data_map *map, t_lemin *arg, t_node *room, t_node *out)
{
	out->duplicated = 1;
	room->duplicated = 1;
	out->key = hashCode(out->room);
	out->paths = NULL;
	out->status = 'X';
	out->type = 'O';
	out->in = room;
	room->out = out;
	room->type = 'I';
	if (map->list[out->key % map->size] == NULL)
		map->list[out->key % map->size] = out;
	else
	{
		out->hash_next = map->list[out->key % map->size];
		map->list[out->key % map->size] = out;
	}
	change_type(room);
}

int intern_infos(t_data_map *map, t_lemin *arg, t_node *room, t_node *out)
{
	t_linkstab *intern;

	if (!(intern = ft_memalloc(sizeof(t_linkstab))))
	{
		arg->malloc_error = 1;
		ft_strdel(&out->room);
		free(out);
		return (-1);
	}
	intern->rooma = room;
	intern->roomb = out;
	intern->isactive = 1;
	intern->imintern = 1;
	intern->selected = 1;
	// intern->rooma->in = intern->roomb;
	// intern->roomb->out = intern->rooma;
	intern->roomb->parent = intern->rooma;
	// intern->rooma = out;
	// printf("\n\n				%s%c parent de %s%c\n", intern->roomb->parent->room, intern->roomb->parent->type, intern->roomb->room, intern->roomb->type);
	add_it(arg, &map, intern);
	return (1);
}

t_node *new_duplicate(t_data_map *map, t_lemin *arg, t_node *room)
{
	t_node *out;

	// if (room == arg->end)
	// 	return (room->parent);
	if (!(out = ft_memalloc(sizeof(t_node))))
	{
		arg->malloc_error = 1;
		return (NULL);
	}
	if (!(out->room = ft_strdup(room->room)))
	{
		arg->malloc_error = 1;
		free(out);
		return (NULL);
	}
	room->just_dup = 1;
	out_infos(map, arg, room, out);
	if (intern_infos(map, arg, room, out) == -1)
		return (NULL);
	// = lookuplinknode()
	// room->parent = out;
	// print_colors(link);
	// link->reversed->rooma = out;
	// link->roomb = link->;
	// printf("\n\n				%s%c parent de %s%c\n", room->parent->room, room->parent->type, room->room, room->type);

	// print_colors(link);
	return (out);
}

void        update_links(t_data_map *map, t_lemin *arg, t_linkstab *tmp)
{
	t_linkstab *link;

	link = tmp;
	while (link->next)
	{
        if (link->rooma->type == 'I' && link->rooma->out != link->roomb && link->rooma->just_dup == 1 && link->weight != 0)
		{
				link->rooma = link->rooma->out;
				link->rooma->just_dup = 0;
		}
		link = link->next;
	}
}

int duplicate_nodes(t_data_map *map, t_lemin *arg, t_node *room)
{
	// print_all_links(map, arg, map->links);
	while (room && room != arg->start)
	{
		// printf("Je suis room %s%c\n", room->room, room->type);
		// if (room->parent)
		// printf("avec %s%c\n", room->parent->room, room->parent->type);
		// if (room->status == 'X' && room->duplicated != 1)
		// 	if (new_duplicate(map, arg, room) == -1)
		// 		return (-1);

		if (room->parent->duplicated != 1 && room->parent && room->parent != arg->start)
		{
			new_duplicate(map, arg, room->parent);
			room->parent = room->parent->out;
		}
		room = room->parent;
	}
	// printf("je suis sorti\n");
	// update_links(map, arg, map->links);
	return (1);
}

void inverse_links(t_data_map *map, t_lemin *arg, t_node *room)
{
	t_linkstab	*tmp;
	t_node		*tmproom;

	while (room)
	{
		printf("ici %s%c\n", room->room, room->type);

		tmp = lookuplink(map, room->parent, room);
		if (tmp)
		{
			print_colors(tmp);
			tmproom = tmp->rooma;
			tmp->rooma = tmp->roomb;
			tmp->roomb = tmproom;
			tmp->weight *= -1;
			tmp->inversed = 1;
		}
		room = room->parent;
	}
}

void check_inversed(t_data_map *map, t_lemin *arg, t_linkstab *tmp)
{
	t_node		*tmproom;
	while (tmp->next)
	{
		if (tmp->selected > 1)
		{
			// print_colors(tmp);

			tmproom = tmp->rooma;
			tmp->rooma = tmp->roomb;
			tmp->roomb = tmproom;

			tmp->inversed = 0;
			if (tmp->imintern == 1)
				tmp->weight = 0;
			else
				tmp->weight = 1;
			arg->total_weight -= 1;
			tmp->selected = 0;
			// print_colors(tmp);

		}
		// if (tmp->reversed && tmp->reversed->selected > 1)
		// 	tmp->reversed->selected = 0;
		tmp = tmp->next;
	}
}

/*

1: Find the shortest path P1 from node s to node t
2: for i = 2,..., k
3: For node-disjoint paths, split the intermediate nodes of all Px where x < i (refer to Figure 3)
4: Replace each link of all Px where x < i with a reverse link of inverted link weight in the original graph
5: Find the shortest path Pi from node s to node t
6: Remove all overlapping links to get i disjoint paths Px where x ≤ i.

*/

int find_path(t_data_map **map, t_lemin *arg)
{
	t_node *tmp;
	double new;
	int nbr = 0;
	double old;
	int augmented;
	t_node *penis;




	augmented = 5;
	bellman_peugeot(map, arg);
	if (add_found_path((*map), arg, arg->end) == -1)
		return (-1);
	old = INFINITE;
	new = cost_path(arg, 1);
	if ((nbr = find_nbr_way(map, arg, (*map)->links)) == -1)
		return (-1);
	while (new < old)
	{
		// print_all_links(*map, arg, (*map)->links);
		printf("debut boucle\n");
		if (duplicate_nodes((*map), arg, arg->end) == -1)
			return (-1);
		inverse_links((*map), arg, arg->end);
		reset(map, arg, (*map)->links);
		// print_all_links(*map, arg, (*map)->links);
		printf("avant bellman\n");
		bellman_peugeot(map, arg);
		if (add_found_path((*map), arg, arg->end) == -1)
			return (-1);
	 	check_inversed((*map), arg, (*map)->links);
		// printf("Salut new %f\n", new);
		// printf("Salut lesamis %f\n", old);
		if ((nbr = find_nbr_way(map, arg, (*map)->links)) == -1)
			return (-1);
		printf("\n\n\nSalut lesamis %f | %f\n", new, old);
		old = new;
		new = cost_path(arg, nbr) + 1.0;
		printf("\n\n\nSalut lesputes %i | %f\n", (int)new, old);
		// print_all_links(*map, arg, (*map)->links);
		printf("fin boucle\n");
		// max_path(arg, map);
	}
	if (gives_order(arg, (*map)->way, nbr) == -1)
		return (-1);


		// penis = lookup(*map, hashCode("END"), "END");
		//
		// printf("hahahaha %s\n", penis->to->roomb->room);
		//
		//
		// printf("\n----------------\nLiaisons partant de %s-%c\n----------------\n", penis->room, penis->type);
		// while (penis->to)
		// {
		// 	// if (penis->to->isactive)
		// 	printf("%s-%c ", penis->to->roomb->room, penis->to->roomb->type);
		// 	penis->to = penis->to->nexto;
		// }
		// printf("\n");

	return (1);
}

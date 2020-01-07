/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:51:04 by tjuzen            #+#    #+#             */
/*   Updated: 2020/01/07 18:53:13 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

// Augmente de 1 la valeur de selected pour A-B (== tmp) et B-A (== reversed)

int checkeverything(t_data_map *map, t_lemin *arg, t_linkstab *tmp)
{
	t_node		*tmproom;
	int tmpweight = arg->total_weight;
	int oui = 0;
	tmproom = arg->end;

	while (tmproom)
	{
		tmp = lookuplink(map, tmproom->parent, tmproom);
		if (tmp)
		{
			if (tmp->imintern != 1)
			{
				arg->total_weight -= -1;
				tmp->fakeselected++;
			}
			if (tmp->reversed)
				tmp->reversed->fakeselected++;
		}
		if (tmproom->parent == arg->start)
			oui = 1;
		tmproom = tmproom->parent;
	}

if (oui)
{
	tmp = (*map).links;

	while (tmp->next)
	{
		if (tmp->fakeselected > 1)
		{
			if (tmp->imintern != 1)
				arg->total_weight--;
			tmp->fakeselected = 0;
		}
		tmp = tmp->next;
	}
}
else
{
	printf("\nhahaha\n");
	arg->total_weight = tmpweight;
	return (-1);
}
return (1);
}

int 	add_found_path(t_data_map *map, t_lemin *arg, t_node *room)
{
	int weight = 0;
	t_linkstab *tmp;

	while (room)
	{
		tmp = lookuplink(map, room->parent, room);
		if (tmp)
		{
			if (tmp->imintern != 1)
			{
				// arg->total_weight -= -1;
				tmp->selected++;
				weight++;
			}
			if (tmp->reversed)
				tmp->reversed->selected++;
		}
		if (room == arg->start)
			return 0;
		room = room->parent;
	}
	return (-1);
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
	return (1);
}

t_linkstab *change_type(t_node *a)
{
	t_linkstab *find;

	find = a->to;
	while (find)
	{
		find->rooma = find->rooma->out;
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
	intern->roomb->parent = intern->rooma;
	add_it(arg, &map, intern);
	return (1);
}

t_node *new_duplicate(t_data_map *map, t_lemin *arg, t_node *room)
{
	t_node *out;

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
	while (room && room != arg->start)
	{
		if (room->parent->duplicated != 1 && room->parent && room->parent != arg->start)
		{
			new_duplicate(map, arg, room->parent);
			room->parent = room->parent->out;
		}
		room = room->parent;
	}
	return (1);
}

void inverse_links(t_data_map *map, t_lemin *arg, t_node *room)
{
	t_linkstab	*tmp;
	t_node		*tmproom;

	while (room)
	{
		tmp = lookuplink(map, room->parent, room);
		if (tmp)
		{
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
			tmproom = tmp->rooma;
			tmp->rooma = tmp->roomb;
			tmp->roomb = tmproom;
			tmp->inversed = 0;
			if (tmp->imintern == 1)
				tmp->weight = 0;
			else
			{
				// arg->total_weight--;
				tmp->weight = 1;
			}
			tmp->selected = 0;
		}
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
	int found = 1;


	bellman_peugeot(map, arg);
	if (add_found_path((*map), arg, arg->end) == -1)
		return (-1);

	checkeverything((*map), arg, (*map)->links);

	old = INFINITE;
	new = cost_path(arg, 1);
	printf("\n\n\nSalut lesputes %f | %f\n", new, old);

	while (new < old)
	{
		if (duplicate_nodes((*map), arg, arg->end) == -1)
			return (-1);
		inverse_links((*map), arg, arg->end);
		reset(map, arg, (*map)->links);
		bellman_peugeot(map, arg);

		if (checkeverything((*map), arg, (*map)->links) == -1)
			break ;

		found++;
		old = new;
		new = cost_path(arg, found);
		printf("\n\n\nSalut lesputes %f | %f\n", new, old);

		if (new < old)
		{
			if (add_found_path((*map), arg, arg->end) == -1)
			{
				printf("\nje break\n");
				found--;
				break ;
			}
		 	check_inversed((*map), arg, (*map)->links);
		}
		else
			found--;

	}
	if ((nbr = find_nbr_way(map, arg, (*map)->links, found)) == -1)
		return (-1);
	if (gives_order(arg, (*map)->way, found) == -1)
		return (-1);
	return (1);
}

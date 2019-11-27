/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:51:04 by tjuzen            #+#    #+#             */
/*   Updated: 2019/11/27 13:32:58 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void check(t_data_map *map, t_lemin *arg, t_node *room)
{
	t_linkstab *tmp = map->links;

	while (tmp->next)
	{
		printf(" On parle de %s%c et %s%c\n", tmp->rooma->room, tmp->rooma->type, tmp->roomb->room, tmp->roomb->type);
		if (tmp->rooma->type == 'I' && tmp->roomb->type == 0)
		{
			// tmp->rooma = tmp->rooma->out;
		}
		if (tmp->rooma->type == 'O' && tmp->roomb->status == 'I')
		{
			// tmp->rooma = tmp->rooma->in;
		}
		tmp = tmp->next;
	}
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

void remove_inversed(t_data_map *map, t_lemin *arg)
{
	t_linkstab *tmp;
	t_linkstab *try;

	tmp = map->links;
	while (tmp->next)
	{
		if (tmp->rooma->type == 'I' && tmp->roomb->type == 'O')
		{
			tmp->isactive = 0;
			tmp->ISUSED = 0;
		}
		if (tmp->rooma->type == 'O' && tmp->roomb->type == 'I')
		{
			tmp->isactive = 0;
			tmp->ISUSED = 0;
		}
		tmp = tmp->next;
	}
	// boucle dans mes liens et remove (isactive = 0) les inversed + originales
}

int 	add_found_path(t_data_map *map, t_lemin *arg, t_node *room)
{
	printf("\n");

	t_linkstab *tmp;

	while (room)
	{
		printf("Room %s\n", room->room);
		tmp = lookuplink(map, room->parent, room);
		if (tmp)
		{
			// print_colors(map, arg, tmp);
			tmp->isactive = 0;
			tmp->rooma->theopath = tmp;
		}
		room = room->parent;
	}
	return (1);
}

int new_duplicate(t_data_map *map, t_lemin *arg, t_linkstab *link)
{
	t_node		*out;
	t_linkstab	*outin;

	if (!(out = ft_memalloc(sizeof(t_node))))
	{
		arg->malloc_error = 1;
		return (-1);
	}
	if (!(out->room = ft_strdup(link->roomb->room)))
	{
		arg->malloc_error = 1;
		free(out);
		return (-1);
	}
	if (!(outin = ft_memalloc(sizeof(t_linkstab))))
	{
		arg->malloc_error = 1;
		ft_strdel(&out->room);
		free(out);
		return (-1);
	}
	out->key = hashCode(out->room);
	out->status = 'X';
	out->isactive = 1;
	out->type = 'O';
	out->weight = 1;
	out->theopath = NULL;


	if (map->list[out->key % map->size] == NULL)
		map->list[out->key % map->size] = out;
	else
	{
		out->hash_next = map->list[out->key % map->size];
		map->list[out->key % map->size] = out;
	}

	outin->rooma = out;
	outin->roomb = link->roomb;
	outin->isactive = 1;
	outin->rooma->parentdup = outin->roomb;
	outin->roomb->type = 'I';
	printf("Nouveau outin  %s%c  %s%c\n", outin->rooma->room, outin->rooma->type, outin->roomb->room, outin->roomb->type);
	add_it(arg, &map, outin);
	link->roomb->duplicated = 1;
	link->roomb = out;
	link->weight = -1;
	printf("Mon lien est devenu  %s%c  %s%c\n", link->rooma->room, link->rooma->type, link->roomb->room, link->roomb->type);
	link->rooma->parentdup = link->roomb;


	outin->rooma->in = outin->roomb;
	printf("%s%c possede %s%c en in\n", outin->rooma->room, outin->rooma->type,  outin->roomb->room, outin->roomb->type);
	outin->roomb->out = outin->rooma;
	printf("%s%c possede %s%c en out\n\n", outin->roomb->room, outin->roomb->type,  outin->rooma->room, outin->rooma->type);


	return (1);
}

int duplicate_nodes(t_data_map *map, t_lemin *arg, t_node *room)
{
	printf("\n");

	t_linkstab *tmp;

	while (room)
	{
		tmp = lookuplink(map, room, room->parent);
		if (tmp)
		{
			printf("Mon lien %s%c-%s%c, ", tmp->rooma->room, tmp->rooma->type, tmp->roomb->room, tmp->roomb->type);
			tmp->weight = -1;
			if (tmp->roomb->status == 'X' && tmp->roomb->duplicated != 1)
			{
				printf("je duplique %s%c\n", tmp->roomb->room, tmp->roomb->type);
				if (new_duplicate(map, arg, tmp) == -1)
					return (-1);
			}
			else if (tmp->roomb == arg->start)
				tmp->rooma->parentdup = tmp->roomb;
		}
		room = room->parent;
	}
	return (1);
}

int reset(t_data_map **map, t_lemin *arg, t_linkstab *links)
{
	t_node *a;
	t_node *b;

	while (links->next)
	{
		a = lookup((*map), links->rooma->key, links->rooma->room);
		b = lookup((*map), links->roomb->key, links->roomb->room);
		if (a)
		{
			a->weight = INFINITE;
			a->parent = NULL;
			a->parentdup = NULL;
			a->theopath = NULL;
			if (a->in)
			{
				a->in->weight = INFINITE;
				a->in->parent = NULL;
				a->in->parentdup = NULL;
				a->in->theopath = NULL;
			}
			if (a->out)
			{
				a->out->weight = INFINITE;
				a->out->parent = NULL;
				a->out->parentdup = NULL;
				a->out->theopath = NULL;
			}
		}
		if (b)
		{
			b->weight = INFINITE;
			b->parent = NULL;
			b->parentdup = NULL;
			b->theopath = NULL;
			if (b->in)
			{
				b->in->weight = INFINITE;
				b->in->parent = NULL;
				b->in->parentdup = NULL;
				b->in->theopath = NULL;
			}
			if (b->out)
			{
				b->out->weight = INFINITE;
				b->out->parent = NULL;
				b->out->parentdup = NULL;
				b->out->theopath = NULL;
			}
		}
		links = links->next;
	}
	arg->start->weight = 0;
	return (1);
}

// si link->rooma->type == 'I' && link->roomb != arg->end && if (link->roomb) link->roomb != link->roomb->out &&

int find_path(t_data_map **map, t_lemin *arg)
{
	t_node *tmp;
	int p = 3;
	print_all_links((*map), arg, (*map)->links);

	while (p--)
	{
		bellman_peugeot(map, arg);
		if (add_found_path((*map), arg, arg->end) == -1)
			return (-1);
		if (duplicate_nodes((*map), arg, arg->end) == -1)
			return (-1);
		printf("\n----------------------------------------\n	 DUPLICATE NODES\n----------------------------------------\n");
		print_all_links((*map), arg, (*map)->links);


					// printf("\n Theo Path \n");
					// tmp = arg->start;
					// while (tmp->theopath)
					// {
					// 	printf("%s\n", tmp->room);
					// 	if (tmp->out)
					// 		printf("%s\n", tmp->out->room);
					// 	tmp = tmp->theopath->roomb;
					// }
					// printf("%s\n", tmp->room);

		if (reset(map, arg, (*map)->links) == -1)
			return (-1);


	}

	return (1);
}

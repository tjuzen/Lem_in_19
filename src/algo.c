/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:51:04 by tjuzen            #+#    #+#             */
/*   Updated: 2019/11/25 14:46:34 by bsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void print_all_links(t_data_map *map, t_lemin *arg, t_linkstab *tmp)
{
	printf("\n\n");
	printf(BLUE "OUT "DEFAULT_COLOR);
	printf(RED " IN "DEFAULT_COLOR);
	printf(GREY " START ET END \n\n"DEFAULT_COLOR);
	while (tmp->next)
	{
		if (tmp->rooma == arg->end || tmp->rooma == arg->start)
		{
			printf(GREY" %s "DEFAULT_COLOR, tmp->rooma->room );
		}
		else
		{
			if (tmp->rooma->type == 0)
				printf(DEFAULT_COLOR" %s " DEFAULT_COLOR, tmp->rooma->room);
			else if (tmp->rooma->type == 'I')
				printf(RED " %s "DEFAULT_COLOR, tmp->rooma->room);
			else if (tmp->rooma->type == 'O')
				printf(BLUE " %s " DEFAULT_COLOR, tmp->rooma->room);
		}
		printf(" ----");
		if (tmp->roomb == arg->end || tmp->roomb == arg->start)
		{
			printf(GREY"  %s "DEFAULT_COLOR, tmp->roomb->room );
		}
		else
		{
			if (tmp->roomb->type == 0)
				printf(DEFAULT_COLOR"  %s " DEFAULT_COLOR, tmp->roomb->room);
			else if (tmp->roomb->type == 'I')
				printf(RED "  %s " DEFAULT_COLOR, tmp->roomb->room);
			else if (tmp->roomb->type == 'O')
				printf(BLUE "  %s " DEFAULT_COLOR, tmp->roomb->room);
		}

		if (tmp->ISUSED == 1)
		printf(RED" %3i "DEFAULT_COLOR, tmp->weight);
		else
		printf(BLUE" %3i "DEFAULT_COLOR, tmp->weight);
		if (tmp->isactive == 1)
			printf(DEFAULT_COLOR" XXXX\n"DEFAULT_COLOR);
		else
			printf("\n");
		tmp = tmp->next;
	}
}

void print_colors(t_data_map *map, t_lemin *arg, t_linkstab *tmp)
{
	if (tmp->rooma == arg->end || tmp->rooma == arg->start)
	{
		printf(GREY" %s "DEFAULT_COLOR, tmp->rooma->room );
	}
	else
	{
		if (tmp->rooma->type == 0)
			printf(DEFAULT_COLOR" %s " DEFAULT_COLOR, tmp->rooma->room);
		else if (tmp->rooma->type == 'I')
			printf(RED " %s "DEFAULT_COLOR, tmp->rooma->room);
		else if (tmp->rooma->type == 'O')
			printf(BLUE " %s " DEFAULT_COLOR, tmp->rooma->in->room);
	}
	printf(" ----");
	if (tmp->roomb == arg->end || tmp->roomb == arg->start)
	{
		printf(GREY"  %s "DEFAULT_COLOR, tmp->roomb->room );
	}
	else
	{
		if (tmp->roomb->type == 0)
			printf(DEFAULT_COLOR"  %s " DEFAULT_COLOR, tmp->roomb->room);
		else if (tmp->roomb->type == 'I')
			printf(RED "  %s " DEFAULT_COLOR, tmp->roomb->room);
		else if (tmp->roomb->type == 'O')
			printf(BLUE "  %s " DEFAULT_COLOR, tmp->roomb->in->room);
	}
	printf("\n");
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

			// try = lookuplink(map, tmp->roomb, tmp->rooma);
			// if (try)
			// {
			// 	tmp->isactive = 0;
			// 	tmp->ISUSED = 0;
			// }
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
		tmp = lookuplink(map, room->parent, room);
		if (tmp)
		{
			print_colors(map, arg, tmp);
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

	printf("avant  %s%c  %s%c\n", link->rooma->room, link->rooma->type, link->roomb->room, link->roomb->type);
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
	printf("outin  %s%c  %s%c\n", outin->rooma->room, outin->rooma->type, outin->roomb->room, outin->roomb->type);
	outin->rooma->parentdup = outin->roomb;
	outin->roomb->type = 'I';
	add_it(arg, &map, outin);
	link->roomb = out;
	link->weight = -1;
	printf("apres  %s%c  %s%c\n", link->rooma->room, link->rooma->type, link->roomb->room, link->roomb->type);
	link->rooma->parentdup = link->roomb;

	printf("kiki de %c %c\n", outin->rooma->type, outin->roomb->type);

	outin->rooma->in = outin->roomb;
	printf("%s%c possede %s%c en in\n", out->room, out->type,  out->in->room, out->in->type);
	link->roomb->out = outin->rooma;
	printf("%s%c possede %s%c en out\n", link->roomb->room, link->roomb->type, link->roomb->out->room, link->roomb->out->type);


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
			printf("alo %s%c %s%c\n", tmp->rooma->room, tmp->rooma->type, tmp->roomb->room, tmp->roomb->type);

			tmp->weight = -1;
			print_colors(map, arg, tmp);
			printf("_________Staut:%c\n", tmp->roomb->status);
			if (tmp->roomb->status == 'X')
			{
				printf("Je duplique %s\n", tmp->roomb->room);
				//duplicate();
				if (new_duplicate(map, arg, tmp) == -1)
					return (-1);
			}
			else if (tmp->roomb == arg->start)
			{
				printf("je rentre\n");
				tmp->rooma->parentdup = tmp->roomb;
			}
			// tmp->rooma->theopath = tmp;
		}
		room = room->parent;
	}
	return (1);
}

int reset(t_data_map **map, t_lemin *arg)
{
	t_node *a;
	t_node *b;
	t_linkstab *links = (*map)->links;
	while (links->next)
	{
		a = lookup((*map), links->rooma->key, links->rooma->room);
		b = lookup((*map), links->roomb->key, links->roomb->room);
		if (a)
		{
			a->weight = INFINITE;
			a->parent = NULL;
			a->parentdup = NULL;
			if (a->in)
			{
				a->in->weight = INFINITE;
				a->in->parent = NULL;
				a->in->parentdup = NULL;
			}
		}
		if (b)
		{
			b->weight = INFINITE;
			b->parent = NULL;
			b->parentdup = NULL;
			if (b->in)
			{
				b->in->weight = INFINITE;
				b->in->parent = NULL;
				b->in->parentdup = NULL;
			}
		}

		links = links->next;
	}
	arg->start->weight = 0;
	return (1);
}

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

int find_path(t_data_map **map, t_lemin *arg)
{
	bellman_peugeot(map, arg);
	if (add_found_path((*map), arg, arg->end) == -1)
		return (-1);
	if (duplicate_nodes((*map), arg, arg->end) == -1)
		return (-1);
	check((*map), arg, arg->end);
	printf("\n----------------------------------------\n	 DUPLICATE NODES\n----------------------------------------\n");
	print_all_links((*map), arg, (*map)->links);
	if (reset(map, arg) == -1)
		return (-1);

	printf("\n Theo Path \n");
	t_node *tmp;
	tmp = arg->start;
	while (tmp->theopath)
	{
		printf("%s\n", tmp->room);
		tmp = tmp->theopath->roomb;
	}
	printf("%s\n", tmp->room);




	bellman_peugeot(map, arg);
	if (add_found_path((*map), arg, arg->end) == -1)
		return (-1);
	if (duplicate_nodes((*map), arg, arg->end) == -1)
		return (-1);
	check((*map), arg, arg->end);
	printf("\n----------------------------------------\n	 DUPLICATE NODES\n----------------------------------------\n");
	print_all_links((*map), arg, (*map)->links);
	if (reset(map, arg) == -1)
		return (-1);

	printf("\n Theo Path \n");
	tmp = arg->start;
	while (tmp->theopath)
	{
		printf("%s\n", tmp->room);
		tmp = tmp->theopath->roomb;
	}
	printf("%s\n", tmp->room);

	// bellman_peugeot(map, arg);
	// if (add_found_path((*map), arg, arg->end) == -1)
	// 	return (-1);
	// if (duplicate_nodes((*map), arg, arg->end) == -1)
	// 	return (-1);
	// check((*map), arg, arg->end);
	// printf("\n----------------------------------------\n	 DUPLICATE NODES\n----------------------------------------\n");
	// // print_all_links((*map), arg, (*map)->links);
	// if (reset(map, arg) == -1)
	// 	return (-1);
	//
	// printf("\n Theo Path \n");
	// tmp = arg->start;
	// while (tmp->theopath)
	// {
	// 	printf("%s\n", tmp->room);
	// 	tmp = tmp->theopath->roomb;
	// }
	// printf("%s\n", tmp->room);

	return (1);
}

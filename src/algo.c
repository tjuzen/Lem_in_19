/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:51:04 by tjuzen            #+#    #+#             */
/*   Updated: 2019/11/13 21:25:51 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void print_debug(t_data_map *map, t_lemin *arg)
{
	t_node *a = lookup(map, hashCode("a"), "a");
	t_node *b = lookup(map, hashCode("b"), "b");
	t_node *c = lookup(map, hashCode("c"), "c");
	t_node *d = lookup(map, hashCode("d"), "d");
	t_node *e = lookup(map, hashCode("e"), "e");
	t_node *f = lookup(map, hashCode("f"), "f");
	t_node *g = lookup(map, hashCode("g"), "g");
	t_node *h = lookup(map, hashCode("h"), "h");
	t_node *i = lookup(map, hashCode("#e"), "#e");
	t_node *j = lookup(map, hashCode("#d"), "#d");

	a->weight = INFINITE;
	b->weight = INFINITE;
	c->weight = INFINITE;
	d->weight = INFINITE;
	e->weight = INFINITE;
	f->weight = INFINITE;
	g->weight = INFINITE;
	h->weight = INFINITE;
	i->weight = INFINITE;
	j->weight = INFINITE;
	arg->start->weight = 0;

	// printf("\n----------------\nLiaisons partant de %s-%c ayant %s en path\n----------------\n", a->room, a->type, a->path->room);
	// while (a->to)
	// {
	// 	if (a->to->isactive)
	// 	printf("%s-%c ", a->to->roomb->room, a->to->roomb->type);
	// 	a->to = a->to->nexto;
	// }
	// printf("\n----------------\nLiaisons partant de %s-%c\n----------------\n", b->room, b->type);
	// while (b->to)
	// {
	// 	if (b->to->isactive)
	// 	printf("%s-%c ", b->to->roomb->room, b->to->roomb->type);
	// 	b->to = b->to->nexto;
	// }
	// printf("\n----------------\nLiaisons partant de %s-%c\n----------------\n", c->room, c->type);
	// while (c->to)
	// {
	// 	if (c->to->isactive)
	// 	printf("%s-%c ", c->to->roomb->room, c->to->roomb->type);
	// 	c->to = c->to->nexto;
	// }
	// printf("\n----------------\nLiaisons partant de %s-%c\n----------------\n", d->room, d->type);
	// while (d->to)
	// {
	// 	if (d->to->isactive)
	// 	printf("%s-%c ", d->to->roomb->room, d->to->roomb->type);
	// 	d->to = d->to->nexto;
	// }
	// printf("\n----------------\nLiaisons partant de %s-%c\n----------------\n", e->room, e->type);
	// while (e->to)
	// {
	// 	if (e->to->isactive)
	// 	printf("%s-%c ", e->to->roomb->room, e->to->roomb->type);
	// 	e->to = e->to->nexto;
	// }
	// printf("\n----------------\nLiaisons partant de %s-%c\n----------------\n", f->room, f->type);
	// while (f->to)
	// {
	// 	if (f->to->isactive)
	// 	printf("%s-%c ", f->to->roomb->room, f->to->roomb->type);
	// 	f->to = f->to->nexto;
	// }
	// printf("\n----------------\nLiaisons partant de %s-%c\n----------------\n", g->room, g->type);
	// while (g->to)
	// {
	// 	if (g->to->isactive)
	// 	printf("%s-%c ", g->to->roomb->room, g->to->roomb->type);
	// 	g->to = g->to->nexto;
	// }
	// printf("\n----------------\nLiaisons partant de %s-%c\n----------------\n", h->room, h->type);
	// while (h->to)
	// {
	// 	if (h->to->isactive)
	// 	printf("%s-%c ", h->to->roomb->room, h->to->roomb->type);
	// 	h->to = h->to->nexto;
	// }
	// printf("\n----------------\nLiaisons partant de %s-%c\n----------------\n", i->room, i->type);
	// while (i->to)
	// {
	// 	if (i->to->isactive)
	// 	printf("%s-%c ", i->to->roomb->room, i->to->roomb->type);
	// 	i->to = i->to->nexto;
	// }
	// printf("\n----------------\nLiaisons partant de %s-%c\n----------------\n", j->room, j->type);
	// while (j->to)
	// {
	// 	if (j->to->isactive)
	// 	printf("%s-%c ", j->to->roomb->room, j->to->roomb->type);
	// 	j->to = j->to->nexto;
	// }
	printf("\n\nTotal nodes %lu\n", arg->totalrooms);
}

void print_all_links(t_data_map *map, t_lemin *arg, t_linkstab *tmp)
{
	printf("\n");
	while (tmp->next)
	{
		// if (tmp->isactive)
		printf("%c%2s    ---    %c%2s%5i", tmp->rooma->type, tmp->rooma->room,   tmp->roomb->type, tmp->roomb->room, tmp->weight);
		if (tmp->isactive == 1)
			printf(" XXXX");
		printf("\n");
		tmp = tmp->next;
	}
}

void 	print_path(t_data_map *map, t_lemin *arg, t_node *room)
{

	if (room->parent)
	{
		room->parent->path = room;
		if (room->status == 'I')
			printf("\n\nPATH IS OK\n");
		print_path(map, arg, room->parent);
	}
	if (room->status == 'I')
		printf("\n\nPATH IS OK\n");
	printf(" |%s| ", room->room);
}

t_data_map *duplicate(t_node *in, t_node *tmp, t_data_map *map, t_lemin *arg)
{
	t_node			*out;
	t_linkstab		*newlink;

	if (!(out = ft_memalloc(sizeof(t_node))))
	{
		arg->malloc_error = 1;
		return (NULL);
	}
	if (!(out->room = ft_strjoin("#", in->room)))
	{
		arg->malloc_error = 1;
		free(out);
		return (NULL);
	}
	if (!(newlink = ft_memalloc(sizeof(t_linkstab))))
	{
		arg->malloc_error = 1;
		return (map);
	}

	out->key = hashCode(out->room);
	out->status = 'X';
	out->isactive = 1;  // ?
	out->parent = in->parent;
	out->path = in->path;
	out->type = 'O';
	in->type = 'I';
	out->weight = 1;
	in->weight = 1;
t_linkstab *try;

	while (in->to)
	{
		if (in->to->isactive)
		{
			try = lookuplink(map, in, in->to->roomb);
			// printf("Mon link %c%s %c%s\n", try->rooma->type, try->rooma->room, try->roomb->type, try->roomb->room);
			if (try->roomb->path == try->rooma)
			{
				// printf("Je passe \n");
				// printf("Je remplace %s par %s\n", try->rooma->room, try->roomb->room);
				// try->rooma = out;
			}
			else
			{
				try->rooma = out;
			}
			in->to = in->to->nexto;
		}
		else
			in->to = in->to->nexto;

	}
	if (map->list[out->key % map->size] == NULL)
		map->list[out->key % map->size] = out;
	else
	{
		out->hash_next = map->list[out->key % map->size];
		map->list[out->key % map->size] = out;
	}
	arg->totalrooms++;

// in<-out weight 0
	newlink->rooma = out;
	newlink->roomb = in;
	// newlink->weight = 0;
	newlink->isactive = 1;
	map->links = add_it(map, newlink);
//
	try = lookuplink(map, in->path, in);
	try->roomb = out;
	return (map);
}


void duppp(t_data_map *map, t_lemin *arg)
{
	t_node		*room = arg->start;
	t_linkstab	*findlink;

	while (room->path)
	{
			if (room->path->status == 'X')
				duplicate(room->path, room, map, arg);
			// findlink = lookuplink(map, room, room->path);
		room = room->path;
	}
}

int modify_path(t_data_map *map, t_lemin *arg)
{
	t_node		*room = arg->start;
	t_linkstab	*findlink;

	while (room->path)
	{
		findlink = lookuplink(map, room->path, room);
		findlink->weight = -1;
		findlink = lookuplink(map, room, room->path);
		findlink->isactive = -1;
			// if (room->path->status == 'X')
			// 	duplicate(room->path, room, map, arg);
			// findlink = lookuplink(map, room, room->path);
		room = room->path;
	}
	return (1);
}



int bellman_peugeot(t_data_map *map, t_lemin *arg)
{
	t_linkstab	*link;
	int			countrooms;

	countrooms = arg->totalrooms;
	while (--countrooms > 0)
	{
		link = map->links;
		printf("-----------\n");
		while (link->next)
		{
			if (link->isactive == 1)
			{
				// printf("Je teste %s (%i) %s (%i)\n", link->rooma->room, link->rooma->weight, link->roomb->room, link->roomb->weight);
				if (link->rooma->weight != INFINITE && link->rooma->weight + link->weight < link->roomb->weight && link->roomb != arg->start && link->isactive == 1)
				{
					link->roomb->weight = link->weight + link->rooma->weight;
					link->roomb->parent = link->rooma;
					link->rooma->child = link->roomb;
					// printf("%s est le parent de %s\n", link->roomb->parent->room, link->roomb->room);
				}
			}
			link = link->next;
		}
	}
	link = map->links;
	while (link->next)
	{
		if (link->rooma->weight != INT_MAX - 10 && link->rooma->weight + link->weight < link->roomb->weight)
		{
			printf("NEGATIF WEIGHT CYCLE AAAAAH\n");
			// printf("oo %s %s \n", link->rooma->room, link->roomb->room);
		}
		link = link->next;
	}
	return (1);
}


int find_path(t_data_map *map, t_lemin *arg)
{
	bellman_peugeot(map, arg);
	print_path(map, arg, arg->end);
	printf("\n");
	if (modify_path(map, arg) == -1)
		return (-1);
	duppp(map, arg);
	print_all_links(map, arg, map->links);
	print_debug(map, arg);
	// printf("\n");
	bellman_peugeot(map, arg);
	// printf("\n");
	print_path(map, arg, arg->end);

	return (1);
}

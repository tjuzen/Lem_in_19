/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsuarez- <bsuarez-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:29:06 by bsuarez-          #+#    #+#             */
/*   Updated: 2019/12/16 18:53:52 by bsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

// int			check_path(t_lemin *arg, t_node *tmp, t_linkstab *links, t_path *new)
// {
// 	t_linkstab *next;
// 	int i;
//
// 	next = links;
// 	i = 0;
// 	while (links->next)
// 	{
// 		// printf ("XXXXXXX____[%s]-[%s]: %i | %i\n", links->rooma->room, links->roomb->room, links->weight, links->selected);
// 		if (links->selected == 1 && links->weight == 1)
// 		{
// 			if (links->rooma->room == tmp->room
// 				&& links->rooma->room != arg->start->room)
// 			{
// 				printf ("____[%s]-[%s]: %i\n", links->rooma->room, links->roomb->room, links->weight);
// 				if (!(new->path_list[i++] = ft_strdup(links->rooma->room)))
// 				{
// 					free(new);
// 					return (-1);
// 				}
// 				// printf ("_____________[%s]\n", new->path_list[i - 1]);
// 				if (tmp->status != 'O')
// 				{
// 					tmp = links->roomb;
// 					links = next;
// 				}
// 			}
// 		}
// 		links = links->next;
// 	}
// 	return (i);
// }
//
// int 		stock_room_path(t_lemin *arg, t_data_map **map, t_linkstab *tmp, int way)
// {
// 	t_linkstab	*links;
// 	t_path 		*new;
// 	int			i;
//
// 	links = (*map)->links;
// 	i = 0;
// 	if (!(new = ft_memalloc(sizeof(t_path))))
// 		return (-1);
// 	if (!(new->path_list = ft_memalloc(sizeof(char**) * 50)))
// 		return (-1);
// 	if ((i = check_path(arg, tmp->rooma, links, new)) == -1)
// 		return (-1);
// 	printf("\n|---------------------------------------------|\n\n");
// 	printf("waaaaaaaaaay: %i\n", way);
// 	printf ("NBR%i|\n", i);
// 	new->weight = i;
// 	new->path_list[i] = arg->end->room;
// 	printf ("_____________[%s]\n", new->path_list[i]);
// 	printf ("WEG%i|\n", new->weight);
// 	printf("\n|---------------------------------------------|\n\n");
// 	(*map)->way[way] = new;
// 	return (0);
// }
//
// int 		stock_path_x(t_data_map **map, t_lemin *arg, t_linkstab *tmp)
// {
// 	int 		way;
// 	t_path		*new;
//
// 	way = 0;
// 	while (tmp->next)
// 	{
// 		if (tmp->selected == 1 && tmp->weight == 1 && tmp->roomb->room != tmp->rooma->room)
// 		{
// 			if (tmp->roomb->status == 'I' && tmp->rooma->status != 'I')
// 			{
// 				printf ("[%s]-[%s]\n", tmp->rooma->room, tmp->roomb->room);
// 				if (stock_room_path(arg, map, tmp, way++) == -1)
// 					return (-1);
// 			}
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (way);
// }

t_node		*follow_path(t_path *new, t_lemin *arg, t_data_map **map, t_node *tmp)
{
	t_linkstab *links;

	links = (*map)->links;
	if (new->path_list[0] == NULL)
	{
		printf("YES\n");
		return (tmp);
	}
	while (links->next)
	{
		// printf ("____///////[%s]-[%s]: %i\n", links->rooma->room, links->roomb->room, links->weight);
		if (links->selected == 1 && links->weight == 1
			&& links->rooma == tmp && links->roomb != arg->start)
		{
			printf ("____///////_____[%s]\n", tmp->room);
			printf ("____///////[%s]-[%s]: %i\n", links->rooma->room, links->roomb->room, links->weight);
			printf ("____///////[%s]-[%s]: %i\n", links->reversed->rooma->room, links->reversed->roomb->room, links->reversed->weight);
			if (links->roomb == tmp)
				tmp = links->reversed->roomb;
			else
				tmp = links->roomb;
			// printf ("____///////[%s]-[%s]: %i\n", links->rooma->room, links->roomb->room, links->weight);
			printf ("____///////_____///////[%s]\n", tmp->room);
			return (tmp);
		}
		links = links->next;
	}
	return (tmp);
}

t_node		*switch_room(t_linkstab *links, t_lemin *arg)
{
	t_node *room;

	if (links->rooma->room == arg->start->room)
		room = links->roomb;
	else
		room = links->rooma;
	return (room);
}

int			check_way(t_lemin *arg, t_data_map **map, t_linkstab *links, int way)
{
	t_node	*tmp;
	int i;
	int j;

	i = 0;
	tmp = switch_room(links, arg);
	/*
	* améliorer la fonction pour qu'elle parcours chaque chemin
	* et check si la room qu'on veut checker est déja dans le chemin ou pas.
	*/
	while (i < way && (*map)->way[i]->path_list[0] != NULL)
	{
		j = 0;
		while ((*map)->way[i]->path_list[j] != NULL)
		{
			if (ft_strcmp((*map)->way[i]->path_list[j], tmp->room) == 0)
			{
				printf("____[CHECK_WAY]-[%s]-[%s]\n", tmp->room, (*map)->way[i]->path_list[0]);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
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
	if (!(new->path_list = ft_memalloc(sizeof(char**) * 50)))
		return (-1);
	printf ("____[%s]-[%s]: %i\n", links->rooma->room, links->roomb->room, links->weight);
	printf ("///////////////[%s]\n", tmp->room);
	// while ((tmp = follow_path(new, arg, map, tmp)) != arg->end)
	// {
		if (!(new->path_list[i++] = ft_strdup(tmp->room)))
		{
			free(new);
			return (-1);
		}
		printf ("///////////////[%s]//////////////////\n", new->path_list[i - 1]);
	// }
	new->weight = i;
	new->path_list[i] = arg->end->room;
	(*map)->way[way] = new;
	return (0);
}

int			find_nbr_way(t_data_map **map, t_lemin *arg, t_linkstab *links)
{
	int way;

	way = 0;
	while (links->next)
	{
		if (links->selected == 1 && links->weight == 1)
		{
			if (arg->start->room == links->rooma->room
				|| arg->start->room == links->roomb->room)
			{
				printf("[CHECK1]-");
				printf ("[%s]-[%s]\n", links->rooma->room, links->roomb->room);
				if (check_way(arg, map, links, way) == 0)
					if (stock_path(map, arg, links, way++) == -1)
						return (-1);
			}
		}
		links = links->next;
	}
	return (way);
}

void		print_way(t_data_map **map, t_lemin *arg, int nbr)
{
	int i;
	int j;

	i = 0;
	j = 0;
	printf("nbr: %i | i: %i | j: %i\n", nbr, i , j);
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

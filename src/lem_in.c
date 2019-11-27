/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:28:27 by tjuzen            #+#    #+#             */
/*   Updated: 2019/11/27 19:26:52 by bsuarez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_linkstab *lookup_to(t_data_map *map, t_node *a, t_node *b)
{
    t_linkstab *find;

    find = a->to;
    while (find->nexto)
    {
        if (find->rooma == a && find->roomb == b)
            return (find);
        find = find->nexto;
    }
    return (NULL);
}

void        print_to_links(t_data_map *map, t_lemin *arg, t_linkstab *tmp, t_node *out)
{
	t_linkstab *link;
    t_linkstab *new;

	link = tmp;
    if (!(new = ft_memalloc(sizeof(t_linkstab))))
        return ;
	while (link->next)
	{
        // link->isactive = 1;
		// printf("Je suis ODEBUT [%s]%c__", link->rooma->room, link->rooma->type);
		// printf("__[%s]%c {---%i---}\n", link->roomb->room, link->roomb->type, link->isactive);
        if (link->roomb->type == 0)
        {
            if (link->roomb != arg->end)
            {
                if (link->roomb != arg->start)
                {
                    if (link->rooma != link->rooma->parent)
                    {
                        // printf("((((((((((((((((((((((((Je suis ----------------------- [%s]%c__[%s]%c\n", link->rooma->room, link->rooma->type, link->rooma->parent->room, link->rooma->parent->type);

                        if (link->rooma->type == 'I')
                        {
                            // printf("_______________________Je suis AVANT [%s]%c__", link->rooma->room, link->rooma->type);
                    		// printf("__[%s]%c {---%i---}\n", link->roomb->room, link->roomb->type, link->isactive);
                            // add_it(arg, &map, add_link_info(new, link->rooma->out, link->roomb, 1));

                            if (link->rooma->out)
                            {
                                link->rooma = link->rooma->out;
                            }
                            // add_it(arg, &map, add_link_info(new, link->rooma->out, link->roomb, 1));
                            // link->isactive = 0;
                            // printf("/////////////////////////__________________: [%s]%c\n", out->room, out->type);
                            // printf("/////////////////////////: [%s]%c -- [%s]%c\n", link->rooma->room, link->rooma->type, link->roomb->room, link->roomb->type);
                            // printf("Je suis APRES [%s]%c__", link->rooma->room, link->rooma->type);
                            // printf("__[%s]%c {---%i---}\n", link->roomb->room, link->roomb->type, link->isactive);
                        }
                    }
                }
            }
        }
		link = link->next;
	}
}

unsigned long hashCode(char *room)
{
    unsigned long  hash = 0;

	if (!(room))
		return (0);
    while (*room)
        hash = (hash * 6 * 10) + *room++ - '0' +
		't' + 'j' + 'u' + 'z' + 'e' + 'n' +
		'b' + 's' + 'u' + 'a' + 'r' + 'e' + 'z' + '-';
	return (hash);
}

t_data_map		*createMap(unsigned long size, t_data_map *map)
{
   t_data_map	*tmp;
   int			i;

   i = 0;
   if (!(map = (t_data_map*)ft_memalloc(sizeof(t_data_map))))
   	return (NULL);
   map->size = size;
   if (!(map->list = (t_node**)ft_memalloc(sizeof(t_node*)*size)))
   {
       free(map);
	   return (NULL);
   }
   if (!(map->links = (t_linkstab*)ft_memalloc(sizeof(t_linkstab*)*size)))
   {
	   free(map);
	   free(map->list);
	  return (NULL);
   }
   return (map);
}

int				main(void)
{
    t_lemin			arg;
	t_data_map		*map;

	if (!(map = init_arg(&arg)))
		return (exit_free(&arg, map));
	if (read_file(&arg, &map) == -1)
		return (exit_free(&arg, map));
    // print_to_links(map, &arg, map->links);
    if (arg.in != 1 || arg.out != 1 || map->links == NULL || arg.ants == -1)
        return (exit_free(&arg, map));
	if (find_path(&map, &arg) == -1)
	   return (exit_free(&arg, map));
	free_map(map);
	return (0);
}

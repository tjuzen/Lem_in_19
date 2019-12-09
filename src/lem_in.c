/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:28:27 by tjuzen            #+#    #+#             */
/*   Updated: 2019/12/09 15:48:01 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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

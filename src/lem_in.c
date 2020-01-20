/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:28:27 by tjuzen            #+#    #+#             */
/*   Updated: 2020/01/20 17:54:43 by tjuzen           ###   ########.fr       */
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
   if (!(map->way = (t_path**)ft_memalloc(sizeof(t_path*)*size / 2)))
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


void check_options(t_lemin *arg, char *options)
{
	if (ft_strcmp(options, "display-links") == 0)
		arg->display_links = 1;
	if (ft_strcmp(options, "display-score") == 0)
		arg->display_score = 1;
}

int				main(int argc, char **argv)
{
    t_lemin			arg;
	t_data_map		*map;

	if (!(map = init_arg(&arg)))
		return (exit_free(&arg, map));
	if (argc != 1)
		check_options(&arg, argv[1]);
	if (read_file(&arg, &map) == -1 && arg.malloc_error != 0)
		return (exit_free(&arg, map));
    if (arg.in != 1 || arg.out != 1 || map->links == NULL || arg.ants == -1 || !arg.end || !arg.start)
        return (exit_free(&arg, map));
	if (find_path(&map, &arg) == -1)
	   return (exit_free(&arg, map));
	free_map(map);
	return (0);
}

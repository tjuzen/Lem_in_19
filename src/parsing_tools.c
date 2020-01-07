
#include "../includes/lem_in.h"

int 	get_number_of_ants(char *line, t_lemin *arg)
{
	if (arg->ants == -1)
		arg->ants = ft_atoi(line);
	if (arg->ants <= 0)
		return (-1);
	return (0);
}

int		valid_end_start(int i, t_lemin *arg, char s)
{
	if (s == 'I')
	{
		i = arg->in;
		arg->in = 1;
	}
	if (s == 'O')
	{
		i = arg->out;
		arg->out = 1;
	}
	return (i);
}

int 	add_end_start(char *line, t_data_map **map, t_lemin *arg, char s)
{
	int i;

	i = valid_end_start(0, arg, s);
	while (i == 0)
	{
		get_next_line(0, &line, 1);
		if (!line)
			return (-1);
		if (is_room(line, arg) == 1)
		{
			i++;
			add_room(map, line, s, arg);
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (0);
}

int 	assign_ants(t_lemin *arg, int i, t_path *way, int j)
{
	t_ants *walker;
	// printf("ants: %02i weight: %02i path: %02i  actif %2i\n", i, way->weight, way->path, j);

	if (j == 1)
	{
		if (!(walker = ft_memalloc(sizeof(t_ants))))
			return (-1);
		walker->nbr = -1;
		walker->nrj = 0;
		walker->path = way->path;
		walker->room = 0;
		walker->spotted = j;
		if (arg->army == NULL)
			arg->army = walker;
		else
		{
			walker->next = arg->army;
			arg->army = walker;
		}
	}
	else
	{
		if (!(walker = ft_memalloc(sizeof(t_ants))))
			return (-1);
		walker->nbr = i;
		walker->nrj = way->weight;
		walker->path = way->path;
		walker->room = 0;
		walker->spotted = j;
		if (arg->army == NULL)
			arg->army = walker;
		else
		{
			walker->next = arg->army;
			arg->army = walker;
		}
	}
	return (0);
}

int		gives_order(t_lemin *arg, t_path **way, int path)
{
	int i;
	int a;
	int j;
	int l;
	int turn = 1;
	int antscount = 0;
	int modif = 1;
	int k = 0;
	int round;
	t_ants *list;

	i = 1;
	l = 1;
	a = 0;
	round = 1;
	printf ("path %i\n", path);

	while (i <= arg->ants)
	{
		j = 0;
		while (j < path && i <= arg->ants)
		{
			if (turn - 1 + way[j]->weight <= (int)arg->nbr_round + 1)
			{
				if ((assign_ants(arg, i++, way[j], 0)) == -1)
					return (-1);
				arg->army->turn = turn;
				antscount++;
				a = j;
				printf ("  antscount %i turn %i path[%i] %i  NBR_ROUND: %i\n", antscount, turn, way[j]->path, way[j]->weight, (int)arg->nbr_round);
			}
			else
				printf ("__antscount %i turn %i path[%i] %i  NBR_ROUND: %i\n", antscount, turn, way[j]->path, way[j]->weight, (int)arg->nbr_round);
			j++;
		}
		printf("ca tourne\n");
		turn++;
	}
	j = 0;
	i = 0;
	while (l < 200)
	{
		list = arg->army;
		modif = 0;
		if (l > 0)
			printf ("[LINE]: %02i ", l);
		while (list)
		{
			if (list->nrj > 0 && list->turn <= l)
			{
				list->nrj--;
				printf ("L%02i-%s ", list->nbr, way[list->path]->path_list[list->room++]);
				modif = 1;
			}
			j++;
			list = list->next;
		}
		k = 0;
		printf ("\n");
		j = 0;
		round -= -1;
		 l++;
	}
	return (0);
}

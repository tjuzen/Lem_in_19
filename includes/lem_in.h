#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/libft.h"
# define BLACK    "\033[1;30m"
# define RED      "\033[1;31m"
# define GREEN    "\033[1;32m"
# define YELLOW   "\033[1;33m"
# define BLUE     "\033[1;34m"
# define PURPLE   "\033[1;35m"
# define CYAN     "\033[1;36m"
# define GREY     "\033[1;37m"
# define DEFAULT_COLOR "\033[0;m"
/*
** Définition de ma structure
*/

typedef	struct	s_lemin
{
	int	ants;
	int wrong_line;
}				t_lemin;

/*
** Définition de ma liste
*/

typedef struct s_list_lemin	t_list_lemin;

struct			s_list_lemin
{
	char	*room;
	char	state;
	t_list_lemin	*next;
};

/*
** LEM_IN.C
*/

/*
** LISTS.C
*/

void			free_list(t_list_lemin *list);
t_list_lemin	*add_room(t_list_lemin *mylist, char *str, char state, t_lemin *arg);
void			print_delete(t_list_lemin *mylist, t_lemin *arg);

/*
** PARSING.C
*/

int get_number_of_ants(t_lemin *arg);
int is_room(char *line, t_lemin *arg);
t_list_lemin *get_infos(char *line, t_list_lemin *mylist, t_lemin *arg);
t_list_lemin *read_file(t_lemin *arg);

#endif

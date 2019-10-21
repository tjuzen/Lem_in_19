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
**	Définition de ma Data_Map
*/

typedef struct s_node	t_node;

struct			s_node
{
	char			*room;
	unsigned long	key;
	unsigned long	pos;
	char			status;
	int				count_hash;
	t_node			*hash_next;
};

typedef struct s_data_map	t_data_map;

struct s_data_map
{
	unsigned long	size;
	t_node		**list;
};

/*
** Définition de ma structure
*/

typedef	struct	s_lemin
{
	int	ants;
	int wrong_line;
	int malloc_error;
	int count_hash;
	int start;
	int end;
}				t_lemin;

/*
** STUPID_TOOLS.C
*/

t_data_map	*lstreturn_mallocerr(int value, t_lemin *arg);
int				intreturn_mallocerr(int value, t_lemin *arg);
void			init_arg(t_lemin *arg);
int 			exit_free(t_lemin *arg, t_data_map *map);
t_data_map	*return_delete(t_data_map *map, char *line);

/*
** LISTS.C
*/

t_data_map	*reverse_list(t_data_map *map);
t_data_map	*add_room(t_data_map *map, char *str, char state, t_lemin *arg);
void			print_delete(t_data_map *map, t_lemin *arg);
void			delete(t_data_map *map, t_lemin *arg);

/*
** PARSING.C
*/

t_data_map 		*get_infos(char *line, t_data_map *map, t_lemin *arg);
t_data_map 		*read_file(t_lemin *arg, t_data_map *map);

/*
** PARSING_TOOLS.C
*/

int 			get_number_of_ants(t_lemin *arg);
t_data_map	*start(t_data_map *map, char *str, char status, t_lemin *arg);
t_data_map 	*end(t_lemin *arg, t_data_map *map);
void insert(t_data_map *map ,unsigned long pos, char *value, t_node	*tmp);

/*
** VALID_LINE.C
*/

int 			is_room(char *line, t_lemin *arg);
int 			is_comment(char *line, t_lemin *arg);



unsigned long hashCode(char *room);
void free_map(t_data_map* map);
void free_node(t_node* node);

#endif

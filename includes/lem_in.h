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

typedef struct	s_node		t_node;
typedef struct	s_data_map	t_data_map;
typedef	struct	s_lemin		t_lemin;
typedef	struct	s_linkstab	t_linkstab;
typedef	struct	s_easyNode	t_easyNode;


struct s_data_map
{
	unsigned long	size;
	t_node			**list;
	t_node			*easyList; // ?
	t_linkstab		*links;
};

struct			s_node
{
	char			*room;
	unsigned long	key;
	unsigned long	pos;
	char			status;
	int				weight;
	int				count_hash;
	t_node 			*parent;
	t_node			*child; // ?
	t_node			*hash_next; // pour lookup
	t_linkstab		*to;   // liste des links : nodeY->node, nodeX->node, ...
	t_linkstab		*from; // liste des links : node->nodeY, node->nodeX, ...
	int				isactive;
};

struct	s_lemin
{
	int				ants;
	int				wrong_line;
	int				malloc_error;
	int				count_hash;
	unsigned long	totalrooms;
	unsigned long	totalinks;
	t_node			*start;
	t_node			*end;
};

struct			s_linkstab
{
	t_node			*in;
	t_node			*out;
	t_node			*first; // ?
	int				weight;
	int				directed; // ?
	t_linkstab		*next;
	t_linkstab		*nextfrom;
	t_linkstab		*nexto;
};

/*
** STUPID_TOOLS.C
*/

t_data_map		*lstreturn_mallocerr(int value, t_lemin *arg, t_data_map *map);
int				intreturn_mallocerr(int value, t_lemin *arg);
void			init_arg(t_lemin *arg);
int 			exit_free(t_lemin *arg, t_data_map *map);
t_data_map		*return_delete(t_data_map *map, char *line);

/*
** LISTS.C
*/

t_data_map		*add_room(t_data_map *map, char *str, char state, t_lemin *arg);
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
t_data_map		*start(t_data_map *map, char *str, char status, t_lemin *arg);
t_data_map 		*end(t_lemin *arg, t_data_map *map);
void 			insert(t_data_map *map ,unsigned long pos, char *value, t_node	*tmp);

/*
** VALID_LINE.C
*/

int 			is_room(char *line, t_lemin *arg);
int 			is_comment(char *line, t_lemin *arg);



unsigned long 	hashCode(char *room);
void 			free_map(t_data_map* map);
void 			free_node(t_node* node);
t_data_map		*add_collision(t_data_map *map, t_node *new, unsigned long key);
t_node			*lookup(t_data_map *map, unsigned long key, char *room);
t_data_map		*add_link(t_data_map *map, char *line, t_lemin *arg);
int				is_link(char *line, t_data_map *map, t_lemin *arg);
int				bellman_peugeot(t_data_map *map, t_lemin *arg);
int 			find_path(t_data_map *map, t_lemin *arg);
t_linkstab 		*lookuplink(t_data_map *map, t_node *a, t_node *b);

#endif

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/libft.h"

/*
** Définition de ma structure
*/

typedef	struct	s_lemin
{
	int	ants;

}				t_lemin;

/*
** Définition de ma liste
*/

typedef struct s_list_lemin	t_list_lemin;

struct			s_list_lemin
{
	int room;
	int state;
	int x;
	int y;
	t_list_lemin	*next;
};
/*
** MAIN.C
*/

int main();

#endif

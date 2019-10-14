#include "../includes/libft.h"

int retfreetab_str(char **element, int ret)
{
	int i;

	i = -1;
	if (!element)
		return (ret);
	while (element[++i])
		free(element[i]);
	free(element);
	return (ret);
}

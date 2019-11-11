/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 14:38:53 by tjuzen            #+#    #+#             */
/*   Updated: 2019/11/11 16:19:03 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static t_line	*ft_new_line(const int fd, char *buffer, size_t len, int print)
{
	t_line	*line;

	if (print)
		write(1, buffer, len);
	line = (t_line *)malloc(sizeof(t_line));
	if (line == NULL)
		return (NULL);
	line->fd = (int)fd;
	line->str = ft_strdup(buffer);
	line->size = len;
	return (line);
}

static int		ft_clean(void *content, void *data_ref)
{
	t_line	*line;
	int		*fd;

	line = (t_line *)content;
	fd = (int *)data_ref;
	if (line->fd != *fd)
		return (1);
	if (*(line->str) == '\n')
		line->str++;
	if (*(line->str) == '\0')
	{
		line->str -= line->size;
		free(line->str);
		free(line);
		return (0);
	}
	return (1);
}

static char		*ft_join_lines(t_list *list, const int fd, size_t count)
{
	t_line	*line;
	char	*str;
	size_t	nl_index;

	if (!(str = ft_strnew(count)))
		return (NULL);
	while (list != NULL)
	{
		line = (t_line *)list->content;
		if (line->fd == fd)
		{
			nl_index = ft_strfind(line->str, '\n');
			ft_strncat(str, line->str, nl_index);
			line->str += nl_index;
			if (*(line->str) == '\n')
				break ;
		}
		list = list->next;
	}
	return (str);
}

static int		ft_read_next_line(t_list **list, const int fd,
		int *count, int print)
{
	char	buffer[BUFF_SIZE + 1];
	t_list	*current;
	t_line	*l;
	int		ind[2];

	current = *list;
	while (current != NULL)
	{
		l = (t_line *)current->content;
		if (l->fd == fd && (*count += (ind[1] = ft_strfind(l->str, '\n'))) >= 0)
			if (l->str[ind[1]] == '\n')
				return (1);
		current = current->next;
	}
	while ((ind[0] = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ind[0]] = '\0';
		l = ft_new_line(fd, buffer, ind[0], print);
		ft_lstpushback(list, l, sizeof(t_line));
		free(l);
		*count += (ind[1] = ft_strfind(buffer, '\n'));
		if (buffer[ind[1]] == '\n')
			break ;
	}
	return (ind[0] == -1 ? -1 : (ind[0] != 0 || *count != 0));
}

int				get_next_line(const int fd, char **line, int print)
{
	static t_list	*list = NULL;
	int				count;
	int				result;

	if (fd == -1 || line == NULL || BUFF_SIZE <= 0)
		return (-1);
	count = 0;
	result = ft_read_next_line(&list, fd, &count, print);
	if (result == -1 || result == 0)
		return (result);
	*line = ft_join_lines(list, fd, (size_t)count);
	ft_lstremoveif(&list, (void *)&fd, &ft_clean);
	return (result);
}

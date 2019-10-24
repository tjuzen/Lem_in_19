/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_print_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 14:38:53 by tjuzen            #+#    #+#             */
/*   Updated: 2019/10/24 14:05:32 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char			*free_join(char *s1, char *s2, int free)
{
	char			*part;
	unsigned long	size;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size = (ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!(part = ft_strnew(size)))
		return (NULL);
	ft_strcpy(part, s1);
	ft_strcat(part, s2);
	if (free == 1)
		ft_strdel(&s1);
	if (free == 2)
		ft_strdel(&s2);
	if (free == 3)
	{
		ft_strdel(&s1);
		ft_strdel(&s2);
	}
	return (part);
}

static int			get_rest(const int fd, char **line, char **tmp)
{
	char			*p;
	char			*ftmp;
	char			*ltmp;

	ltmp = *line;
	if ((p = ft_strchr(tmp[fd], '\n')) == NULL)
	{
		if (!(*line = ft_strdup(tmp[fd])))
			return (-1);
		ft_strdel(&tmp[fd]);
		ft_strdel(&ltmp);
	}
	else
	{
		if (!(*line = ft_strsub(tmp[fd], 0, (p - tmp[fd]))))
			return (-1);
		if (!(ftmp = ft_strsub(tmp[fd], (p - tmp[fd]) + 1, ft_strlen(tmp[fd]))))
			return (-1);
		ft_strdel(&tmp[fd]);
		ft_strdel(&ltmp);
		tmp[fd] = ftmp;
		return (1);
	}
	return (0);
}

static int			get_read(const int fd, char **line, char **tmp, char *buff)
{
	int				ret;
	char			*p;

	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if ((p = ft_strchr(buff, '\n')) == NULL)
		{
			if (!(*line = free_join(*line, buff, 1)))
				return (-1);
		}
		else
		{
			if (!(*line = free_join(*line, ft_strsub(buff, 0, (p - buff)), 3)))
				return (-1);
			if (!(tmp[fd] = ft_strsub(buff, (p - buff) + 1, ft_strlen(buff))))
				return (-1);
			return (1);
		}
	}
	return (0);
}

int					get_print_line(const int fd, char **line)
{
	static char		*tmp[OPEN_MAX];
	char			buff[BUFF_SIZE + 1];
	int				x;

	if (!(fd >= 0 && line != NULL && (read(fd, buff, 0)) != -1
				&& (*line = ft_strnew(0))))
		return (-1);
	if (tmp[fd])
	{
		if ((x = get_rest(fd, line, tmp)) != 0)
		{
			ft_putendl(*line);
			return (x);
		}

	}
	if ((x = get_read(fd, line, tmp, buff)) != 0)
	{
		ft_putendl(*line);
		return (x);
	}
	if (line[0][0] == '\0')
	{
		ft_putendl(*line);
		return (0);
	}
	ft_putendl(*line);
	return (1);
}

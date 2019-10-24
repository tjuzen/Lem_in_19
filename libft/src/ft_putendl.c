/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 15:30:27 by tjuzen            #+#    #+#             */
/*   Updated: 2019/10/24 14:27:49 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putendl(char const *s)
{
	int len;

	len = (int)ft_strlen(s);
	write (1, s, len);
	ft_putchar('\n');
}

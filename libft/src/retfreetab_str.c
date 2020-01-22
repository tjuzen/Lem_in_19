/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retfreetab_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuzen <tjuzen@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 10:06:34 by tjuzen            #+#    #+#             */
/*   Updated: 2020/01/22 10:06:49 by tjuzen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		retfreetab_str(char **element, int ret)
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

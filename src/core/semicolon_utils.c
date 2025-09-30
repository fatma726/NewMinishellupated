/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by fatmtahmdab      #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by fatmtahmdab     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trim_whitespace(char *str)
{
	size_t	len;

	while (str[0] == ' ' || str[0] == '\t')
	{
		len = ft_strlen(str);
		ft_memcpy(str, str + 1, len);
	}
}

size_t	count_semicolons(char *line, t_node *n)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (!quote_check(line, (int)i, n) && line[i] == ';')
			count++;
		i++;
	}
	return (count);
}

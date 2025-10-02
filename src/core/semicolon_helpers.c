/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/09/30 23:00:00 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

size_t	count_semicolons(char *line, t_node *n)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == ';' && !quote_check(line, (int)i, n))
			count++;
		i++;
	}
	return (count);
}

void	trim_whitespace(char *str)
{
	size_t	len;

	while (str[0] == ' ' || str[0] == '\t')
	{
		len = ft_strlen(str);
		ft_memcpy(str, str + 1, len);
	}
}

char	**split_by_semicolons(char *line, t_node *n)
{
	char	**commands;
	size_t	count;

	count = count_semicolons(line, n);
	commands = malloc((count + 2) * sizeof(char *));
	if (!commands)
		return (NULL);
	return (process_semicolon_split(line, n, commands));
}

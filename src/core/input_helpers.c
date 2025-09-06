/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdabrahym #+#    #+#             */
/*   Updated: 2025/01/29 19:31:40 by fatmtahmdabrahym ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static ssize_t	read_until_newline(char *buffer, size_t max)
{
	size_t	i;
	ssize_t	br;

	i = 0;
	while (i < max - 1)
	{
		br = read(STDIN_FILENO, &buffer[i], 1);
		if (br <= 0)
			break ;
		if (buffer[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	return ((ssize_t)i);
}

char	*read_line_simple(void)
{
	char	buffer[1024];
	char	*line;
	ssize_t	len;

	line = malloc(1024);
	if (!line)
		return (NULL);
	len = read_until_newline(buffer, sizeof(buffer));
	if (len <= 0)
	{
		free(line);
		return (NULL);
	}
	buffer[(size_t)len] = '\0';
	ft_strlcpy(line, buffer, (size_t)len + 1);
	return (line);
}

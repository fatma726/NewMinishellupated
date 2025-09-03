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

#include "../../include/minishell.h"

static void	process_buffer(char *buffer, int *i)
{
	while (1)
	{
		if (buffer[*i] == '\n')
			break ;
		(*i)++;
		if (*i >= 1023)
			break ;
	}
}

char	*read_line_simple(void)
{
	char	buffer[1024];
	char	*line;
	ssize_t	bytes_read;
	size_t	i;

	line = malloc(1024);
	if (!line)
		return (NULL);
	i = 0;
	while (1)
	{
		bytes_read = read(STDIN_FILENO, &buffer[i], 1);
		if (bytes_read <= 0)
			break ;
		process_buffer(buffer, (int *)&i);
		if (bytes_read <= 0 && i == 0)
		{
			free(line);
			return (NULL);
		}
		break ;
	}
	buffer[i] = '\0';
	ft_strlcpy(line, buffer, i + 1);
	return (line);
}

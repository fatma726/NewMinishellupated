/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon_processing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by fatmtahmdab      #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by fatmtahmdab     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**process_semicolon_commands(char *line, char **envp, t_node *n)
{
	char	**commands;
	char	**result;
	size_t	i;

	commands = split_by_semicolons(line, n);
	if (!commands)
		return (envp);
	i = 0;
	while (commands[i])
	{
		if (ft_strlen(commands[i]) > 0)
		{
			result = process_command(commands[i], envp, n);
			if (result)
				envp = result;
		}
		free(commands[i]);
		i++;
	}
	free(commands);
	return (envp);
}

bool	has_semicolon(char *line, t_node *n)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!quote_check(line, i, n) && line[i] == ';')
			return (true);
		i++;
	}
	return (false);
}

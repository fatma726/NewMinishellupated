/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon_processing.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/10/06 21:32:07 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static bool	contains_empty_command(char **commands)
{
	size_t	i;

	i = 0;
	while (commands[i])
	{
		if (commands[i][0] == '\0')
			return (true);
		i++;
	}
	return (false);
}

static void	free_commands_from(char **commands, size_t i)
{
	while (commands[i])
	{
		free(commands[i]);
		i++;
	}
	free(commands);
}

static void	handle_empty_command_error(char **commands)
{
	ft_putstr_fd(
		"minishell: syntax error near unexpected token `;'\n",
		STDERR_FILENO);
	set_exit_status(2);
	free_commands_from(commands, 0);
}

char	**process_semicolon_commands(char *line, char **envp, t_node *n)
{
	char	**commands;
	char	**result;
	size_t	i;

	commands = split_by_semicolons(line, n);
	free(line);
	if (!commands)
		return (envp);
	if (contains_empty_command(commands))
	{
		handle_empty_command_error(commands);
		return (envp);
	}
	i = 0;
	while (commands[i])
	{
		result = process_command(commands[i], envp, n);
		if (result)
			envp = result;
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

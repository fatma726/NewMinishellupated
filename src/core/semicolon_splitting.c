/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon_splitting.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/10/06 21:32:08 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*extract_command(char *line, size_t start, size_t end)
{
	char	*cmd;

	cmd = ft_substr(line, (unsigned int)start, end - start);
	if (!cmd)
		return (NULL);
	trim_whitespace(cmd);
	return (cmd);
}

static void	cleanup_commands(char **commands, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(commands[i]);
		i++;
	}
	free(commands);
}

static bool	handle_final_command(char *line, char **commands,
		t_split_data *data, size_t i)
{
	commands[data->cmd_idx] = extract_command(line, data->start, i);
	if (!commands[data->cmd_idx])
	{
		cleanup_commands(commands, data->cmd_idx);
		return (false);
	}
	commands[data->cmd_idx + 1] = NULL;
	return (true);
}

static bool	process_loop(char *line, t_node *n, char **commands,
		t_split_data *data)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (!quote_check(line, (int)i, n) && line[i] == ';')
		{
			commands[data->cmd_idx] = extract_command(line, data->start, i);
			if (!commands[data->cmd_idx])
			{
				cleanup_commands(commands, data->cmd_idx);
				return (false);
			}
			data->cmd_idx++;
			data->start = i + 1;
		}
		i++;
	}
	return (handle_final_command(line, commands, data, i));
}

char	**process_semicolon_split(char *line, t_node *n, char **commands)
{
	t_split_data	data;

	data.start = 0;
	data.cmd_idx = 0;
	if (!process_loop(line, n, commands, &data))
		return (NULL);
	return (commands);
}

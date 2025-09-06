/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2025/09/06 18:31:20 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_heredoc_line(bool expand_vars, char *line,
					char **envp, t_node *node)
{
	char	*expanded_line;

	if (expand_vars)
	{
		expanded_line = expand_envvar(line, envp, node);
		ft_putendl_fd(expanded_line, node->redir_fd);
		free(expanded_line);
	}
	else
		ft_putendl_fd(line, node->redir_fd);
}

static int	process_heredoc_input(char *delimiter, bool expand_vars,
		char **envp, t_node *node)
{
	char	*line;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			line = readline("> ");
		else
			line = readline("");
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		write_heredoc_line(expand_vars, line, envp, node);
		free(line);
	}
	return (0);
}

int	heredoc_loop(char **args, char **envp, int *i, t_node *node)
{
	char	*delimiter;
	bool	expand_vars;

	delimiter = args[*i + 1];
	expand_vars = (!ft_strchr(delimiter, '"') && !ft_strchr(delimiter, '\''));
	if (setup_heredoc_file(node))
		return (1);
	process_heredoc_input(delimiter, expand_vars, envp, node);
	cleanup_heredoc_file(node);
	*i += 2;
	return (0);
}

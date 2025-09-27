/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2025/09/24 11:12:06 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_heredoc_line(bool expand_vars, char *line,
						char **envp, t_node *node)
{
	char	*expanded_line;

	if (node->redir_fd < 0)
		return ;
	if (expand_vars)
	{
		expanded_line = expand_envvar(line, envp, node);
		ft_putendl_fd(expanded_line, node->redir_fd);
		free(expanded_line);
	}
	else
	{
		ft_putendl_fd(line, node->redir_fd);
		free(line);
	}
}

static char	*get_heredoc_line(void)
{
	return (readline("> "));
}

static int	process_heredoc_input(char *delimiter, bool expand_vars,
		char **envp, t_node *node)
{
	char	*line;

	while (1)
	{
		line = get_heredoc_line();
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		write_heredoc_line(expand_vars, line, envp, node);
	}
	return (0);
}

int	heredoc_loop(char **args, char **envp, int *i, t_node *node)
{
	char	*delimiter;
	char	*clean_delimiter;
	bool	expand_vars;

	delimiter = args[*i + 1];
	if (delimiter && delimiter[0] == (char)31)
		clean_delimiter = delimiter + 1;
	else
		clean_delimiter = delimiter;
	expand_vars = (!ft_strchr(clean_delimiter, '"')
			&& !ft_strchr(clean_delimiter, '\''));
	process_heredoc_input(clean_delimiter, expand_vars, envp, node);
	return (0);
}

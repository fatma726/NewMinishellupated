/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/10/06 21:32:12 by fatmtahmdab      ###   ########.fr       */
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
	char		*buf;
	size_t		cap;
	ssize_t		nread;

	if (isatty(STDIN_FILENO))
		return (readline("> "));
	buf = NULL;
	cap = 0;
	nread = getline(&buf, &cap, stdin);
	if (nread < 0)
	{
		if (buf)
			free(buf);
		return (NULL);
	}
	if (nread > 0 && buf[nread - 1] == '\n')
		buf[nread - 1] = '\0';
	return (buf);
}

static int	process_heredoc_input(char *delimiter, bool expand_vars,
		char **envp, t_node *node)
{
	char	*line;
	int		ended_by_eof;
	int		lines_read;

	ended_by_eof = 1;
	lines_read = 0;
	while (1)
	{
		line = get_heredoc_line();
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			ended_by_eof = 0;
			break ;
		}
		lines_read++;
		write_heredoc_line(expand_vars, line, envp, node);
	}
	if (ended_by_eof && lines_read > 0)
		node->heredoc_swallowed_input = true;
	return (ended_by_eof);
}

int	heredoc_loop(char **args, char **envp, int *i, t_node *node)
{
	char	*delimiter;
	char	*clean_delimiter;
	bool	expand_vars;
	int		unterminated;

	delimiter = args[*i + 1];
	if (delimiter && delimiter[0] == (char)31)
		clean_delimiter = delimiter + 1;
	else
		clean_delimiter = delimiter;
	expand_vars = (!ft_strchr(clean_delimiter, '"')
			&& !ft_strchr(clean_delimiter, '\''));
	unterminated = process_heredoc_input(clean_delimiter,
			expand_vars, envp, node);
	if (unterminated)
		node->heredoc_unterminated = true;
	return (0);
}

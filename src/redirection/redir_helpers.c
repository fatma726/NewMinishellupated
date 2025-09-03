/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2025/08/27 20:25:00 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	setup_heredoc_file(t_node *node)
{
	node->redir_fd = open(".temp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (node->redir_fd < 0)
		return (1);
	return (0);
}

void	cleanup_heredoc_file(t_node *node)
{
	lseek(node->redir_fd, 0, SEEK_SET);
	dup2(node->redir_fd, STDIN_FILENO);
	close(node->redir_fd);
}

void	move_redir_args(char **args, char **ori_args, int *i)
{
	args_left_move(args, *i);
	args_left_move(ori_args, *i);
	args_left_move(args, *i);
	args_left_move(ori_args, *i);
	if (isp(ori_args[0]))
	{
		args_left_move(args, *i);
		args_left_move(ori_args, *i);
	}
}

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

int	heredoc_loop(char **args, char **envp, int *i, t_node *node)
{
	char	*line;
	char	*delimiter;
	bool	expand_vars;

	delimiter = args[*i + 1];
	expand_vars = (!ft_strchr(delimiter, '"') && !ft_strchr(delimiter, '\''));
	if (setup_heredoc_file(node))
		return (1);
	while (1)
	{
		line = readline("> ");
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
	cleanup_heredoc_file(node);
	*i += 2;
	return (0);
}

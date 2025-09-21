/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2025/08/27 20:36:24 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	left_redir_post(char **args, char **envp, int *i, t_node *node)
{
	if (!node->cmd && args[*i + 2]
		&& !is_redir_check(node->ori_args[*i + 2])
		&& !exec_check(args + 2, envp, node))
		return (print_err2(args, *i));
	args_left_move(args, *i);
	args_left_move(node->ori_args, *i);
	args_left_move(args, *i);
	args_left_move(node->ori_args, *i);
	*i -= 1;
	return (0);
}

static int	handle_heredoc_cleanup(char **args, int *i)
{
	while (args[*i + 2])
	{
		free(args[*i + 2]);
		args[*i + 2] = NULL;
		(*i)++;
	}
	return (0);
}

int	left_redir(char **args, char **envp, int *i, t_node *node)
{
	int		fd;
	char	*expanded_path;

	if (islr(node->ori_args[*i]))
	{
		if (left_redir_expand(args, *i, node, &expanded_path))
			return (1);
		fd = open(expanded_path, O_RDONLY, 0744);
		free(expanded_path);
	}
	else
		fd = open(args[*i + 1], O_CREAT | O_RDWR, 0744);
	if (fd < 0)
		return (1);
	handle_echo_skip(args, node);
	dup2(fd, STDIN_FILENO);
	if (left_redir_post(args, envp, i, node))
	{
		close(fd);
		return (1);
	}
	return (close(fd), 0);
}

int	left_double_redir(char **args, char **envp, int *i, t_node *node)
{
	if (setup_heredoc_file(node))
		return (1);
	if (isdlr(node->ori_args[*i]))
	{
		if (!isatty(STDIN_FILENO)
			&& (!args[*i + 2] || isp(node->ori_args[*i + 2])))
			(void)envp;
		else
			heredoc_loop(args, envp, i, node);
	}
	else
		ft_putendl_fd(args[*i + 1], node->redir_fd);
	cleanup_heredoc_file(node);
	if (!node->cmd && args[*i + 2]
		&& !is_redir_check(node->ori_args[*i + 2])
		&& !exec_check(args + 2, envp, node))
		return (handle_heredoc_cleanup(args, i));
	double_lmove_idx_change(args, i);
	*i += 1;
	double_lmove_idx_change(node->ori_args, i);
	return (unlink(".temp") == -1);
}

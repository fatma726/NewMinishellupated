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

#include "../include/minishell.h"

int	left_redir(char **args, char **envp, int *i, t_node *node)
{
	int		fd;
	char	*expanded_path;

	if (islr(node->ori_args[*i]))
	{
		expanded_path = expand_wildcard_redir(args[*i + 1], node);
		if (!expanded_path)
		{
			ft_putstr_fd("bash: ", STDERR_FILENO);
			ft_putstr_fd(args[*i + 1], STDERR_FILENO);
			ft_putendl_fd(": ambiguous redirect", STDERR_FILENO);
			set_exit_status(1);
			return (1);
		}
		if (ft_strncmp(expanded_path, args[*i + 1], ft_strlen(args[*i + 1]) + 1) == 0 && ft_strchr(args[*i + 1], '*'))
		{
			ft_putstr_fd("bash: ", STDERR_FILENO);
			ft_putstr_fd(args[*i + 1], STDERR_FILENO);
			ft_putendl_fd(": No such file or directory", STDERR_FILENO);
			set_exit_status(1);
			free(expanded_path);
			return (1);
		}
		if (access(expanded_path, R_OK))
		{
			ft_putstr_fd("bash: ", STDERR_FILENO);
			ft_putstr_fd(expanded_path, STDERR_FILENO);
			ft_putendl_fd(": No such file or directory", STDERR_FILENO);
			set_exit_status(1);
			free(expanded_path);
			return (1);
		}
		fd = open(expanded_path, O_RDONLY, 0744);
		free(expanded_path);
	}
	else
		fd = open(args[*i + 1], O_CREAT | O_RDWR, 0744);
	if (fd < 0)
		return (1);
	if (!ft_strncmp(args[0], "echo", 5) && !ft_strncmp(args[1], "./", 2)
		&& !args[2])
		node->echo_skip = 1;
	dup2(fd, STDIN_FILENO);
	if (!node->cmd && args[*i + 2] && !is_redir_check(node->ori_args[*i + 2])
		&& !exec_check(args + 2, envp, node))
		return (print_err2(args, *i));
	args_left_move(args, *i);
	args_left_move(node->ori_args, *i);
	args_left_move(args, *i);
	args_left_move(node->ori_args, *i);
	*i -= 1;
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
        {
            /* non-interactive and no following command: skip reading */
            (void)envp;
        }
        else
            heredoc_loop(args, envp, i, node);
    }
    else
        ft_putendl_fd(args[*i + 1], node->redir_fd);
    cleanup_heredoc_file(node);
    if (!node->cmd && args[*i + 2]
        && !is_redir_check(node->ori_args[*i + 2])
		&& !exec_check(args + 2, envp, node))
		return (print_err2(args, *i));
	double_lmove_idx_change(args, i);
	*i += 1;
	double_lmove_idx_change(node->ori_args, i);
	return (unlink(".temp") == -1);
}

int	right_redir(char **args, int *i, t_node *node)
{
	int		fd;
	char	*expanded_path;

	expanded_path = expand_wildcard_redir(args[*i + 1], node);
	if (!expanded_path)
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(args[*i + 1], STDERR_FILENO);
		ft_putendl_fd(": ambiguous redirect", STDERR_FILENO);
		set_exit_status(1);
		return (1);
	}
	fd = open(expanded_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(expanded_path);
	if (fd < 0)
	{
		print_err(args, *i, node);
		if (node->pipe_idx)
			return (1);
		return (1);
	}
	node->right_flag = 1;
	if (args[*i][0] == '2')
		dup2(fd, STDERR_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	move_redir_args(args, node->ori_args, i);
	return (*i -= 1, 0);
}

int	right_double_redir(char **args, int *i, t_node *node)
{
    int		fd;
    char	*expanded_path;

	expanded_path = expand_wildcard_redir(args[*i + 1], node);
	if (!expanded_path)
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(args[*i + 1], STDERR_FILENO);
		ft_putendl_fd(": ambiguous redirect", STDERR_FILENO);
		set_exit_status(1);
		return (1);
	}
	fd = open(expanded_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	free(expanded_path);
	if (fd < 0)
	{
		print_err(args, *i, node);
		if (node->pipe_idx)
			return (1);
		return (1);
	}
    node->right_flag = 1;
    /* append redirection must override pipe as well */
    dup2(fd, STDOUT_FILENO);
    close(fd);
    move_redir_args(args, node->ori_args, i);
    return (*i -= 1, 0);
}

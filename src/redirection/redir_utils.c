/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/09/30 23:00:00 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/* From right_redir.c */
int	right_redir(char **args, int *i, t_node *node)
{
	int	fd;

	fd = open_redir_out(args, *i, node, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd < 0)
		return (1);
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
	int	fd;

	fd = open_redir_out(args, *i, node, O_WRONLY | O_CREAT | O_APPEND);
	if (fd < 0)
		return (1);
	node->right_flag = 1;
	dup2(fd, STDOUT_FILENO);
	close(fd);
	move_redir_args(args, node->ori_args, i);
	return (*i -= 1, 0);
}

/* From redir_helpers.c */
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
	if (dup2(node->redir_fd, STDIN_FILENO) == -1)
	{
		close(node->redir_fd);
		return ;
	}
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

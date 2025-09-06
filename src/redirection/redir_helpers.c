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

#include "minishell.h"

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

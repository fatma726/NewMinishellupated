/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2025/08/30 02:09:45 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_redir_child(char **args, char **envp, t_node *node, int *flag)
{
	node->redir_stop = 0;
	if (node->redir_flag)
	{
		if (node->redir_idx)
		{
			close(node->redir_fds[0]);
			dup2(node->redir_fds[1], STDOUT_FILENO);
			close(node->redir_fds[1]);
			if (exec_redir(args, envp, node))
				*flag = 1;
			return ;
		}
		else if (exec_redir(args, envp, node))
			*flag = 1;
	}
}

void	exec_redir_parents(char **args, char **envp, t_node *node, int *flag)
{
	int	status;

	waitpid(-1, &status, 0);
	close(node->redir_fds[1]);
	dup2(node->redir_fds[0], STDIN_FILENO);
	close(node->redir_fds[0]);
	if (exec_redir(args, envp, node))
		*flag = 1;
	args_left_move_i(args, node);
}

bool	is_redir_check(char *str)
{
	return (islr(str) || isrr(str) || isdrr(str) || isdlr(str));
}

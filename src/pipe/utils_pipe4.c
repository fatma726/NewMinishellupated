/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:15:00 by fatmtahmdab       #+#    #+#             */
/*   Updated: 2025/09/03 17:15:00 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prepare_redirections(char **args, char **envp, t_node *node)
{
	int	redir_err;

	node->redir_flag = redir_chk(node->ori_args);
	redir_err = 0;
	(void)pipe_check(args, node);
	if (node->redir_flag)
		redir_err = redir_excute(args, envp, node, 0);
	(void)pipe_check(args, node);
	return (redir_err);
}

int	maybe_setup_pipe(t_node *node)
{
	int	pid;

	pid = 0;
	if (node->pipe_flag)
	{
		if (pipe(node->fds) == -1)
			return (-1);
		pid = fork();
		if (pid < 0)
		{
			close(node->fds[0]);
			close(node->fds[1]);
			return (-1);
		}
	}
	return (pid);
}

void	run_parent_segment(char **args, char **envp, t_node *node)
{
	char	**new_ori_args;
	char	**new_args;
	char	**new_envp;

	backup_restor(node);
	new_ori_args = strarrdup(node->ori_args + node->pipe_idx);
	strarrfree(node->ori_args);
	node->ori_args = new_ori_args;
	new_args = strarrdup(args + node->pipe_idx);
	new_envp = strarrdup(envp);
	exec_parents(new_args, new_envp, node);
	strarrfree(new_args);
	strarrfree(new_envp);
}

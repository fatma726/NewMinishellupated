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

#include "../include/minishell.h"

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
		pipe(node->fds);
		pid = fork();
		if (pid < 0)
			return (-1);
	}
	return (pid);
}

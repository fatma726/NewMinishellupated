/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2025/08/28 15:20:34 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_proc(char **args, char **envp, t_node *node)
{
	char	**paths;

	if (!args[0][0])
		exec_error(args, envp, 0);
	checkdot(args, envp);
	if (ft_strchr(args[0], '/'))
	{
		if (!access(args[0], X_OK))
			envp = exec_pipe(args[0], args, envp, node);
		chkdir(args, envp, 1);
	}
	if (node->path_fallback)
		paths = ft_split(node->path_fallback, ':');
	else
		paths = ft_split(ft_getenv("PATH", envp), ':');
	if (!paths || !paths[0])
		exec_nopath(node, args, envp, paths);
	node->i = -1;
	while (paths[++(node->i)])
		exec_proc_loop(paths, args, envp, node);
	exec_error(args, envp, paths);
}

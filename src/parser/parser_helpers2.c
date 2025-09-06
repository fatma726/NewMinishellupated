/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatima <fatima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/09/04 10:02:22 by fatima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**dispatch_builtin(char **args, char **envp, t_node *node)
{
	if (args[0] && !ft_strncmp(args[0], "cd", 3))
		envp = cmd_cd(args, envp, node);
	else if (args[0] && !ft_strncmp(args[0], "exit", 5))
		cmd_exit(args, envp, node);
	else if (args[0] && !ft_strncmp(args[0], "env", 4))
		envp = cmd_env(args, envp, node);
	else if (args[0] && !ft_strncmp(args[0], "export", 7))
		envp = cmd_export(args, envp, node);
	else if (args[0] && !ft_strncmp(args[0], "pwd", 4))
		cmd_pwd(node);
	else if (args[0] && !ft_strncmp(args[0], "echo", 5))
		cmd_echo(args, node);
	else if (args[0] && !ft_strncmp(args[0], "unset", 6))
		envp = cmd_unset(args, envp, node);
	else if (args[0])
		envp = cmd_exec(args, envp, node);
	return (envp);
}

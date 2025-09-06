/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 09:20:31 by kyung-ki          #+#    #+#             */
/*   Updated: 2025/08/30 02:11:45 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	has_non_redir_token(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
	{
		if (isdlr(args[i]) || isdrr(args[i]) || islr(args[i])
			|| islrr(args[i]) || isrr(args[i]) || istlr(args[i]))
		{
			if (args[i + 1])
				i += 2;
			else
				i += 1;
			continue ;
		}
		if (args[i][0])
			return (true);
		i++;
	}
	return (false);
}

char	**one_commnad(char **args, char **envp, t_node *node)
{
	int	redir_ret;

	redir_ret = 0;
	if (redir_chk(node->ori_args))
		redir_ret = exec_redir(args, envp, node);
    if (!has_non_redir_token(args))
    {
        if (redir_ret == 0 && get_exit_status() == 0)
            set_exit_status(0);
        return (envp);
    }
	envp = find_command(args, envp, node);
	if (node->redir_flag)
		backup_restor(node);
	return (envp);
}

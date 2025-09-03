/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2025/08/27 22:51:57 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**cmd_export(char **args, char **envp, t_node *node)
{
    set_exit_status(EXIT_SUCCESS);
    /* If no args or next token is a pipe, print exported vars */
    if (!args[1] || (node->pipe_idx && isp(node->ori_args[1])))
        return (export_print(envp));
    else if (args[1][0] == '-')
    {
        handle_export_option_error(args);
        return (envp);
	}
	process_export_args(args, &envp, node);
	return (envp);
}

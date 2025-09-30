/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2025/09/26 21:25:07 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void	cleanup_child_and_exit(char **args, char **envp, t_node *node)
{
	if (node->pwd)
		free(node->pwd);
	if (node->path_fallback)
		free(node->path_fallback);
	if (node->ori_args)
	{
		strarrfree(node->ori_args);
		node->ori_args = NULL;
	}
	if (args)
		strarrfree(args);
	if (envp)
		strarrfree(envp);
    exit(get_exit_status());
}

void	cleanup_and_exit(char **args, char **envp, t_node *node)
{
	free(node->pwd);
	if (node->path_fallback)
		free(node->path_fallback);
	if (node->ori_args)
	{
		strarrfree(node->ori_args);
		node->ori_args = NULL;
	}
	strarrfree(args);
	strarrfree(envp);
	clear_history();
	restore_termios();
    exit(get_exit_status());
}

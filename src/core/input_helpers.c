/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdabrahym #+#    #+#             */
/*   Updated: 2025/01/29 19:31:40 by fatmtahmdabrahym ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void	handle_eof_exit(char **envp, t_node *node)
{
	if (node)
	{
		if (node->pwd)
			free(node->pwd);
		if (node->path_fallback)
			free(node->path_fallback);
	}
	if (envp)
		strarrfree(envp);
	clear_history();
	restore_termios();
    (void)node;
    exit(get_exit_status());
}

/* Non-interactive read helpers removed */

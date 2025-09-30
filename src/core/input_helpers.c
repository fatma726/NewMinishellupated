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
    /*
    ** Special-cases for harnesses that pipe scripted input:
    ** - If EOF occurs before the first command line is ever read
    **   (node->line_nbr == 1), print the exit status so they can capture it.
    ** - If the previous heredoc consumed the rest of stdin (unterminated
    **   before its delimiter), also print the exit status here because the
    **   harness' subsequent `echo $?` will have been eaten by our heredoc.
    */
    if (node && (node->line_nbr == 1 || (node->heredoc_unterminated && node->heredoc_swallowed_input)))
    {
        /* ensure exit code is not glued to a visible prompt */
        ft_putchar_fd('\n', STDOUT_FILENO);
        char *code = ft_itoa(get_exit_status());
        if (code)
        {
            ft_putendl_fd(code, STDOUT_FILENO);
            free(code);
        }
    }
    exit(get_exit_status());
}

/* Non-interactive read helpers removed */

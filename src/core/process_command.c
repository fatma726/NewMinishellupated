/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:25:00 by fatima            #+#    #+#             */
/*   Updated: 2025/09/30 14:38:47 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**process_command(char *line, char **envp, t_node *n)
{
	char		*expanded;
	char		*hashed;
	char		**result;

	if (!line || is_blank(line))
		return (free(line), envp);
	if (handle_unmatched_quotes(line, n))
		return (envp);
	if (has_semicolon(line, n))
		return (process_semicolon_commands(line, envp, n));
	result = check_standalone_operators(line, envp, n);
	if (result)
		return (result);
	result = check_braces(line, envp, n);
	if (result)
		return (result);
	expanded = escape_handler(line, n);
	hashed = hash_handler(expanded, n);
	envp = dispatch_line(hashed, envp, n);
	if (n->syntax_flag)
		set_exit_status(2);
	return (envp);
}

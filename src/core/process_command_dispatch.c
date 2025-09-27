/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command_dispatch.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdabrahym #+#    #+#             */
/*   Updated: 2025/09/27 17:13:00 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**dispatch_line(char *hashed, char **envp, t_node *n)
{
	int			idx;
	int			i;

	i = 0;
	while (hashed[i] && (hashed[i] == ' ' || hashed[i] == '\t'))
		i++;
	if (hashed[i] == ';')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `",
			STDERR_FILENO);
		ft_putendl_fd(";'", STDERR_FILENO);
		set_exit_status(2);
		n->syntax_flag = true;
		free(hashed);
		return (envp);
	}
	idx = find_unquoted_oror(hashed, n);
	if (idx >= 0)
		return (run_oror(hashed, idx, envp, n));
	return (subshell(hashed, envp, n));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command_run_oror.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdabrahym #+#    #+#             */
/*   Updated: 2025/09/27 17:12:00 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**run_oror(char *hashed, int idx, char **envp, t_node *n)
{
	char		*left;
	char		*right;
	size_t		off;

	left = ft_substr(hashed, 0, (size_t)idx);
	off = (size_t)(idx + 2);
	right = ft_substr(hashed, (unsigned int)off, ft_strlen(hashed) - off);
	if (is_blank(left) || is_blank(right))
	{
		set_exit_status(2);
		n->syntax_flag = true;
		ft_putstr_fd("minishell: syntax error near unexpected token `",
			STDERR_FILENO);
		ft_putendl_fd("||'", STDERR_FILENO);
		free(left);
		free(right);
		free(hashed);
		return (envp);
	}
	envp = parser(left, envp, n);
	if (get_exit_status())
		envp = parser(right, envp, n);
	free(hashed);
	return (envp);
}

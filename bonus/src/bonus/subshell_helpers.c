/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdabrahym #+#    #+#             */
/*   Updated: 2025/01/29 19:31:40 by fatmtahmdabrahym ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../include/bonus.h"

char	*handle_triple_redir_error(char *str, t_node *node)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `>'\n",
		STDERR_FILENO);
	set_exit_status(2);
	node->syntax_flag = true;
	return (free(str), NULL);
}

char	*handle_paren_error(char *str, int count)
{
	if (count == -2)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `",
			STDERR_FILENO);
		ft_putendl_fd(")'", STDERR_FILENO);
		return (free(str), NULL);
	}
	if (count != 0)
	{
		ft_putstr_fd(
			"minishell: syntax error near unexpected token `newline'",
			STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		return (free(str), NULL);
	}
	return (str);
}

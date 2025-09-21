/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/09/20 17:00:50 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	syntax_check(char **args, char **envp, t_node *node)
{
	(void)envp;
	(void)node;
	if (!args || !args[0])
		return (true);
	if (!check_leading_operators_syntax(args))
		return (false);
	if (!check_consecutive_operators_syntax(args))
		return (false);
	if (!check_trailing_operators_syntax(args))
		return (false);
	return (true);
}

void	handle_syntax_error(char **envp, t_node *node)
{
	const char	*error_token;

	(void)envp;
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	error_token = get_error_token(node->ori_args);
	ft_putstr_fd(error_token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	set_exit_status(2);
	if (node)
		node->syntax_flag = true;
}

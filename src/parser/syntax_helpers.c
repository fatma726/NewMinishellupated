/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatima <fatima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdab       #+#    #+#             */
/*   Updated: 2025/09/03 09:01:11 by fatima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

const char	*check_leading_operators(char **args)
{
	if (!args || !args[0])
		return (NULL);
	if (args[1] == NULL && (islr(args[0]) || isrr(args[0]) || isdlr(args[0])))
		return (NULL);
	if (isdlr(args[0]) && args[1])
		return (NULL);
	if ((isrr(args[0]) || isdrr(args[0]) || islr(args[0]) || isdlr(args[0]))
		&& args[1])
	{
		if (is_ampersand(args[1]))
			return ("&");
		if (isda(args[1]))
			return ("&&");
		if (isdp(args[1]))
			return ("||");
	}
	if (isp(args[0])
		|| isdp(args[0]) || isda(args[0]) || is_ampersand(args[0]))
		return (args[0]);
	return (NULL);
}

const char	*check_consecutive_ops(char **args, int i)
{
	if ((isp(args[i]) || islr(args[i]) || isrr(args[i]) || isdlr(args[i])
			|| isdp(args[i]) || isda(args[i]) || is_ampersand(args[i]))
		&& (isp(args[i + 1]) || islr(args[i + 1]) || isrr(args[i + 1])
			|| isdlr(args[i + 1]) || isdp(args[i + 1])
			|| isda(args[i + 1]) || is_ampersand(args[i + 1])))
		return (args[i + 1]);
	return (NULL);
}

const char	*check_triple_redir_split(char **args, int i)
{
	if (ft_strchr(args[i], '>')
		&& ft_strchr(args[i], '>'))
		return (">");
	return (NULL);
}

bool	c(char **args, int i, bool (*f1)(char *), bool (*f2)(char *))
{
	return (f1(args[i]) && f2(args[i + 1]));
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

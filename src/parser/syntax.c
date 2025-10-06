/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/10/06 21:32:10 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

bool	syntax_check(char **args, char **envp, t_node *node)
{
	int	i;

	(void)envp;
	(void)node;
	if (!args || !args[0])
		return (true);
	i = 0;
	while (args[i])
	{
		if (ft_strnstr(args[i], "|&", ft_strlen(args[i]))
			|| ft_strnstr(args[i], "&|", ft_strlen(args[i])))
			return (false);
		i++;
	}
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

bool	in_heredoc(char *str, int i)
{
	if (!str || i < 0)
		return (false);
	while (i && !ft_strchr(" \t", str[i]))
		i--;
	while (i && ft_strchr(" \t", str[i]))
		i--;
	return (i > 0 && str[i] == '<' && str[i - 1] == '<');
}

static void	process_quote_char(char c, int *quote)
{
	if (c == '\'' && *quote != 2)
	{
		if (*quote == 1)
			*quote = 0;
		else
			*quote = 1;
	}
	else if (c == '"' && *quote != 1)
	{
		if (*quote == 2)
			*quote = 0;
		else
			*quote = 2;
	}
}

int	quote_check(char const *str, int i, t_node *node)
{
	int	quote;
	int	j;

	if (!str || i < 0)
		return (0);
	quote = 0;
	j = 0;
	while (j <= i && str[j])
	{
		process_quote_char(str[j], &quote);
		j++;
	}
	(void)node;
	return (quote);
}

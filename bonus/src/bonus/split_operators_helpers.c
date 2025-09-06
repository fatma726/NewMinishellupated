/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_operators_helpers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdabrahym #+#    #+#             */
/*   Updated: 2025/01/29 19:31:40 by fatmtahmdabrahym ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../include/bonus.h"

bool	is_operator_pair(char *s, size_t i, t_node *n)
{
	if (quote_check(s, (int)i, n))
		return (false);
	return ((s[i] == '&' && s[i + 1] == '&')
		|| (s[i] == '|' && s[i + 1] == '|'));
}

static void	handle_ampersand_error(t_node *n)
{
	n->syntax_flag = true;
	set_exit_status(2);
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	ft_putchar_fd('&', STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}

static void	handle_double_ampersand_error(t_node *n)
{
	n->syntax_flag = true;
	set_exit_status(2);
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	ft_putstr_fd("&&", STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}

static bool	check_redir_token(char c, t_node *n)
{
	if (c == '&')
	{
		handle_ampersand_error(n);
		return (false);
	}
	return (true);
}

bool	check_redirection_syntax(char *s, t_node *n)
{
	size_t	j;
	size_t	k;

	j = 0;
	while (s[j])
	{
		if (s[j] == '>' && !quote_check(s, (int)j, n))
		{
			k = j + 1;
			if (s[k] == '>')
				k++;
			while (s[k] == ' ' || s[k] == '\t')
				k++;
			if (s[k] == '&' && s[k + 1] == '&')
			{
				handle_double_ampersand_error(n);
				return (false);
			}
			if (!check_redir_token(s[k], n))
				return (false);
		}
		j++;
	}
	return (true);
}

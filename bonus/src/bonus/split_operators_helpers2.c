/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_operators_helpers2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/10/06 18:54:01 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/bonus.h"

bool	syntax_err_pair(char *s, size_t i, t_node *n, int pair)
{
	n->syntax_flag = true;
	set_exit_status(2);
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	ft_putchar_fd(s[i], STDERR_FILENO);
	if (pair)
		ft_putchar_fd(s[i + 1], STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	free(s);
	return (true);
}

bool	starts_invalid(char *s, size_t i)
{
	return (i == 0 && ((s[i] == '|' && s[i + 1] == '|')
			|| (s[i] == '&' && s[i + 1] == '&')
			|| (s[i] == '&' && s[i + 1] != '&')));
}

bool	has_triple_ops(char *s, size_t i)
{
	return (s[i] && s[i + 1] && s[i + 2]
		&& ((s[i] == '|' && s[i + 1] == '|' && s[i + 2] == '|')
			|| (s[i] == '&' && s[i + 1] == '&' && s[i + 2] == '&')));
}

bool	has_mixed_op_error(char *s, t_node *n)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (!quote_check(s, (int)i, n) && s[i] == '|' && s[i + 1] == '&')
		{
			syntax_err_pair(s, i, n, 0);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	handle_invalid_start_and_report(char *s, size_t i, t_node *n)
{
	int	pair_flag;

	if (!starts_invalid(s, i))
		return (false);
	pair_flag = 1;
	if (i == 0 && s[i] == '&' && s[i + 1] != '&')
		pair_flag = 0;
	syntax_err_pair(s, i, n, pair_flag);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_helpers2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdabrahym #+#    #+#             */
/*   Updated: 2025/08/30 19:10:00 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	check_leading_operators_syntax(char **a)
{
	if (a[0] && (isp(a[0]) || istr(a[0])
			|| isdp(a[0]) || isda(a[0]) || is_ampersand(a[0])))
		return (false);
	if (a[0] && isdlr(a[0]) && a[1])
		return (true);
	if (a[0] && isdlr(a[0]) && !a[1])
		return (false);
	return (true);
}

bool	check_pipe_redir_combination(char **a, int i)
{
	if (ft_strchr(a[i], '|')
		&& (ft_strchr(a[i + 1], '>') || ft_strchr(a[i + 1], '<'))
		&& a[i + 2] && a[i + 2][0])
		return (true);
	return (false);
}

bool	check_trailing_operators_syntax(char **a)
{
	int		i;

	i = 0;
	while (a[i] && a[i + 1])
		i++;
	if (i > 0 && a[i] && (isp(a[i]) || islr(a[i]) || isrr(a[i])
			|| isdlr(a[i]) || isdrr(a[i]) || isdp(a[i]) || isda(a[i])
			|| is_ampersand(a[i]))
		&& !ft_strchr(a[i], '\'') && !ft_strchr(a[i], '"'))
		return (false);
	return (true);
}

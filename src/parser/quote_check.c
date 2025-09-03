/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatmtahmdab       #+#    #+#             */
/*   Updated: 2025/08/29 21:31:31 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	quote_check_loop(char const *s, int j, int *next, bool *doublequote)
{
	int	escape;

	escape = *next;
	if (escape != 2 && escape != 3 && s[j] == '\"')
	{
		*doublequote = escape != 1;
		*next = escape != 1;
		if (!next)
			escape = 0;
	}
	else if (escape != 1 && escape != 3 && s[j] == '\'')
		*next = ((escape != 2) * 2);
	else if (escape != 2 && escape != 3 && s[j] == '\\' && (escape != 1
			|| s[j + 1] == '"' || s[j + 1] == '\\' || s[j + 1] == '$'))
	{
		escape = 0;
		*next = 3;
	}
	else if (escape == 3)
		*next = *doublequote;
	return (escape);
}

int	quote_check(char const *s, int i, t_node *node)
{
	int		escape;
	int		j;
	bool	doublequote;
	int		next;

	if (node->escape_skip)
		return (0);
	doublequote = false;
	escape = 0;
	next = 0;
	j = -1;
	while (++j <= i)
		escape = quote_check_loop(s, j, &next, &doublequote);
	return (escape);
}

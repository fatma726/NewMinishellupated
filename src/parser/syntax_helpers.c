/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/09/23 14:24:37 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

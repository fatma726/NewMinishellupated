/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/09/20 17:01:04 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	in_heredoc(char *str, int i)
{
	while (i && !ft_strchr(" \t", str[i]))
		i--;
	while (i && ft_strchr(" \t", str[i]))
		i--;
	return (i && str[i] == '<' && str[i - 1] == '<');
}

int	quote_check(char const *str, int i, t_node *node)
{
	int	quote;
	int	j;

	quote = 0;
	j = 0;
	while (j <= i && str[j])
	{
		if (str[j] == '\'' && quote != 2)
		{
			if (quote == 1)
				quote = 0;
			else
				quote = 1;
		}
		else if (str[j] == '"' && quote != 1)
		{
			if (quote == 2)
				quote = 0;
			else
				quote = 2;
		}
		j++;
	}
	(void)node;
	return (quote);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_loop.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatima <fatima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/09/04 09:47:54 by fatima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_redirection_skip(char **args, char **newargs, int *i)
{
	if (i[2] > 0 && (isrr(args[i[2] - 1]) || isdrr(args[i[2] - 1])
			|| islr(args[i[2] - 1]) || islrr(args[i[2] - 1])
			|| isdlr(args[i[2] - 1]) || istlr(args[i[2] - 1])))
	{
		newargs[i[5]++] = ft_strdup(args[i[2]]);
		return ;
	}
}

static void	process_wildcard_in_arg(char **args, char **newargs, int *i,
		t_node *node)
{
	i[0] = -1;
	while (args[i[2]][++i[0]])
	{
		i[3] = quote_check(args[i[2]], i[0], node);
		if (!i[3] && args[i[2]][i[0]] == '*')
		{
			wildcard_handler(args, newargs, i, node);
			return ;
		}
	}
	newargs[i[5]++] = ft_strdup(args[i[2]]);
}

void	expand_wildcard_loop(char **args, char **newargs, char **envp,
		t_node *node)
{
	int											i[6];

	i[2] = -1;
	i[5] = 0;
	while (args[++i[2]])
	{
		handle_redirection_skip(args, newargs, i);
		if (i[2] > 0 && (isrr(args[i[2] - 1]) || isdrr(args[i[2] - 1])
				|| islr(args[i[2] - 1]) || islrr(args[i[2] - 1])
				|| isdlr(args[i[2] - 1]) || istlr(args[i[2] - 1])))
			continue ;
		tilde_handler(args, i, envp);
		process_wildcard_in_arg(args, newargs, i, node);
	}
	newargs[i[5]] = NULL;
}

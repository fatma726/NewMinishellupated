/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatima <fatima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/09/04 10:30:00 by fatima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifdef BUILD_BONUS

#include "../include/minishell.h"
#include "../../bonus/include/bonus.h"

static bool	is_redir_token(char *s)
{
	return (s && (isdlr(s) || isdrr(s) || islr(s) || islrr(s)
		|| isrr(s) || istlr(s)));
}

static size_t	compute_new_size(char **args)
{
	size_t	i;
	bool	skip;
	int		matches;
	size_t	sz;

	sz = 0;
	i = 0;
	skip = false;
	while (args && args[i])
	{
		if (skip)
		{
			skip = false;
			sz++;
			i++;
			continue ;
		}
		if (is_redir_token(args[i]))
		{
			sz++;
			skip = true;
			i++;
			continue ;
		}
		if (ft_strchr(args[i], '*'))
		{
			matches = count_matching_files(args[i]);
			sz += (matches > 0) ? (size_t)matches : 1;
		}
		else
			sz++;
		i++;
	}
	return (sz + 1);
}

char	**expand_wildcard_if_bonus(char **args, char **envp, t_node *node)
{
	char	**newargs;
	int		j;
	bool	skip_next;
	int		matches;
	int		i;

	(void)envp;
	(void)node;
	newargs = NULL;
	/* quick scan: if there is no '*' outside redirection contexts, just return */
	for (i = 0, skip_next = false; args && args[i]; ++i)
	{
		if (skip_next)
		{
			skip_next = false;
			continue ;
		}
		if (is_redir_token(args[i]))
		{
			skip_next = true;
			continue ;
		}
		if (ft_strchr(args[i], '*'))
		{
			newargs = (char **)malloc(sizeof(char *) * compute_new_size(args));
			break ;
		}
	}
	if (!newargs)
		return (args);
	/* build expanded args skipping redirection operands */
	j = 0;
	skip_next = false;
	for (i = 0; args && args[i]; ++i)
	{
		if (skip_next)
		{
			newargs[j++] = ft_strdup(args[i]);
			skip_next = false;
			continue ;
		}
		if (is_redir_token(args[i]))
		{
			newargs[j++] = ft_strdup(args[i]);
			skip_next = true;
			continue ;
		}
		if (ft_strchr(args[i], '*'))
		{
			matches = expand_pattern(newargs, &j, args[i]);
			if (matches == 0)
			{
				newargs[j++] = ft_strdup(args[i]);
			}
		}
		else
			newargs[j++] = ft_strdup(args[i]);
	}
	newargs[j] = NULL;
	strarrfree(args);
	return (newargs);
}

#else

char	**expand_wildcard_if_bonus(char **args, char **envp, t_node *node)
{
	(void)envp;
	(void)node;
	return (args);
}

#endif

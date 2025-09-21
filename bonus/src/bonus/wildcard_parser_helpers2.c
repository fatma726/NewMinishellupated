/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_parser_helpers2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/09/21 15:07:09 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifdef BUILD_BONUS
# include "bonus.h"

/* prototypes provided in bonus.h */

void	break_on_first_pattern(char **args, char ***out, int *i,
								bool *skip)
{
	*out = NULL;
	*i = 0;
	*skip = false;
	while (args && args[*i])
	{
		if (*skip)
		{
			*skip = false;
			(*i)++;
			continue ;
		}
		if (is_redir_token(args[*i]))
		{
			*skip = true;
			(*i)++;
			continue ;
		}
		if (ft_strchr(args[*i], '*'))
		{
			*out = (char **)malloc(sizeof(char *) * count_expanded_size(args));
			break ;
		}
		(*i)++;
	}
}

void	append_arg_or_expand(char **newargs, int *j, char *arg)
{
	int	matches;

	if (ft_strchr(arg, '*'))
	{
		matches = expand_pattern(newargs, j, arg);
		if (matches == 0)
			newargs[(*j)++] = ft_strdup(arg);
	}
	else
		newargs[(*j)++] = ft_strdup(arg);
}

void	process_one_arg(char **args, char **newargs,
			int *ij, bool *skip_next)
{
	if (*skip_next)
	{
		newargs[(ij[1])++] = ft_strdup(args[ij[0]]);
		*skip_next = false;
		ij[0]++;
		return ;
	}
	if (is_redir_token(args[ij[0]]))
	{
		newargs[(ij[1])++] = ft_strdup(args[ij[0]]);
		*skip_next = true;
		ij[0]++;
		return ;
	}
	append_arg_or_expand(newargs, &ij[1], args[ij[0]]);
	ij[0]++;
}

void	build_expanded_args(char **args, char **newargs)
{
	int		ij[2];
	bool	skip_next;

	ij[0] = 0;
	ij[1] = 0;
	skip_next = false;
	while (args && args[ij[0]])
		process_one_arg(args, newargs, ij, &skip_next);
	newargs[ij[1]] = NULL;
}

#endif

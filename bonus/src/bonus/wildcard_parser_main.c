/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_parser_main.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/09/30 23:00:00 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

#ifdef BUILD_BONUS
# include "bonus.h"

/* implemented in wildcard_parser_helpers.c */

/* helper prototypes are provided by headers; avoid redundant decls */

char	**expand_wildcard_if_bonus(char **args, char **envp, t_node *node)
{
	char	**newargs;
	int		i;
	bool	skip_next;

	(void)envp;
	(void)node;
	break_on_first_pattern(args, &newargs, &i, &skip_next);
	if (!newargs)
		return (args);
	build_expanded_args(args, newargs);
	strarrfree(args);
	return (newargs);
}

#endif

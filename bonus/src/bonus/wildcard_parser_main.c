/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_parser_main.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatmtahmdabrahym <fatmtahmdabrahym@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/09/20 17:21:27 by fatmtahmdab      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifdef BUILD_BONUS
# include "bonus.h"

bool		is_redir_token(char *s);
size_t		count_expanded_size(char **args);
bool		check_wildcard_redirections(char **args);
void		build_expanded_args(char **args, char **newargs);
void		process_one_arg(char **args, char **newargs, int *ij,
				bool *skip_next);

/* implemented in wildcard_parser_helpers.c */

void		break_on_first_pattern(char **args, char ***out, int *i,
				bool *skip);
void		append_arg_or_expand(char **newargs, int *j, char *arg);
void		process_one_arg(char **args, char **newargs, int *ij,
				bool *skip_next);
void		build_expanded_args(char **args, char **newargs);

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

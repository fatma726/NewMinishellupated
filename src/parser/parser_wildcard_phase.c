/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_wildcard_phase.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatima <fatima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by fatima            #+#    #+#             */
/*   Updated: 2025/09/22 22:22:01 by fatima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#ifdef BUILD_BONUS
# include "../../bonus/include/bonus.h"

char	**apply_wildcard_phase(char **args, char **envp, t_node *node,
		char *orig)
{
	if (!check_wildcard_redirections(args))
	{
		free(orig);
		strarrfree(args);
		set_exit_status(1);
		return (NULL);
	}
	return (expand_wildcard_if_bonus(args, envp, node));
}

#else

char	**apply_wildcard_phase(char **args, char **envp, t_node *node,
		char *orig)
{
	(void)envp;
	(void)node;
	(void)orig;
	return (args);
}

#endif
